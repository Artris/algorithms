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