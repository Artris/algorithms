module type Sort {
    let sort: array(int) => array(int);
};

module Merge: Sort {
    let merge = (a, b) => {
        let a_len = Array.length(a);
        let b_len = Array.length(b);
        let res = Array.make(a_len + b_len, 0);
        
        let rec aux = (a_ind, b_ind) => {
            let a' = a_ind < a_len ? Some(Array.get(a, a_ind)) : None;
            let b' = b_ind < b_len ? Some(Array.get(b, b_ind)) : None;
            switch (a', b') {
            | (None, None) => res
            | (Some(a_val), None) => {
                Array.set(res, a_ind + b_ind, a_val);
                aux(a_ind + 1, b_ind);
            }
            | (None, Some(b_val)) => {
                Array.set(res, a_ind + b_ind, b_val);
                aux(a_ind, b_ind + 1);
            }
            | (Some(val_a), Some(val_b)) when val_a < val_b => {
                Array.set(res, a_ind + b_ind, val_a);
                aux(a_ind + 1, b_ind);
            }
            | (_, Some(val_b)) => {
                Array.set(res, a_ind + b_ind, val_b);
                aux(a_ind, b_ind + 1);
            }
            };
        };
    
        aux(0, 0);
    };
    
    let rec sort =
        fun
        | [||] => [||]
        | [|head|] => [|head|]
        | arr => {
            let len = Array.length(arr);
            let mid = len / 2;
            let a = Array.sub(arr, 0, mid);
            let b = Array.sub(arr, mid, len - mid);
            let a' = sort(a);
            let b' = sort(b);
            merge(a', b');
        };
    
};