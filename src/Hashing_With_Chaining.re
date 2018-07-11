type element('a, 'b) = {
    key: 'a,
    value: 'b
};

type bucket('a, 'b) = list(element('a, 'b));

type t('a, 'b) = {
    pre_hash: 'a => int,
    hash: int => int => int,
    table: ref(array(bucket('a, 'b))),
    num_bindings: int
};

let create = (~pre_hash, ~hash) => {
    pre_hash,
    hash,
    table: ref([|[]|]),
    num_bindings: 0
};

exception Not_found;

let bucket = (map, key) => {
    let {pre_hash, hash, table} = map;
    let table = table^;
    let number_buckets = Array.length(table);
    let bucket_index = pre_hash(key) |> hash(number_buckets);
    let bucket = Array.get(table, bucket_index);
    (bucket, bucket_index)
};

let remove_from_bucket = (bucket, key) => {
    let rec helper = (prev, next) => {
        switch next {
        | [] => raise(Not_found)
        | [e, ...rest] when e.key == key => List.rev_append(prev, rest);
        | [e, ...rest] => helper([e, ...prev], rest);
        };
    };

    helper([], bucket);
};

let find = (map, key) => {
    let (bucket, _index) =  bucket(map, key);
    let element = List.find(element => element.key == key, bucket);
    element.value;
};

let add = (map, key, value) => {
    let (bucket, index) =  bucket(map, key);
    Array.set(map.table^, index, [{key, value}, ...bucket]);
};

let remove = (map, key) => {
    let (bucket, index) =  bucket(map, key);
    Array.set(map.table^, index, remove_from_bucket(bucket, key));
};

let length = map => map.num_bindings;
