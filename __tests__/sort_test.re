open Jest;
open Expect;
open Sort;

describe("Merge Sort", () => {
    test("sort", () => {
        let arr = [|7,4,5,8,3,1,2,9,0,6|];
        let expected = [|0,1,2,3,4,5,6,7,8,9|];
        let result = MergeSort.sort((<), arr);
        expect(result) |> toEqual(expected);
    });
});

describe("Insertion Sort", () => {
    test("sort", () => {
        let arr = [|7,4,5,8,3,1,2,9,0,6|];
        let expected = [|0,1,2,3,4,5,6,7,8,9|];
        let result = InsertionSort.sort((<), arr);
        expect(result) |> toEqual(expected);
    });
});