/*
Adapted from the Python implementation
https://en.wikipedia.org/wiki/Radix_sort#Implementation
*/

exception Inconsistent_state;

let rec pow = (n, p) =>
    switch (n, p) {
    | (_, 0) => 1
    | (n, p) => n * pow(n, p - 1)
    };

let upto = (~from=0, num) => {
    let rec aux = it => {
        if(it < num){
            [it, ...aux(it + 1)]
        } else {
            []
        }
    };

    aux(from);
};

let num_digits = (num, base) => {
    let rec aux = (num, count) => {
        let num = num / base;
        if(num == 0){
            count + 1;
        } else {
            aux(num, count + 1);
        };
    };

    aux(num, 0);
};

let list_to_array = list => {
    let length = List.length(list);
    let array = Array.make(length, None);
    List.iteri((ind, e) => {
        Array.set(array, ind, Some(e));
    }, list);

    Array.map(e => {
        switch e {
        | None => raise(Inconsistent_state)
        | Some(v) => v
        };
    }, array);
};

let max = list => List.fold_left((cur_max, num) => {
    switch cur_max {
    | None => Some(num)
    | Some(cur_max) => Some(cur_max < num ? num : cur_max)
    };
}, None, list);

let list_to_bucket = (list, base, iteration) => {
    let buckets = Array.make(base, []);

    let aux = num => {
        let bucket_index = (num / pow(base, iteration)) mod base;
        let bucket = Array.get(buckets, bucket_index);
        Array.set(buckets, bucket_index, [num, ...bucket]);
    };

    List.iter(aux, list);
    buckets;
};

let buckets_to_list = buckets => Array.fold_left(
    (bucket, list) => List.append(list, bucket), [], buckets);

let sort = (array, base) => {
    let list = Array.to_list(array);
    let max = max(list);
    switch max {
    | None => [||]
    | Some(max) => {
        let max_num_digits = num_digits(max, base);
        let digit_indices_from_right = upto(max_num_digits);

        let aux = (list, it) => {
            let buckets = list_to_bucket(list, base, it);
            buckets_to_list(buckets);
        };

        let list = List.fold_left(aux, list, digit_indices_from_right);
        list_to_array(List.rev(list));
    }
    };        
};