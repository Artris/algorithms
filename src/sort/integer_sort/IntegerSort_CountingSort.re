let max = array => {
    let aux = (current_max, value) => {
        switch current_max {
        | None => Some(value)
        | Some(current_max) => Some(current_max < value ? value : current_max)
        };
    };

    Array.fold_left(aux, None, array);
};

let count = (array, max) => {
    let counters = Array.make(max + 1, 0);
    let increment_counter = (counters, value) => {
        let counter = Array.get(counters, value);
        Array.set(counters, value, counter + 1);
        counters;
    };

    Array.fold_left(increment_counter, counters, array);
};

let repeat = counts => {
    let repeated = Array.mapi((value, count) => Array.make(count, value), counts);
    Array.concat(Array.to_list(repeated));
};

let sort = array => {
    let max = max(array);
    switch max {
    | None => [||]
    | Some(max) => {
        let counts = count(array, max);
        repeat(counts);
    }
    };
};