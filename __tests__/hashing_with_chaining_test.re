open Jest;
open Expect;

describe("Hashing With Chaining", () => {
    open Hashing_With_Chaining;

    let rec generate_keys =
        fun
        | 0 => []
        | n => [n, ...generate_keys(n - 1)];
    
    let num_keys = 400;

    let keys = generate_keys(num_keys);

    let setup = () => {
        let hash = create(~pre_hash = n => n, ~hash = m => n => n mod m);
        List.iter(key => add(hash, key, string_of_int(key)), keys);
        hash
    };

    test("length", () => {
        let hash = setup();

        let length = length(hash);

        expect(length) |> toEqual(num_keys);
    });

    test("find", () => {
        let hash = setup();

        let result = List.map(key => find(hash, key), keys);
        let expected = List.map(key => string_of_int(key), keys);

        expect(result) |> toEqual(expected);
    });

    test("add", () => {
        let hash = setup();

        add(hash, 17, "Hi");
        let e17 = find(hash, 17);

        expect(e17) |> toEqual("Hi");
    });
});