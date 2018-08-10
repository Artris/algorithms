type node = {
    id: string,
    neighbours: list(string),
};

type directedGraph = list(node);

type resultType = {
    level: Hashtbl.t(string, option(int)),
    parent: Hashtbl.t(string, option(string))
};

exception Not_found(string);

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

let rec visit = (~node_id, ~adj_tbl, ~level, ~parent, ~current_level) => {
    if (!Hashtbl.mem(level, node_id)) {
        Hashtbl.add(level, node_id, Some(current_level));
        let neighbours = Hashtbl.find(adj_tbl, node_id);
        let markParent = neighbour_id => {
            if (!Hashtbl.mem(parent, neighbour_id)) {
                Hashtbl.add(parent, neighbour_id, Some(node_id));
            }
        };
        let markParentAndVisit = neighbour_id =>  {
            markParent(neighbour_id);
            visit(
            ~node_id=neighbour_id,
            ~adj_tbl=adj_tbl, 
            ~level=level,
            ~parent=parent,
            ~current_level=current_level + 1);
        };

        List.iter(markParentAndVisit, neighbours);
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
    let level = Hashtbl.create(num_nodes);
    let parent = Hashtbl.create(num_nodes);

    Hashtbl.add(parent, root_id, None);
    let adj_tbl = parseAdjList(adj_list);
    visit(
        ~node_id=root_id, 
        ~adj_tbl=adj_tbl, 
        ~level=level, 
        ~parent=parent, 
        ~current_level=0);
    
    let markNodeIfUnvisited = markNodeIfUnvisited(~level=level, ~parent=parent);
    Hashtbl.iter(markNodeIfUnvisited, adj_tbl);
    {level: level, parent: parent};
};