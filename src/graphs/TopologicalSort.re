type node = {
    id: string,
    neighbours: list(string),
};

type mark =
  | Temp
  | Perm;

type directedGraph = list(node);

exception Not_found(string);

exception Graph_not_DAG;

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

let rec visit = (~node_id, ~adj_tbl, ~mark_tbl, ~list) => {
    if (Hashtbl.mem(mark_tbl, node_id)) {
        switch (Hashtbl.find(mark_tbl, node_id)) {
            | Temp => raise(Graph_not_DAG);
            | Perm => list;
        };
    }
    else {
        let neighbours = Hashtbl.find(adj_tbl, node_id);
        let visitNeighbour = (sorting, neighbour_id) => {
            visit(
            ~node_id=neighbour_id,
            ~adj_tbl=adj_tbl,
            ~mark_tbl=mark_tbl,
            ~list=sorting);
        };
        
        Hashtbl.add(mark_tbl, node_id, Temp);
        let list = List.fold_left(visitNeighbour, list, neighbours);
        Hashtbl.add(mark_tbl, node_id, Perm);

        List.append(list, [node_id]);
    };
};

let sort = adj_list => {
    let num_nodes = List.length(adj_list);
    let mark_tbl = Hashtbl.create(num_nodes);
    let adj_tbl = parseAdjList(adj_list);

    let traverse = (list, node) => {
        visit(
        ~node_id=node.id, 
        ~adj_tbl=adj_tbl,
        ~mark_tbl=mark_tbl,
        ~list=list);
    };

    let list = List.fold_left(traverse, [], adj_list);
    List.rev(list);
};