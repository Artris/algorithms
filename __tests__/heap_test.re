open Jest;
open Expect;

describe("Heap", () => {  
    test("heap sort", () => {
        let heap = Heap.create((a, b) => a < b);
        Heap.add(heap, 9, "9");
        Heap.add(heap, 8, "8");
        Heap.add(heap, 7, "7");
        Heap.add(heap, 3, "3");
        Heap.add(heap, 2, "2");
        Heap.add(heap, 1, "1");
        Heap.add(heap, 6, "6");
        Heap.add(heap, 5, "5");
        Heap.add(heap, 4, "4");

        let e1 = Heap.extract(heap);
        let e2  = Heap.extract(heap);
        let e3  = Heap.extract(heap);
        let e4  = Heap.extract(heap);
        let e5  = Heap.extract(heap);
        let e6  = Heap.extract(heap);
        let e7  = Heap.extract(heap);
        let e8  = Heap.extract(heap);
        let e9  = Heap.extract(heap);

        expect((e1, e2, e3, e4, e5, e6, e7, e8, e9)) |> toEqual(
            ("1", "2", "3", "4", "5", "6", "7", "8", "9"));
    });
});