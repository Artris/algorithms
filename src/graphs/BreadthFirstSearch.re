type node = {
    id: string,
    neighbours: list(string),
};

type returnResult = {
    level: Hashtbl.t(string, option(int)),
    parent: Hashtbl.t(string, option(string))
};

exception NodeNotExist(string);

let parseAdjList = adj_list => {
    let adj_tbl = Hashtbl.create(List.length(adj_list));
    let insert = ({id, neighbours}) => {
        Hashtbl.add(adj_tbl, id, neighbours);
    };

    List.iter(insert, adj_list);
    let validateNeighbours = node => {
        List.iter(neighbour => {
            if (!Hashtbl.mem(adj_tbl, neighbour)) {
                raise(NodeNotExist(neighbour));
            }
        }, node.neighbours);
    };

    List.iter(validateNeighbours, adj_list);
    adj_tbl;
};

let visit = (node_id, ~adj_tbl, ~level, ~parent, ~current_level) => {
    if (!Hashtbl.mem(level, node_id)) {
        Hashtbl.add(level, node_id, Some(current_level));
        let neighbours = Hashtbl.find(adj_tbl, node_id);
        let markParent = neighbour_id => {
            if (!Hashtbl.mem(parent, neighbour_id)) {
                Hashtbl.add(parent, neighbour_id, Some(node_id));
            };
        };
        List.iter(markParent, neighbours);
        neighbours;   
    } else {
        ([]);
    }
};

let rec traverse = (frontier, adj_tbl, level, parent, current_level) => {
    let updateFrontier = (_, node_id) => {
        let visit = visit(
            ~adj_tbl = adj_tbl, 
            ~level = level,
            ~parent = parent,
            ~current_level = current_level);
        visit(node_id);
    };

    let frontier_empty = List.length(frontier) == 0;
    if (!frontier_empty) {
        let frontier = List.fold_left(updateFrontier, [], frontier);
        traverse(frontier, adj_tbl, level, parent, current_level + 1);
    }
};

let markNodeIfUnvisited = (node_id, _, ~level, ~parent) => {
    if (!Hashtbl.mem(level, node_id)) {
        Hashtbl.add(level, node_id, None);
        Hashtbl.add(parent, node_id, None);
    }
};

let search = (adj_list, root_id) => {
    let num_nodes = List.length(adj_list);
    let level: Hashtbl.t(string, option(int)) = Hashtbl.create(num_nodes);
    let parent: Hashtbl.t(string, option(string)) = Hashtbl.create(num_nodes);

    Hashtbl.add(parent, root_id, None);
    let adj_tbl = parseAdjList(adj_list);
    traverse([root_id], adj_tbl, level, parent, 0);
    
    let markNodeIfUnvisited = markNodeIfUnvisited(~level = level, ~parent = parent);
    Hashtbl.iter(markNodeIfUnvisited, adj_tbl);
    {level: level, parent: parent};
};