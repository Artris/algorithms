open Jest;
open Expect;

describe("Heap", () => {
    open Heap;

    let num_keys = 30;

    let gen_keys = n => {
        let rec gen =
            fun
            | -1 => []
            | n => [n, ...gen(n - 1)];
        
        gen(n - 1);
    };
    
    let keys = gen_keys(num_keys);
    
    let setup = () => {
        let heap = create((a, b) => a < b);
        List.iter(key => add(heap, key, string_of_int(key)), keys);
        heap;
    };

    test("size", () => {
        let heap = setup();

        let heap_size = size(heap);

        expect(heap_size) |> toBe(num_keys);
    });

    test("head", () => {
        let heap = setup();

        let head = head(heap);

        expect(head) |> toBe("0");
    });

    test("decrease_root_priority", () => {
        let heap = setup();

        decrease_root_priority(heap, 500);
        decrease_root_priority(heap, 501);
        decrease_root_priority(heap, 502);
        let head = head(heap);

        expect(head) |> toBe("3");
    });

    test("remove", () => {
        let heap = setup();

        let match = (_, value, ~match_value) => value == match_value;

        let removeSmallestN = n => {
            let rec rem =
                fun
                | -1 => ()
                | x => {
                    let value = string_of_int(x);
                    remove(heap, match(~match_value=value)) |> ignore;
                    rem(x-1);
                };
            rem(n-1);
        };

        removeSmallestN(10);
        
        let res1 = extract(heap);
        let res2 = extract(heap);
        let res3 = extract(heap);

        expect((res1, res2, res3)) |> toEqual(
            ("10", "11", "12"));
    });

    test("update", () => {
        let heap = setup();

        let match = (_, value, ~match_value) => value == match_value;

        let decrementSmallestN = n => {
            let rec rem =
                fun
                | -1 => ()
                | x => {
                    let value = string_of_int(x);
                    update(
                        heap, 
                        match(~match_value=value),
                        x-1,
                        string_of_int(x-1)) |> ignore;
                    rem(x-1);
                };
            rem(n-1);
        };

        decrementSmallestN(10);
        
        let res1 = extract(heap);
        let res2 = extract(heap);
        let res3 = extract(heap);

        expect((res1, res2, res3)) |> toEqual(
            ("-1", "0", "1"));
    });

    test("heap sort", () => {
        let heap = setup();

        let expected = List.map(key => string_of_int(key), List.rev(keys));
        let result = List.map(_key => extract(heap), keys);

        expect(result) |> toEqual(expected);
    });
});