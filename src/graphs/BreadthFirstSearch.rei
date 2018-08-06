type node = {
    id: string,
    neighbours: list(string),
};

type directedGraph = list(node);

type resultType = {
    level: Hashtbl.t(string, option(int)), 
    parent: Hashtbl.t(string, option(string))
};

let search: (directedGraph, string) => resultType;