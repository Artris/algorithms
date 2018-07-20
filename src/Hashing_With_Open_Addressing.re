type binding('a, 'b) = {
    key: 'a,
    value: 'b
};

type bucket('a , 'b) = 
  | Empty
  | Deleted
  | Filled(binding('a, 'b));

type t('a, 'b) = {
    pre_hash: 'a => int,
    hash: (int, int, int) => int,
    table: ref(array(bucket('a, 'b))),
    num_bindings: ref(int),
    load: float
};

let create = (~pre_hash, ~hash) => {
    pre_hash,
    hash,
    table: ref([|Empty|]),
    num_bindings: ref(0),
    load: 0.25
};

exception Not_found;
exception Inconsistent_state;

let length = map => map.num_bindings^;

let find_index = (map, key) => {
    let {hash, pre_hash, table} = map;
    let table = table^;

    let num_buckets = Array.length(table);
    let hash = hash(num_buckets, pre_hash(key));

    let rec search = iter => {
        if (iter == num_buckets) {
            raise(Not_found)
        };

        let index = hash(iter);
        let bucket = Array.get(table, index);
        switch bucket {
        | Empty => raise(Not_found)
        | Deleted => search(iter + 1)
        | Filled(binding) when binding.key == key => index
        | _ => search(iter + 1)
        };
    };

    search(0);
}

let find = (map, key) => {
    let index = find_index(map, key);
    let bucket = Array.get(map.table^, index);
    switch bucket {
    | Empty | Deleted => raise(Inconsistent_state)
    | Filled(binding) => binding.value
    };
};

let iter = (f, map) => {
    let f = 
        fun
        | Empty => ()
        | Deleted => ()
        | Filled(binding) => f(binding.key, binding.value);
    
    Array.iter(f, map.table^);
};

let expected_num_buckets = map => {
    let {table, num_bindings} = map;
    let num_buckets = Array.length(table^);
    let load = float_of_int(num_bindings^) /. float_of_int(num_buckets);
    switch load {
    | l when l > (map.load *. 2.) => num_buckets * 2
    | l when l < (map.load /. 2.) && num_buckets > 1 => num_buckets / 2
    | _ => num_buckets
    };
};

let find_insert_bucket_index = (table, hash, pre_hash, key) => {
    let num_buckets = Array.length(table);
    let hash = hash(pre_hash(key));

    let rec search = iter => {
        if (iter == num_buckets) {
            raise(Not_found) 
        };

        let index = hash(iter);
        let bucket = Array.get(table, index);
        switch bucket {
        | Empty | Deleted => index
        | Filled(binding) when binding.key == key => index
        | _ => search(iter + 1)
        };
    };

    search(0);
};

let rehash = (map, expected_num_buckets) => {
    let {pre_hash, hash} = map;
    let hash = hash(expected_num_buckets);
    let table = Array.make(expected_num_buckets, Empty);

    let populate = (key, value) => {
        let bucket_index = find_insert_bucket_index(table, hash, pre_hash, key);
        Array.set(table, bucket_index, Filled({key, value}));
    };

    iter(populate, map);
    map.table := table;
};

let maybe_rehash = map => {
    let num_buckets = Array.length(map.table^);
    let expected_num_buckets = expected_num_buckets(map);
    if(num_buckets != expected_num_buckets) {
        rehash(map, expected_num_buckets)
    }
};

let add = (map, key, value) => {
    let {table, hash, pre_hash, num_bindings} = map;
    let table = table^;
    let num_buckets = Array.length(table);
    let index = find_insert_bucket_index(table, hash(num_buckets), pre_hash, key);
    Array.set(table, index, Filled({key, value}));
    num_bindings := num_bindings^ + 1;
    maybe_rehash(map);
};

let remove = (map, key) => {
    let index = find_index(map, key);
    Array.set(map.table^, index, Deleted);
    maybe_rehash(map);
};