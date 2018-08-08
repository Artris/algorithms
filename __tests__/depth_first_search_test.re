open Jest;
open Expect;

describe("Depth First Search", () => {
    open DepthFirstSearch;

    test("single node", () => {

        let adj_list = [{id: "A", neighbours: []}];

        let expected_level = Some(0);
        let expected_parent = None;

        let {level, parent} = search(adj_list, "A");
        let level = Hashtbl.find(level, "A");
        let parent = Hashtbl.find(parent, "A");

        expect((level, parent)) |> toEqual((expected_level, expected_parent));
    });

    test("simple cycle", () => {

        let adj_list = [
            {id: "A", neighbours: ["B", "D"]},
            {id: "B", neighbours: ["A", "C"]}, 
            {id: "C", neighbours: ["B", "D"]}, 
            {id: "D", neighbours: ["A", "C"]}];

        let expected_levels = (Some(0), Some(1), Some(2), Some(3));
        let expected_parents = (None, Some("A"), Some("B"), Some("C"));

        let {level, parent} = search(adj_list, "A");

        let levels = (
            Hashtbl.find(level, "A"),
            Hashtbl.find(level, "B"),
            Hashtbl.find(level, "C"), 
            Hashtbl.find(level, "D"));
        
        let parents = (
            Hashtbl.find(parent, "A"),
            Hashtbl.find(parent, "B"),
            Hashtbl.find(parent, "C"), 
            Hashtbl.find(parent, "D"));

            expect((levels, parents)) |> toEqual((expected_levels, expected_parents));
    });
    
    test("complete graph", () => {

        let adj_list = [
            {id: "A", neighbours: ["B", "C", "D"]},
            {id: "B", neighbours: ["A", "C", "D"]}, 
            {id: "C", neighbours: ["A", "B", "D"]}, 
            {id: "D", neighbours: ["A", "B", "C"]}];

        let expected_levels = (Some(0), Some(1), Some(2), Some(3));
        let expected_parents = (None, Some("A"), Some("B"), Some("C"));

        let {level, parent} = search(adj_list, "A");

        let levels = (
            Hashtbl.find(level, "A"),
            Hashtbl.find(level, "B"),
            Hashtbl.find(level, "C"), 
            Hashtbl.find(level, "D"));
        
        let parents = (
            Hashtbl.find(parent, "A"),
            Hashtbl.find(parent, "B"),
            Hashtbl.find(parent, "C"), 
            Hashtbl.find(parent, "D"));

            expect((levels, parents)) |> toEqual((expected_levels, expected_parents));
    });

    test("forest", () => {

        let adj_list = [
            {id: "A", neighbours: ["B"]},
            {id: "B", neighbours: ["A"]}, 
            {id: "C", neighbours: ["D"]}, 
            {id: "D", neighbours: ["C"]}];

        let expected_levels = (Some(0), Some(1), None, None);
        let expected_parents = (None, Some("A"), None, None);

        let {level, parent} = search(adj_list, "A");

        let levels = (
            Hashtbl.find(level, "A"),
            Hashtbl.find(level, "B"),
            Hashtbl.find(level, "C"), 
            Hashtbl.find(level, "D"));
        
        let parents = (
            Hashtbl.find(parent, "A"),
            Hashtbl.find(parent, "B"),
            Hashtbl.find(parent, "C"), 
            Hashtbl.find(parent, "D"));

        expect((levels, parents)) |> toEqual((expected_levels, expected_parents));
    });
});