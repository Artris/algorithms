open Jest;
open Expect;

describe("Dynamic Array", () => {
    let dynamic_array = ref(Dynamic_Array.create());
    beforeEach(() => {
        dynamic_array := Dynamic_Array.create();
        let dynamic_array = dynamic_array^;
        Dynamic_Array.push(dynamic_array, 1);
        Dynamic_Array.push(dynamic_array, 2);
        Dynamic_Array.push(dynamic_array, 3);
        Dynamic_Array.push(dynamic_array, 4);
        Dynamic_Array.push(dynamic_array, 5);
        Dynamic_Array.push(dynamic_array, 6);
        Dynamic_Array.push(dynamic_array, 7);
        Dynamic_Array.push(dynamic_array, 8);
    });

    test("length", () => {
        let dynamic_array  = dynamic_array^;
        let length = Dynamic_Array.length(dynamic_array);
        expect(length) |> toBe(8);
    });

    test("get", () => {
        let dynamic_array  = dynamic_array^;
        let e0 = Dynamic_Array.get(dynamic_array, 0);
        let e1 = Dynamic_Array.get(dynamic_array, 1);
        let e2 = Dynamic_Array.get(dynamic_array, 2);
        let e3 = Dynamic_Array.get(dynamic_array, 3);
        let e4 = Dynamic_Array.get(dynamic_array, 4);
        let e5 = Dynamic_Array.get(dynamic_array, 5);
        let e6 = Dynamic_Array.get(dynamic_array, 6);
        let e7 = Dynamic_Array.get(dynamic_array, 7);

        expect((e0, e1, e2, e3, e4, e5, e6, e7)) |> toEqual((1, 2, 3, 4, 5, 6, 7, 8));
    });

    test("set", () => {
        let dynamic_array  = dynamic_array^;
        Dynamic_Array.set(dynamic_array, 0, 10);
        Dynamic_Array.set(dynamic_array, 7, 11);
        Dynamic_Array.set(dynamic_array, 4, 44);

        let e0 = Dynamic_Array.get(dynamic_array, 0);
        let e7 = Dynamic_Array.get(dynamic_array, 7);
        let e4 = Dynamic_Array.get(dynamic_array, 4);
        expect((e0, e7, e4)) |> toEqual((10, 11, 44));
    });

    test("push", () => {
        let dynamic_array  = dynamic_array^;
        Dynamic_Array.push(dynamic_array, 9);
        let e8 = Dynamic_Array.get(dynamic_array, 8);
        expect(e8) |> toEqual(9);
    });

    test("pop", () => {
        let dynamic_array  = dynamic_array^;
        let e7 = Dynamic_Array.pop(dynamic_array);
        let e6 = Dynamic_Array.pop(dynamic_array);
        let e5 = Dynamic_Array.pop(dynamic_array);
        let e4 = Dynamic_Array.pop(dynamic_array);
        let e3 = Dynamic_Array.pop(dynamic_array);
        let e2 = Dynamic_Array.pop(dynamic_array);
        let e1 = Dynamic_Array.pop(dynamic_array);
        let e0 = Dynamic_Array.pop(dynamic_array);
        expect((e0, e1, e2, e3, e4, e5, e6, e7)) |> toEqual((1, 2, 3, 4, 5, 6, 7, 8));
    });
});