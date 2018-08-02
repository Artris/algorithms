module type AlphabetType = {
    type t;
    let size: int;
    let ord: t => int;
};

module type S = {
    type sym;
    type t;
    let create: int => t;
    let append: (t, sym) => unit;
    let skip: (t, sym) => unit;
    let compare: (t, t) => bool;
};

module Rolling_Hash = (Sym: AlphabetType): (S with type sym := Sym.t) => {
    type t = {
        u: ref(int),
        d: ref(int),
        p: int
    };

    let pow = (a, n, m) => {
        let rec aux = (n, acc) => {
            switch n {
            | 0 => 1
            | _ => aux(n - 1, (acc * a) mod m)
            };
        };

        aux(n, 1);
    };

    let create = p => {
        u: ref(0),
        d: ref(0),
        p: p
    };

    let append = ({u, d, p}, c) => {
        u := (u^ * Sym.size + Sym.ord(c)) mod p;
        d := d^ + 1;
    }

    let skip = ({u, d, p}, c) => {
        u := (u^ - Sym.ord(c) * pow(Sym.size, d^ - 1, p)) mod p;
        d := d^ - 1;
    };

    let compare = (a, b) => a == b;
};

module AlphaNumeric = {
    type t = char;
    let size = 256;
    let ord = Char.code;
};

module Karp_Rabin = {
    module CRH = Rolling_Hash(AlphaNumeric);

    let find = (s, e, f) => {
        let rec aux = i => {
            if(i < e){
                switch (f(i)) {
                | true => Some(i)
                | false => aux(i + 1)
                };
            } else {
                None;
            };
        };

        aux(s);
    };

    let p = 101;

    let search = (pattern, text) => {
        let pattern_length = String.length(pattern);
        
        let rp = CRH.create(p);
        String.iter(CRH.append(rp), pattern);

        let rt = CRH.create(p);
        String.iter(CRH.append(rt), String.sub(text, 0, pattern_length));

        if(CRH.compare(rp, rt) && pattern == String.sub(text, 0, pattern_length)){
            Some(0);
        } else {
            let f = ind => {
                CRH.skip(rt, String.get(text, ind - pattern_length));
                CRH.append(rt, String.get(text, ind));
                CRH.compare(rt, rp) && pattern == String.sub(text, ind - pattern_length + 1, pattern_length);
            };

            find(pattern_length, String.length(text) - pattern_length, f);
        };
    };
};