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

    test("find", () => {
        let hash = setup();

        let e0 = find(hash, 0);
        let e1 = find(hash, 1);
        let e2 = find(hash, 2);
        let e3 = find(hash, 3);
        let e4 = find(hash, 4);
        let e5 = find(hash, 5);
        let e6 = find(hash, 6);
        let e7 = find(hash, 7);
        let e8 = find(hash, 8);

        expect((e0, e1, e2, e3, e4, e5, e6, e7, e8)) |> toEqual(
            ("0", "1", "2", "3", "4", "5", "6", "7", "8"));
    });

    test("add", () => {
        let hash = setup();

        add(hash, 3, "33");
        add(hash, 8, "88");

        let e3 = find(hash, 3);
        let e8 = find(hash, 8);

        expect((e3, e8)) |> toEqual(("33", "88"));
    });
});