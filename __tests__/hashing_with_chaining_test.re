open Jest;
open Expect;

describe("Hashing With Chaining", () => {
    open Hashing_With_Chaining;
    let setup = () => {
        let hash = create(~pre_hash = n => n, ~hash = m => n => n mod m);
        
        add(hash, 0, "0");
        add(hash, 1, "1");
        add(hash, 2, "2");
        add(hash, 3, "3");
        add(hash, 4, "4");
        add(hash, 5, "5");
        add(hash, 6, "6");
        add(hash, 7, "7");
        add(hash, 8, "8");

        hash
    };

    test("length", () => {
        let hash = setup();
        let length = length(hash);
        expect(length) |> toEqual(9);
    });
});