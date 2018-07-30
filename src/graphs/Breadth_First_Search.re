type node = {
    id: string,
    neighbours: list(node),
};

type pair = (string, list(string));

let approx_num_nodes = 5;
let level: Hashtbl.t(string, int) = Hashtbl.create(approx_num_nodes);

let toHashTbl = pair_list => {
    let hashtbl_adj_list = Hashtbl.create(approx_num_nodes);
    let insert = pair => {
        let key = Pervasives.fst(pair);
        let value = Pervasives.snd(pair);
        Hashtbl.add(hashtbl_adj_list, key, value);
    };
    List.iter(insert, pair_list);
    hashtbl_adj_list;
};

let visit = (node_id, ~adj_tbl, ~current_level) => {
    let search_result = Hashtbl.find_all(level, node_id);
    let is_visited = List.length(search_result) > 0;
    if (!is_visited) {
        Hashtbl.add(level, node_id, current_level);
        let neighbours = Hashtbl.find(adj_tbl, node_id);
        neighbours;
    } else {
        ([]);
    }
};

let rec traverse = (frontier, adj_tbl, current_level) => {
    let frontier_empty = List.length(frontier) == 0;
    if (!frontier_empty) {
        let prev_frontier = frontier;
        let frontier = ref([]);

        let updateFrontier = (node_id) => {
            let visit = visit(~adj_tbl=adj_tbl, ~current_level=current_level);
            frontier := List.append(frontier^, visit(node_id));
        };
        List.iter(updateFrontier, prev_frontier);
        traverse(frontier^, adj_tbl, current_level + 1);
    };
};

let markNodeIfUnvisited = (key, value) => {
    let node_id = key;
    let search_result = Hashtbl.find_all(level, node_id);
    let is_visited = List.length(search_result) > 0;
    if (!is_visited) {
        Hashtbl.add(level, node_id, -1);
    }
};

let breadthFirstSearch = (adj_list, root_id) => {
    Hashtbl.reset(level);
    let adj_tbl = toHashTbl(adj_list);
    traverse([root_id], adj_tbl, 0);

    Hashtbl.iter(markNodeIfUnvisited, adj_tbl);
    level;
};