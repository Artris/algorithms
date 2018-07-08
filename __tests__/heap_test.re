open Jest;
open Expect;

describe("Heap", () => {
    let heap = ref(Heap.create((a, b) => a < b));
    beforeEach(() => {
        heap := Heap.create((a, b) => a < b);
        let heap = heap^;

        Heap.add(heap, 9, "9");
        Heap.add(heap, 8, "8");
        Heap.add(heap, 7, "7");
        Heap.add(heap, 3, "3");
        Heap.add(heap, 2, "2");
        Heap.add(heap, 1, "1");
        Heap.add(heap, 6, "6");
        Heap.add(heap, 5, "5");
        Heap.add(heap, 4, "4");
    });

    test("size", () => {
        let heap = heap^;
        let heap_size = Heap.size(heap);

        expect(heap_size) |> toBe(9);
    });

    test("head", () => {
        let heap = heap^;
        let head = Heap.head(heap);

        expect(head) |> toBe("1");
    });

    test("decrease_root_priority", () => {
        let heap = heap^;
        Heap.decrease_root_priority(heap, 11);
        Heap.decrease_root_priority(heap, 12);
        Heap.decrease_root_priority(heap, 13);
        let head = Heap.head(heap);

        expect(head) |> toBe("4");
    });

    test("heap sort", () => {
        let heap = heap^;

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