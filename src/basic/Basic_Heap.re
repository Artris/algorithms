module Array = Basic_DynamicArray;

type heapElement('a, 'b) = {
    key: 'a,
    value: 'b
};

type t('a, 'b) = {
    queue: Array.t(heapElement('a, 'b)),
    compare: ('a, 'a) => bool 
};

exception EmptyQueue;
exception HasHigherPriority;

let create = compare => {
    queue: Array.create(),
    compare: compare
};

let parent = 
    fun
    | 0 => None
    | index => Some((index - 1) / 2);

let left = index => 2 * index + 1;
let right = index => 2 * (index + 1);

let key = (queue, index) => Array.get(queue, index).key;

let rec sift_down = ({queue, compare}, index) => {
    let key = key(queue);
    let heap_size = Array.length(queue);
    let left_index = left(index);
    let right_index = right(index);

    let max_priority_index = ref(index);
    max_priority_index :=
        if (left_index < heap_size &&
            compare(key(left_index), key(max_priority_index^))){ left_index } 
        else { max_priority_index^ };
    
        max_priority_index :=
        if (right_index < heap_size &&
            compare(key(right_index), key(max_priority_index^))){ right_index } 
        else { max_priority_index^ };
    
    let max_priority_index = max_priority_index^;
    if(max_priority_index != index){
        Array.swap(queue, max_priority_index, index);
        sift_down({queue, compare}, max_priority_index);
    }
};

let rec sift_up = ({queue, compare}, index) => {
    let key = key(queue);
    let parent_index = parent(index);

    switch parent_index {
    | Some(p_ind) when compare(key(index), key(p_ind)) => {
        Array.swap(queue, index, p_ind);
        sift_up({queue, compare}, p_ind);
    }
    | _ => () 
    };
};

let fix_last = heap => {
    let heap_size = Array.length(heap.queue);
    sift_up(heap, heap_size - 1);
};

let extract = ({queue, compare}) => {
    let heap_size = Array.length(queue);
    switch heap_size {
    | 0 => raise(EmptyQueue)
    | 1 => Array.pop(queue).value;
    | _ => {
        Array.swap(queue, 0, heap_size - 1);
        let res = Array.pop(queue);
        sift_down({queue, compare}, 0);
        res.value;
    }
    };
};

let add = (heap, key, value) => {
    Array.push(heap.queue, {key, value});
    fix_last(heap);
};

let head = ({queue}) => {
    let heap_size = Array.length(queue);
    switch heap_size {
    | 0 => raise(EmptyQueue)
    | _ => Array.get(queue, 0).value
    };
};

let update_priority = ({queue, compare}, index, new_priority) => {
    let current_priority = key(queue, index);
    let value = Array.get(queue, index).value;
    Array.set(queue, index, {key: new_priority, value: value});

    let has_higher_priority = compare(new_priority, current_priority);
    if(has_higher_priority){
        sift_up({queue, compare}, index)
    } else {
        sift_down({queue, compare}, index)
    }
}

let decrease_root_priority = ({queue, compare}, new_priority) => {
    let current_priority = key(queue, 0);
    let has_higher_priority = compare(new_priority, current_priority);
    if(has_higher_priority){
        raise(HasHigherPriority);
    } else {
        update_priority({queue, compare}, 0, new_priority);
    }
}

let size = heap => Array.length(heap.queue);
