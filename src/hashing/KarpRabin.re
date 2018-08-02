module CRH = RollingHash.Make({
    type t = char;
    let size = 256;
    let ord = Char.code;
});

let p = 101;

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

        let index = find(pattern_length, String.length(text) - pattern_length, f);
        switch index {
        | Some(index) => Some(index - pattern_length + 1)
        | None => None
        };
    };
};
