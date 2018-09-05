type node = {
    id: string,
    neighbours: list(string),
};

type edge = {
    tail: string,
    head: string,
    weight: int,
};

type directedGraph = list(node);

type resultType = {
    dist: Hashtbl.t(string, int), 
    prev: Hashtbl.t(string, option(string))
};

let search: (directedGraph, list(edge), string) => resultType;