type element('a, 'b) = {
    key: 'a,
    value: 'b
};

type bucket('a, 'b) = list(element('a, 'b));

type t('a, 'b) = {
    pre_hash: 'a => int,
    hash: int => int => int,
    table: array(bucket('a, 'b)),
    num_bindings: int
};

let create = (~pre_hash, ~hash) => {
    pre_hash,
    hash,
    table: [||],
    num_bindings: 0
};

let find = (map, key) => {
    let {pre_hash, hash, table} = map;
    let number_buckets = Array.length(table);
    let bucket_index = pre_hash(key) |> hash(number_buckets);
    let bucket = Array.get(table, bucket_index);
    let element = List.find(element => element.key == key, bucket);
    element.value;
};