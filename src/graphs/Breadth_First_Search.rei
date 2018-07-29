type node = {
    id: string,
    mutable neighbours: list(node),
};

type pair = (string, list(string));

let breadthFirstSearch: (list(pair), string) => Hashtbl.t(string, int);