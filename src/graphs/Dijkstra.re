type node = {
    id: string,
    neighbours: list(string),
};

type directedGraph = list(node);

type edge = {
    tail: string,
    head: string,
    weight: int,
};

type resultType = {
    dist: Hashtbl.t(string, int),
    prev: Hashtbl.t(string, option(string))
};

exception Not_found(string);

let infinity = Pervasives.max_int;

let parseAdjList = adj_list => {
    let adj_tbl = Hashtbl.create(List.length(adj_list));
    let insert = ({id, neighbours}) => {
        Hashtbl.add(adj_tbl, id, neighbours);
    };

    List.iter(insert, adj_list);
    let validateNeighbours = node => {
        List.iter(neighbour => {
            if (!Hashtbl.mem(adj_tbl, neighbour)) {
                raise(Not_found(neighbour));
            }
        }, node.neighbours);
    };

    List.iter(validateNeighbours, adj_list);
    adj_tbl;
};

let parseWeights = (weight_list, adj_list) => {
    let weight_tbl = Hashtbl.create(List.length(adj_list));
    let initializeWeights = ({id, neighbours}) => {
        let adj_edge_weights = Hashtbl.create(List.length(neighbours));
        Hashtbl.add(weight_tbl, id, adj_edge_weights);
    };

    List.iter(initializeWeights, adj_list);
    let insertWeight = ({tail, head, weight}) => {
        let adj_edge_weights = Hashtbl.find(weight_tbl, tail);
        Hashtbl.add(adj_edge_weights, head, weight);
    };

    List.iter(insertWeight, weight_list);
    weight_tbl;
};

let initializeDist = (adj_list, source_id) => {
    let dist = Hashtbl.create(List.length(adj_list));
    let initialize = ({id, _}) => {
        Hashtbl.add(dist, id, infinity);    
    };

    List.iter(initialize, adj_list);
    Hashtbl.replace(dist, source_id, 0);
    dist;
};

let initializePrev = adj_list => {
    let prev = Hashtbl.create(List.length(adj_list));
    let initialize = ({id, _}) => {
        Hashtbl.add(prev, id, None);
    };

    List.iter(initialize, adj_list);
    prev;
};

let getEdgeWeight = (weight_tbl, tail, head) => {
    let adj_edge_weights = Hashtbl.find(weight_tbl, tail);
    Hashtbl.find(adj_edge_weights, head);
};

let add = (a, b) => {
    if (a == infinity || b == infinity) {
        infinity;
    } else {
        a + b;
    };
};

let rec traverse = (~queue, ~adj_tbl, ~weight_tbl, ~dist, ~prev) => {
    switch (Heap.size(queue)) {
    | 0 => ();
    | _ => {
        let current_id = Heap.extract(queue);
        let neighbours = Hashtbl.find(adj_tbl, current_id);
        
        let updateDist = neighbour_id => {
            let neighbour_dist = Hashtbl.find(dist, neighbour_id);
            let current_dist = Hashtbl.find(dist, current_id);
            let edge_weight = getEdgeWeight(weight_tbl, current_id, neighbour_id);
            let alt_dist = add(current_dist, edge_weight);

            if (alt_dist < neighbour_dist) {
                Hashtbl.replace(dist, neighbour_id, alt_dist);
                Hashtbl.replace(prev, neighbour_id, Some(current_id));
                Heap.remove(queue, (key, _) => key == neighbour_id) |> ignore;
                Heap.add(queue, neighbour_id, neighbour_id);
            };
        };
        
        List.iter(updateDist, neighbours);
        traverse(
            ~queue=queue,
            ~adj_tbl=adj_tbl,
            ~weight_tbl=weight_tbl,
            ~dist=dist, 
            ~prev=prev);
    };
    };
};

let search = (adj_list, weights, source_id) => {
    let prev = initializePrev(adj_list);
    let dist = initializeDist(adj_list, source_id);
    let weight_tbl = parseWeights(weights, adj_list);
    let adj_tbl = parseAdjList(adj_list);

    let compare = (a, b) => {
        let dist_a = Hashtbl.find(dist, a);
        let dist_b = Hashtbl.find(dist, b);
        dist_a < dist_b;
    };

    let priorityQueue = Heap.create(compare);
    let enqueue = (key, _) => {
        Heap.add(priorityQueue, key, key);
    };

    Hashtbl.iter(enqueue, dist);
    traverse(
        ~queue=priorityQueue,
        ~adj_tbl=adj_tbl,
        ~weight_tbl=weight_tbl,
        ~dist=dist, 
        ~prev=prev);
    
    {dist: dist, prev: prev};
};