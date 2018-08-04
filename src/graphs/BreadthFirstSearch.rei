type node = {
    id: string,
    neighbours: list(string),
};
type returnResult = {
    level: Hashtbl.t(string, option(int)), 
    parent: Hashtbl.t(string, option(string))
};
let search: (list(node), string) => returnResult;