open Jest;
open Expect;

describe("Dynamic Array", () => {
    test("length", () => {
        let dynamic_array = Dynamic_Array.create();
        Dynamic_Array.push(dynamic_array, 1);
        Dynamic_Array.push(dynamic_array, 2);
        Dynamic_Array.push(dynamic_array, 3);

        let length = Dynamic_Array.length(dynamic_array);
        expect(length) |> toBe(3);
    });

    test("get", () => {
        let dynamic_array = Dynamic_Array.create();
        Dynamic_Array.push(dynamic_array, 1);
        Dynamic_Array.push(dynamic_array, 2);
        Dynamic_Array.push(dynamic_array, 3);

        let thrid_element = Dynamic_Array.get(dynamic_array, 2);
        expect(thrid_element) |> toBe(3);
    });

    test("set", () => {
        let dynamic_array = Dynamic_Array.create();
        Dynamic_Array.push(dynamic_array, 1);
        Dynamic_Array.push(dynamic_array, 2);
        Dynamic_Array.push(dynamic_array, 3);

        Dynamic_Array.set(dynamic_array, 2, 5);

        let thrid_element = Dynamic_Array.get(dynamic_array, 2);
        expect(thrid_element) |> toBe(5);
    });
});