open Jest;
open Expect;

describe("Dynamic Array", () => {
    open DynamicArray;

    let num_elements = 400;

    let gen_elements = n => {
        let rec gen =
            fun
            | -1 => []
            | n => [n, ...gen(n - 1)];
        
        List.rev(gen(n - 1));
    };
    
    let elements = gen_elements(num_elements);
    
    let setup = () => {
        let dynamic_array = create();
        List.iter(elm => push(dynamic_array, elm), elements);
        dynamic_array;
    };

    test("length", () => {
        let dynamic_array  = setup();
        
        let length = length(dynamic_array);
        
        expect(length) |> toBe(num_elements);
    });

    test("get", () => {
        let dynamic_array  = setup();
        
        let index = 133;
        let expected = 133;
        let result = get(dynamic_array, index);

        expect(result) |> toEqual(expected);
    });

    test("set", () => {
        let dynamic_array  = setup();
        
        let index = 71;
        let expected = -71;
        set(dynamic_array, index, expected)
        let result = get(dynamic_array, index);
        
        expect(result) |> toEqual(expected);
    });

    test("push", () => {
        let dynamic_array  = setup();
        
        let index = 400;
        let expected = 400; 
        push(dynamic_array, expected);
        let result = get(dynamic_array, index);

        expect(result) |> toEqual(expected);
    });

    test("pop", () => {
        let dynamic_array  = setup();

        let e399 = pop(dynamic_array);
        let e398 = pop(dynamic_array);

        expect((e398, e399)) |> toEqual((398, 399));
    });

    test("swap", () => {
        let dynamic_array  = setup();
        
        let a = 122;
        let b = 233;

        swap(dynamic_array, a, b);
        let a' = get(dynamic_array, a);
        let b' = get(dynamic_array, b);

        expect((a', b')) |> toEqual((b, a));
    });
});