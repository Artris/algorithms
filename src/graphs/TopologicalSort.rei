type node = {
    id: string,
    neighbours: list(string),
};

type directedGraph = list(node);

let sort: directedGraph => list(string);