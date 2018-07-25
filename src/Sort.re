module type Sort = {
    let sort: (('a, 'a) => bool, array('a)) => array('a);
};

exception Invalid_state;

module Merge: Sort {
    let merge = (compare, a, b) => {
        let (<<) = compare;
        let a_len = Array.length(a);
        let b_len = Array.length(b);
        let res = Array.make(a_len + b_len, None);
        
        let rec aux = (a_ind, b_ind) => {
            let a' = a_ind < a_len ? Some(Array.get(a, a_ind)) : None;
            let b' = b_ind < b_len ? Some(Array.get(b, b_ind)) : None;
            switch (a', b') {
            | (None, None) => res
            | (Some(_a_val), None) => {
                Array.set(res, a_ind + b_ind, a');
                aux(a_ind + 1, b_ind);
            }
            | (None, Some(_b_val)) => {
                Array.set(res, a_ind + b_ind, b');
                aux(a_ind, b_ind + 1);
            }
            | (Some(a_val), Some(b_val)) when a_val << b_val => {
                Array.set(res, a_ind + b_ind, a');
                aux(a_ind + 1, b_ind);
            }
            | (_, Some(_b_val)) => {
                Array.set(res, a_ind + b_ind, b');
                aux(a_ind, b_ind + 1);
            }
            };
        };
    
        aux(0, 0) |> Array.map(e => {
            switch e {
            | Some(v) => v
            | None => raise(Invalid_state)
            };
        });
    };
    
    let sort = (compare, array) => {
        let rec aux = 
            fun
            | [||] => [||]
            | [|head|] => [|head|]
            | arr => {
                let len = Array.length(arr);
                let mid = len / 2;
                let a = Array.sub(arr, 0, mid);
                let b = Array.sub(arr, mid, len - mid);
                let a' = aux(a);
                let b' = aux(b);
                merge(compare, a', b');
            };

        aux(array);
    };
};

module Insertion: Sort {
    let insert = (compare, array, index) => {
        let (<<) = compare;
        let rec aux = index => {
            if(0 < index){
                let n = Array.get(array, index);
                let p = Array.get(array, index - 1);
                if(n << p){
                    Array.set(array, index, p);
                    Array.set(array, index - 1, n);
                    aux(index - 1);
                };
            };
        };

        aux(index);
    };


    let sort = (compare, array) => {
        let array = Array.copy(array);
        let length = Array.length(array);
        let insert = insert(compare, array);
        
        let rec aux = index => {
            if(index < length){
                insert(index);
                aux(index + 1);
            };
        };

        aux(1);
        array;
    };
};