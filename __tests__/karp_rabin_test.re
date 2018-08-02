open Jest;
open Expect;

describe("Karp Rabin", () => {
    test("search returns the start index of the pattern in the text when text has the pattern", () => {
        let text = "OMG Karp Rabin works!";
        let pattern = "Rabin";
        let index = KarpRabin.search(pattern, text);
        expect(index) |> toEqual(Some(9));
    });

    test("search returns None when the pattern is not in the text", () => {
        let text = "OMG Karp Rabin works!";
        let pattern = "X";
        let index = KarpRabin.search(pattern, text);
        expect(index) |> toEqual(None);
    });
});
