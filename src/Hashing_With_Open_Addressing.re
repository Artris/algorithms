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