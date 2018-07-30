open Jest;
open Expect;

describe("Breadth First Search", () => {
    open Breadth_First_Search;

    test("single node", () => {

        let adj_list = [("node_1", [])];

        let expected = ("node_1", 0);
        let result_tbl = breadthFirstSearch(adj_list, "node_1");
        let result = ("node_1", Hashtbl.find(result_tbl, "node_1"));

        expect(result) |> toEqual(expected);
    });

    test("simple cycle", () => {

        let adj_list = [
            ("A", ["B", "D"]), 
            ("B", ["A", "C"]), 
            ("C", ["B", "D"]), 
            ("D", ["A", "C"])];

        let expected = (0, 1, 2, 1);

        let result_tbl = breadthFirstSearch(adj_list, "A");

        let a = Hashtbl.find(result_tbl, "A");
        let b = Hashtbl.find(result_tbl, "B");
        let c = Hashtbl.find(result_tbl, "C");
        let d = Hashtbl.find(result_tbl, "D");

        expect((a, b, c, d)) |> toEqual(expected);
    });
    
    test("complete graph", () => {

        let adj_list = [
            ("A", ["B", "C", "D"]), 
            ("B", ["A", "C", "D"]), 
            ("C", ["A", "B", "D"]), 
            ("D", ["A", "B", "C"])];

        let expected = (0, 1, 1, 1);

        let result_tbl = breadthFirstSearch(adj_list, "A");

        let a = Hashtbl.find(result_tbl, "A");
        let b = Hashtbl.find(result_tbl, "B");
        let c = Hashtbl.find(result_tbl, "C");
        let d = Hashtbl.find(result_tbl, "D");

        expect((a, b, c, d)) |> toEqual(expected);
    });

    test("forest", () => {

        let adj_list = [
            ("A", ["B"]), 
            ("B", ["A"]), 
            ("C", ["D"]), 
            ("D", ["C"])];

        let expected = (0, 1, -1, -1);

        let result_tbl = breadthFirstSearch(adj_list, "A");

        let a = Hashtbl.find(result_tbl, "A");
        let b = Hashtbl.find(result_tbl, "B");
        let c = Hashtbl.find(result_tbl, "C");
        let d = Hashtbl.find(result_tbl, "D");

        expect((a, b, c, d)) |> toEqual(expected);
    });
});