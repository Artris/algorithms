open Jest;
open Expect;

describe("Topological Sort", () => {
    open TopologicalSort;

    test("single node", () => {
        let adj_list = [{id: "A", children: []}];
        let expected_sorting = ["A"];
        let sorting = sort(adj_list);

        expect(sorting) |> toEqual(expected_sorting);
    });

    test("simple tree", () => {

        let adj_list = [
            {id: "A", children: ["B"]},
            {id: "B", children: ["C"]}, 
            {id: "C", children: ["D"]}, 
            {id: "D", children: []}
            ];

            let expected_sorting = ["A", "B", "C", "D"];
            let sorting = sort(adj_list);
    
            expect(sorting) |> toEqual(expected_sorting);
    });
    
    test("star graph", () => {

        let adj_list = [
            {id: "A", children: []},
            {id: "B", children: ["A"]}, 
            {id: "C", children: ["A"]}, 
            {id: "D", children: ["A"]}];

            let expected_sorting = ["D", "C", "B", "A"];
            let sorting = sort(adj_list);
    
            expect(sorting) |> toEqual(expected_sorting);
    });

    test("forest", () => {

        let adj_list = [
            {id: "A", children: ["B"]},
            {id: "B", children: []}, 
            {id: "C", children: ["D"]}, 
            {id: "D", children: []}];

            let expected_sorting = ["C", "D", "A", "B"];
            let sorting = sort(adj_list);
    
            expect(sorting) |> toEqual(expected_sorting);
    });
});