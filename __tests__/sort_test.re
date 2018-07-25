open Jest;
open Expect;

describe("Merge Sort", () => {
    test("sort", () => {
        let arr = [|7,4,5,8,3,1,2,9,0,6|];
        let expected = [|0,1,2,3,4,5,6,7,8,9|];
        let result = Sort.Merge.sort((<), arr);
        expect(result) |> toEqual(expected);
    });
});