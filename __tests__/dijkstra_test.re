open Jest;
open Expect;

describe("Breadth First Search", () => {
    open Dijkstra;

    let infinity = Pervasives.max_int;

    test("single node", () => {

        let adj_list = [{id: "A", neighbours: []}];

        let expected_dist = 0;
        let expected_prev = None;

        let {dist, prev} = search(adj_list, [],  "A");
        let dist = Hashtbl.find(dist, "A");
        let prev = Hashtbl.find(prev, "A");

        expect((dist, prev)) |> toEqual((expected_dist, expected_prev));
    });

    test("simple unidirectional cycle", () => {

        let adj_list = [
            {id: "A", neighbours: ["B"]},
            {id: "B", neighbours: ["C"]}, 
            {id: "C", neighbours: ["D"]}, 
            {id: "D", neighbours: ["A"]}];

        let weight_list = [
            {tail: "A", head: "B", weight: 1},
            {tail: "B", head: "C", weight: 1},
            {tail: "C", head: "D", weight: 1},
            {tail: "D", head: "A", weight: 1}]

        let expected_dists = (0, 1, 2, 3);
        let expected_prevs = (None, Some("A"), Some("B"), Some("C"));

        let {dist, prev} = search(adj_list, weight_list, "A");

        let dists = (
            Hashtbl.find(dist, "A"),
            Hashtbl.find(dist, "B"),
            Hashtbl.find(dist, "C"), 
            Hashtbl.find(dist, "D"));
        
        let prevs = (
            Hashtbl.find(prev, "A"),
            Hashtbl.find(prev, "B"),
            Hashtbl.find(prev, "C"), 
            Hashtbl.find(prev, "D"));

            expect((dists, prevs)) |> toEqual((expected_dists, expected_prevs));
    });
    
    test("complete biderectional graph", () => {

        let adj_list = [
            {id: "A", neighbours: ["B", "C", "D"]},
            {id: "B", neighbours: ["A", "C", "D"]}, 
            {id: "C", neighbours: ["A", "B", "D"]}, 
            {id: "D", neighbours: ["A", "B", "C"]}];

            let weight_list = [
                {tail: "A", head: "B", weight: 2},
                {tail: "A", head: "C", weight: 5},
                {tail: "A", head: "D", weight: 5},
                {tail: "B", head: "A", weight: 1},
                {tail: "B", head: "C", weight: 1},
                {tail: "B", head: "D", weight: 3},
                {tail: "C", head: "A", weight: 1},
                {tail: "C", head: "B", weight: 1},
                {tail: "C", head: "D", weight: 1},
                {tail: "D", head: "A", weight: 1},
                {tail: "D", head: "B", weight: 1},
                {tail: "D", head: "C", weight: 1}]
    
            let expected_dists = (0, 2, 3, 4);
            let expected_prevs = (None, Some("A"), Some("B"), Some("C"));
    
            let {dist, prev} = search(adj_list, weight_list, "A");
    
            let dists = (
                Hashtbl.find(dist, "A"),
                Hashtbl.find(dist, "B"),
                Hashtbl.find(dist, "C"), 
                Hashtbl.find(dist, "D"));
            
            let prevs = (
                Hashtbl.find(prev, "A"),
                Hashtbl.find(prev, "B"),
                Hashtbl.find(prev, "C"), 
                Hashtbl.find(prev, "D"));
    
                expect((dists, prevs)) |> toEqual((expected_dists, expected_prevs));
    });

    test("forest", () => {

        let adj_list = [
            {id: "A", neighbours: ["B"]},
            {id: "B", neighbours: ["A"]}, 
            {id: "C", neighbours: ["D"]}, 
            {id: "D", neighbours: ["C"]}];

        let weight_list = [
            {tail: "A", head: "B", weight: 1},
            {tail: "B", head: "A", weight: 1},
            {tail: "C", head: "D", weight: 1},
            {tail: "D", head: "C", weight: 1}]

        let expected_dists = (0, 1, infinity, infinity);
        let expected_prevs = (None, Some("A"), None, None);

        let {dist, prev} = search(adj_list, weight_list, "A");

        let dists = (
            Hashtbl.find(dist, "A"),
            Hashtbl.find(dist, "B"),
            Hashtbl.find(dist, "C"), 
            Hashtbl.find(dist, "D"));
        
        let prevs = (
            Hashtbl.find(prev, "A"),
            Hashtbl.find(prev, "B"),
            Hashtbl.find(prev, "C"), 
            Hashtbl.find(prev, "D"));

            expect((dists, prevs)) |> toEqual((expected_dists, expected_prevs));
    });
});