type binding('a, 'b) = {
    key: 'a,
    value: 'b
};

type slot('a , 'b) = 
  | Empty
  | Deleted
  | Filled(binding('a, 'b));

type t('a, 'b) = {
    pre_hash: 'a => int,
    hash: (int, int, int) => int,
    table: ref(array(slot('a, 'b))),
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

    let num_slots = Array.length(table);
    let hash = hash(num_slots, pre_hash(key));

    let rec search = iter => {
        if (iter == num_slots) {
            raise(Not_found)
        };

        let index = hash(iter);
        let slot = Array.get(table, index);
        switch slot {
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
    let slot = Array.get(map.table^, index);
    switch slot {
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

let expected_num_slots = map => {
    let {table, num_bindings} = map;
    let num_slots = Array.length(table^);
    let load = float_of_int(num_bindings^) /. float_of_int(num_slots);
    switch load {
    | l when l > (map.load *. 2.) => num_slots * 2
    | l when l < (map.load /. 2.) && num_slots > 1 => num_slots / 2
    | _ => num_slots
    };
};

let find_insert_slot_index = (table, hash, pre_hash, key) => {
    let num_slots = Array.length(table);
    let hash = hash(pre_hash(key));

    let rec search = iter => {
        if (iter == num_slots) {
            raise(Not_found) 
        };

        let index = hash(iter);
        let slot = Array.get(table, index);
        switch slot {
        | Empty | Deleted => index
        | Filled(binding) when binding.key == key => index
        | _ => search(iter + 1)
        };
    };

    search(0);
};

let rehash = (map, expected_num_slots) => {
    let {pre_hash, hash} = map;
    let hash = hash(expected_num_slots);
    let table = Array.make(expected_num_slots, Empty);

    let populate = (key, value) => {
        let bucket_index = find_insert_slot_index(table, hash, pre_hash, key);
        Array.set(table, bucket_index, Filled({key, value}));
    };

    iter(populate, map);
    map.table := table;
};

let maybe_rehash = map => {
    let num_slots = Array.length(map.table^);
    let expected_num_slots = expected_num_slots(map);
    if(num_slots != expected_num_slots) {
        rehash(map, expected_num_slots)
    }
};

let add = (map, key, value) => {
    let {table, hash, pre_hash, num_bindings} = map;
    let table = table^;
    let num_slots = Array.length(table);
    let index = find_insert_slot_index(table, hash(num_slots), pre_hash, key);
    Array.set(table, index, Filled({key, value}));
    num_bindings := num_bindings^ + 1;
    maybe_rehash(map);
};

let remove = (map, key) => {
    let index = find_index(map, key);
    Array.set(map.table^, index, Deleted);
    maybe_rehash(map);
};