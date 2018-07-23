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

let create = (~init_size=1, ~pre_hash, ~hash, ()) => {
    pre_hash,
    hash,
    table: ref(Array.make(init_size, Empty)),
    num_bindings: ref(0),
    load: 0.25
};

exception Key_not_found;
exception Inconsistent_state;

let length = map => map.num_bindings^;

let find_index = (map, key) => {
    let {hash, pre_hash, table} = map;
    let table = table^;

    let num_slots = Array.length(table);
    let hash = hash(num_slots, pre_hash(key));

    let rec search = iter => {
        if (iter == num_slots) {
            raise(Key_not_found)
        };

        let index = hash(iter);
        let slot = Array.get(table, index);
        switch slot {
        | Empty => raise(Key_not_found)
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

let insert = ({hash, pre_hash, table, num_bindings}) => {
    let table = table^;
    let num_slots = Array.length(table);
    let hash = hash(num_slots);

    (key, value) => {
        let hash = hash(pre_hash(key));

        let rec aux = iter => {
            if (iter == num_slots) {
                raise(Key_not_found) 
            };
    
            let index = hash(iter);
            let slot = Array.get(table, index);
            switch slot {
            | Empty | Deleted => {
                Array.set(table, index, Filled({key, value}));
                num_bindings := num_bindings^ + 1;
            }
            | Filled(binding) when binding.key == key => {
                Array.set(table, index, Filled({key, value}));
            }
            | _ => aux(iter + 1)
            };
        };

        aux(0);
    }
};

let rehash = (map, expected_num_slots) => {
    let {pre_hash, hash} = map;
    let temp_map = create(
        ~pre_hash=pre_hash,
        ~hash=hash,
        ~init_size=expected_num_slots,
        ()
    );

    let populate = insert(temp_map);
    iter(populate, map);

    map.table := temp_map.table^;
};

let maybe_rehash = map => {
    let num_slots = Array.length(map.table^);
    let expected_num_slots = expected_num_slots(map);
    if(num_slots != expected_num_slots) {
        rehash(map, expected_num_slots)
    }
};

let add = (map, key, value) => {
    insert(map)(key, value);
    maybe_rehash(map);
};

let remove = (map, key) => {
    let index = find_index(map, key);
    Array.set(map.table^, index, Deleted);
    map.num_bindings := map.num_bindings^ - 1;
    maybe_rehash(map);
};