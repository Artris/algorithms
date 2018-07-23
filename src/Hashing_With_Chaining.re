type binding('a, 'b) = {
    key: 'a,
    value: 'b
};

type bucket('a, 'b) = list(binding('a, 'b));

type t('a, 'b) = {
    pre_hash: 'a => int,
    hash: int => int => int,
    table: ref(array(bucket('a, 'b))),
    num_bindings: ref(int),
    load: int
};

let create = (~pre_hash, ~hash) => {
    pre_hash,
    hash,
    table: ref([|[]|]),
    num_bindings: ref(0),
    load: 16
};

exception Key_not_found;

let bucket = (map, key) => {
    let {pre_hash, hash, table} = map;
    let table = table^;
    let number_buckets = Array.length(table);
    let bucket_index = key |> pre_hash |> hash(number_buckets);
    let bucket = Array.get(table, bucket_index);
    (bucket, bucket_index)
};

let remove_from_bucket = (bucket, key) => {
    let rec helper = (prev, next) => {
        switch next {
        | [] => raise(Key_not_found)
        | [e, ...rest] when e.key == key => List.rev_append(prev, rest);
        | [e, ...rest] => helper([e, ...prev], rest);
        };
    };

    helper([], bucket);
};

let iter = (f, map) => {
    let f = e => f(e.key, e.value);
    let iter_bucket = bucket => {
        let bucket = List.rev(bucket);
        List.iter(f, bucket);
    };
    Array.iter(iter_bucket, map.table^);
};

let expected_num_buckets = map => {
    let {table, num_bindings} = map;
    let num_buckets = Array.length(table^);
    let load = num_bindings^ / num_buckets;
    switch load {
    | l when l > map.load * 2 => num_buckets * 2
    | l when l < map.load / 2 && num_buckets > 1 => num_buckets / 2
    | _ => num_buckets
    };
};

let rehash = (map, expected_num_buckets) => {
    let {pre_hash, hash} = map;
    let hash = hash(expected_num_buckets);
    let table = Array.make(expected_num_buckets, []);

    let populate = (key, value) => {
        let bucket_index = key |> pre_hash |> hash;
        let bucket = Array.get(table, bucket_index);
        Array.set(table, bucket_index, [{key, value}, ...bucket]);
    };

    iter(populate, map);
    map.table := table;
}

let maybe_rehash = map => {
    let num_buckets = Array.length(map.table^);
    let expected_num_buckets = expected_num_buckets(map);
    if(num_buckets != expected_num_buckets) {
        rehash(map, expected_num_buckets)
    }
};

let find = (map, key) => {
    let (bucket, _index) =  bucket(map, key);
    let binding = List.find(binding => binding.key == key, bucket);
    binding.value;
};

let add = (map, key, value) => {
    let (bucket, index) =  bucket(map, key);
    Array.set(map.table^, index, [{key, value}, ...bucket]);
    map.num_bindings := map.num_bindings^ + 1;
    maybe_rehash(map);
};

let remove = (map, key) => {
    let (bucket, index) =  bucket(map, key);
    Array.set(map.table^, index, remove_from_bucket(bucket, key));
    map.num_bindings := map.num_bindings^ - 1;
    maybe_rehash(map);
};

let length = map => map.num_bindings^;
