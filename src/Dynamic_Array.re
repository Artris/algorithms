type t('a) = {
    array: ref(array(option('a))),
    size: ref(int)
};

exception InvalidArgument(string);
exception InconsistentState(string);
exception ArrayIsEmpty;

let create = () => ({
    array: ref([||]),
    size: ref(0)
});

let length = dynamic_array => dynamic_array.size^;

let contents =
    fun
    | None => raise(InconsistentState("expected a value"))
    | Some(value) => value;

let execute_if_index_is_valid = (dynamic_array, index, fn) => {
    let {size, array} = dynamic_array;
    let size = size^;
    let array = array^;
    if(index < 0 || index >= size) {
        raise(InvalidArgument("index out of bounds"))
    } else {
        fn(array);
    }
};

let get = (dynamic_array, index) => {
    let fn = array => { Array.get(array, index) |> contents };
    execute_if_index_is_valid(dynamic_array, index, fn);
};

let set = (dynamic_array, index, value) => {
    let fn = array => { Array.set(array, index, Some(value)) };
    execute_if_index_is_valid(dynamic_array, index, fn);
};

let push = (dynamic_array, value) => {
    let {size, array} = dynamic_array;
    let available_space = Array.length(array^);

    if(size^ == available_space){
        array := Array.append(array^, Array.make(available_space + 1, None));
    };
    
    Array.set(array^, size^, Some(value));
    size := size^ + 1;
};

let pop = dynamic_array => {
    let {size, array} = dynamic_array;
    let available_space = Array.length(array^);

    if(size^ == 0){
        raise(ArrayIsEmpty);
    } else {
        let index = size^ - 1;
        let value = Array.get(array^, index);
        Array.set(array^, index, None);

        if (size^ < available_space / 4){
            array := Array.sub(array^, 0, available_space / 2);
        };

        size := size^ - 1;
        contents(value);
    }
};

let swap = (dynamic_array, a, b) => {
    let a' = get(dynamic_array, a);
    let b' = get(dynamic_array, b);
    set(dynamic_array, a, b');
    set(dynamic_array, b, a');
}

let inspect = dynamic_array => Js.Array.toString(dynamic_array.array^);