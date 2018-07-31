open Jest;
open Expect;

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

describe("Counting Sort", () => {
    test("sort", () => {
        let arr = [|7,4,5,8,3,1,2,9,0,6|];
        let expected = [|0,1,2,3,4,5,6,7,8,9|];
        let result = CountingSort.sort(arr);
        expect(result) |> toEqual(expected);
    });

    test("sort should handle duplicate elements", () => {
        let arr = [|4,4,4,4, 1, 3,3,3, 2,2|];
        let expected = [|1,2,2,3,3,3,4,4,4,4|];
        let result = CountingSort.sort(arr);
        expect(result) |> toEqual(expected);
    });
});

describe("Radix Sort", () => {
    test("sort", () => {
        let arr = [|7,4,5,8,3,1,2,9,0,6|];
        let expected = [|0,1,2,3,4,5,6,7,8,9|];
        let result = RadixSort.sort(arr, 10);
        expect(result) |> toEqual(expected);
    });

    test("sort should handle duplicate elements", () => {
        let arr = [|4,4,4,4, 1, 3,3,3, 2,2|];
        let expected = [|1,2,2,3,3,3,4,4,4,4|];
        let result = RadixSort.sort(arr, 10);
        expect(result) |> toEqual(expected);
    });
});