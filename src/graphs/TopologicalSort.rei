type node = {
    id: string,
    children: list(string),
};

type directedGraph = list(node);

let sort: directedGraph => list(string);