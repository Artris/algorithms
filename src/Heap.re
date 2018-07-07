type heapElement('a, 'b) = {
    key: 'a,
    value: 'b
};

type t('a, 'b) = {
    queue: Dynamic_Array.t(heapElement('a, 'b)),
    compare: ('a, 'a) => bool 
};

exception EmptyQueue;
exception HasHigherPriority;

let create = compare => {
    queue: Dynamic_Array.create(),
    compare: compare
};

let parent = 
    fun
    | 0 => None
    | index => Some(index / 2);

let left = index => 2 * index + 1;
let right = index => 2 * (index + 1);

let swap = (a, b, queue) => {
    let a' = Dynamic_Array.get(queue, a);
    let b' = Dynamic_Array.get(queue, b);
    Dynamic_Array.set(queue, a, b');
    Dynamic_Array.set(queue, b, a');
};

let key = (queue, index) => Dynamic_Array.get(queue, index).key;

let rec sift_down = (index, compare, queue) => {
    let key = key(queue);
    let heap_size = Dynamic_Array.length(queue);
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
        swap(max_priority_index, index, queue);
        sift_down(max_priority_index, compare, queue);
    }
};

let rec sift_up = (index, compare, queue) => {
    let key = key(queue);
    let parent_index = parent(index);

    switch parent_index {
    | Some(p_ind) when compare(key(index), key(p_ind)) => {
        swap(index, p_ind, queue);
        sift_up(p_ind, compare, queue);
    }
    | _ => () 
    };
};

let fix_last = (compare, queue) => {
    let heap_size = Dynamic_Array.length(queue);
    sift_up(heap_size - 1, compare, queue);
};

let extract = heap => {
    switch (Dynamic_Array.length(heap.queue)) {
    | 0 => raise(EmptyQueue)
    | 1 => Dynamic_Array.pop(heap.queue).value;
    | _ => {
        let q = heap.queue;
        let heap_size = Dynamic_Array.length(q);
        let head = Dynamic_Array.get(q, 0);
        swap(0, heap_size - 1, q);
        sift_down(0, heap.compare, q);
        head.value;
    }
    };
};

let add = (heap, key, value) => {
    Dynamic_Array.push(heap.queue, {key, value});
    fix_last(heap.compare, heap.queue);
};

let head = heap => {
    switch (Dynamic_Array.length(heap.queue)) {
    | 0 => raise(EmptyQueue)
    | _ => Dynamic_Array.get(heap.queue, 0).value
    };
};

let update_priority = (heap, index, new_priority) => {
    let queue = heap.queue;
    let current_priority = key(queue, index);
    let value = Dynamic_Array.get(queue, index).value;
    Dynamic_Array.set(queue, index, {key: new_priority, value: value});

    let has_higher_priority = heap.compare(new_priority, current_priority);
    if(has_higher_priority){
        sift_up(index, heap.compare, queue)
    } else {
        sift_down(index, heap.compare, queue)
    }
}

let decrease_root_priority = (heap, new_priority) => {
    let queue = heap.queue;
    let current_priority = key(queue, 0);
    let has_higher_priority = heap.compare(new_priority, current_priority);
    if(has_higher_priority){
        raise(HasHigherPriority);
    } else {
        update_priority(heap, 0, new_priority);
    }
}

let size = heap => Dynamic_Array.length(heap.queue);