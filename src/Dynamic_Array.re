type t('a) = {
    array: array('a),
    size: int
};

exception InvalidArgument(string);

let create = () => ({
    array: [||],
    size: 0
});

let length = dynamic_array => dynamic_array.size;

let get = (dynamic_array, index) => {
    let {size, array} = dynamic_array;
    switch index {
    | ind when ind < 0 => raise(InvalidArgument("index out of bounds"))
    | ind when ind >= size => raise(InvalidArgument("index out of bounds"))
    | ind => Array.get(array, ind)
    };
}