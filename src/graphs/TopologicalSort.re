type node = {
    id: string,
    children: list(string),
};

type directedGraph = list(node);

exception Invalid_node_id(string);

exception Graph_not_DAG;

let parseAdjList = adj_list => {
    let adj_tbl = Hashtbl.create(List.length(adj_list));
    let insert = ({id, children}) => {
        Hashtbl.add(adj_tbl, id, children);
    };

    List.iter(insert, adj_list);
    let validateChildren = node => {
        List.iter(child_id => {
            if (!Hashtbl.mem(adj_tbl, child_id)) {
                raise(Invalid_node_id(child_id));
            }
        }, node.children);
    };

    List.iter(validateChildren, adj_list);
    adj_tbl;
};

let rec visit = (~node_id, ~adj_tbl, ~visited, ~ordering, ~ancestors) => {
    if (Hashtbl.mem(visited, node_id)) {
        let pred = id => id == node_id;
        switch (List.find(pred, ancestors)) {
        | exception Not_found => ordering;
        | _ => raise(Graph_not_DAG);
        };
    }
    else {
        let ancestors = List.append(ancestors, [node_id]);
        let children = Hashtbl.find(adj_tbl, node_id);
        let visitChild = (ordering, child_id) => {
            visit(
            ~node_id=child_id,
            ~adj_tbl=adj_tbl,
            ~visited=visited,
            ~ordering=ordering,
            ~ancestors=ancestors);
        };
        
        Hashtbl.add(visited, node_id, node_id);
        let list = List.fold_left(visitChild, ordering, children);
        List.append(list, [node_id]);
    };
};

let sort = adj_list => {
    let num_nodes = List.length(adj_list);
    let adj_tbl = parseAdjList(adj_list);
    let visited = Hashtbl.create(num_nodes);

    let traverse = (ordering, node) => {
        visit(
        ~node_id=node.id, 
        ~adj_tbl=adj_tbl,
        ~visited=visited,
        ~ordering=ordering,
        ~ancestors=[]);
    };

    let top_sorting = List.fold_left(traverse, [], adj_list);
    List.rev(top_sorting);
};