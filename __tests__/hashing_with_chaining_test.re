open Jest;
open Expect;
open Hashing;

describe("Hashing With Chaining", () => {
    open HashtblWithChaining;

    let rec range_upto =
        fun
        | 0 => []
        | n => [n, ...range_upto(n - 1)];
    
    let num_keys = 400;

    let keys = range_upto(num_keys);

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

    test("remove restores the previous mapping", () => {
        let hash = setup();

        add(hash, 17, "Hi");
        remove(hash, 17);
        let e17 = find(hash, 17);

        expect(e17) |> toEqual("17");
    });

    test("remove throws when the key doesn't exists", () => {
        let hash = setup();

        remove(hash, 17);
        
        expect(() => {
            remove(hash, 17);
        }) |> toThrowException(Key_not_found);
    });

    test("hash table maintains its complete history", () => {
        let key = 17;
        let values = range_upto(400);
        let hash = create(~pre_hash = n => n, ~hash = m => n => n mod m);
        List.iter(value => add(hash, key, value), values);

        let result = List.map(_ => {
            let value = find(hash, key);
            remove(hash, key);
            value;
        }, values);
        let expected = List.rev(values);
        
        expect(result) |> toEqual(expected);
    });
});