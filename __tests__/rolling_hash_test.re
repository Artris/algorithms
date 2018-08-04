open Jest;
open Expect;

module IRH = RollingHash.Make({
    type t = int;
    let size = 10;
    let ord = t => t;
});

describe("Rolling Hash", () => {
    test("compare returns true when two hashs have seen the same sequence", () => {
        let h1 = IRH.create(101);
        let h2 = IRH.create(101);

        List.iter(n => IRH.append(h1, n), [0,1,2,3,4,5,6,7]);
        List.iter(n => IRH.append(h2, n), [0,1,2,3,4,5,6,7]);

        expect(IRH.compare(h1, h2)) |> toBe(true);
    });

    test("skips shifts the start of the sequence forward", () => {
        let h1 = IRH.create(101);
        let h2 = IRH.create(101);

        List.iter(n => IRH.append(h1, n), [3,4,5,6,7]);
        List.iter(n => IRH.append(h2, n), [0,1,2,3,4,5,6,7]);
        List.iter(n => IRH.skip(h2, n), [0,1,2]);

        expect(IRH.compare(h1, h2)) |> toBe(true);
    });

    test("compare returns false when two hashs hold different sequences", () => {
        let h1 = IRH.create(101);
        let h2 = IRH.create(101);

        List.iter(n => IRH.append(h1, n), [0,1,2,3,4,5,6,7]);
        List.iter(n => IRH.append(h2, n), [0,1,2,3,4,5,6]);

        expect(IRH.compare(h1, h2)) |> toBe(false);
    });
});
