module type AlphabetType = {
    type t;
    let size: int;
    let ord: t => int;
};

module type S = {
    type sym;
    type t;
    let create: int => t;
    let append: (t, sym) => t;
    let skip: (t, sym) => t;
};

module Rolling_Hash = (Sym: AlphabetType): (S with type sym := Sym.t) => {
    type t = {
        u: int,
        d: int,
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
        u: 0,
        d: 0,
        p: p
    };

    let append = ({u, d, p}, c) => {
        u: (u * Sym.size + Sym.ord(c)) mod p,
        d: d + 1,
        p: p
    }

    let skip = ({u, d, p}, c) => {
        u: (u - Sym.ord(c) * pow(Sym.size, d - 1, p)) mod p,
        d: d - 1,
        p: p
    };
};


