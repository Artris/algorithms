type binding('a, 'b) = {
    key: 'a,
    value: 'b
};

type state('a , 'b) = 
  | Empty
  | Deleted
  | Filled(binding('a, 'b));

type t('a, 'b) = {
    pre_hash: 'a => int,
    hash: (int, int, int) => int,
    table: ref(array(state('a, 'b))),
    num_bindings: ref(int)
};

let create = (~pre_hash, ~hash) => {
    pre_hash,
    hash,
    table: ref([||]),
    num_bindings: ref(0)
};

exception Not_found;

let length = map => map.num_bindings^;

let find = (map, key) => {
    let {hash, pre_hash, table} = map;
    let table = table^;
    let key = pre_hash(key);

    let size = Array.length(table);
    let hash = hash(size, key);

    let rec search = iter => {
        let index = hash(iter);
        let state = Array.get(table, index);
        switch state {
        | Empty => raise(Not_found)
        | Deleted => search(iter + 1)
        | Filled(binding) when binding.key == key => binding.value
        | _ => search(iter + 1)
        };
    };

    search(0);
};
