type t('a) = {
    array: ref(array(option('a))),
    size: ref(int)
};

exception InvalidArgument(string);
exception InconsistentState(string); 

let create = () => ({
    array: ref([||]),
    size: ref(0)
});

let length = dynamic_array => dynamic_array.size^;

let contents =
    fun
    | None => raise(InconsistentState("expected a value"))
    | Some(value) => value

let get = (dynamic_array, index) => {
    let {size, array} = dynamic_array;
    switch index {
    | ind when ind < 0 => raise(InvalidArgument("index out of bounds"))
    | ind when ind >= size^ => raise(InvalidArgument("index out of bounds"))
    | ind => Array.get(array^, ind) |> contents
    };
}

let set = (dynamic_array, index, value) => {
    let {size, array} = dynamic_array;
    switch index {
    | ind when ind < 0 => raise(InvalidArgument("index out of bounds"))
    | ind when ind >= size^ => raise(InvalidArgument("index out of bounds"))
    | ind => Array.set(array^, ind, Some(value))
    };
}

let push = (dynamic_array, value) => {
    let {size, array} = dynamic_array;
    let space = Array.length(array^);

    if(size^ == space){
        array := Array.append(array^, Array.make(space + 1, None));
    };
    
    Array.set(array^, size^, Some(value));
    size := size^ + 1;

    dynamic_array;
}