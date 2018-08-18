open Jest;
open Expect;

describe("Topological Sort", () => {
    open TopologicalSort;

    test("single node", () => {
        let adj_list = [{id: "A", neighbours: []}];
        let expected_sorting = ["A"];
        let sorting = sort(adj_list);

        expect(sorting) |> toEqual(expected_sorting);
    });

    test("simple tree", () => {

        let adj_list = [
            {id: "A", neighbours: ["B"]},
            {id: "B", neighbours: ["C"]}, 
            {id: "C", neighbours: ["D"]}, 
            {id: "D", neighbours: []}
            ];

            let expected_sorting = ["A", "B", "C", "D"];
            let sorting = sort(adj_list);
    
            expect(sorting) |> toEqual(expected_sorting);
    });
    
    test("star graph", () => {

        let adj_list = [
            {id: "A", neighbours: []},
            {id: "B", neighbours: ["A"]}, 
            {id: "C", neighbours: ["A"]}, 
            {id: "D", neighbours: ["A"]}];

            let expected_sorting = ["D", "C", "B", "A"];
            let sorting = sort(adj_list);
    
            expect(sorting) |> toEqual(expected_sorting);
    });

    test("forest", () => {

        let adj_list = [
            {id: "A", neighbours: ["B"]},
            {id: "B", neighbours: []}, 
            {id: "C", neighbours: ["D"]}, 
            {id: "D", neighbours: []}];

            let expected_sorting = ["C", "D", "A", "B"];
            let sorting = sort(adj_list);
    
            expect(sorting) |> toEqual(expected_sorting);
    });
});