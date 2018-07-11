type t('a, 'b);

let create: (
    ~pre_hash: 'a => int,
    ~hash: int => int => int
) => t('a, 'b);

let find: (t('a, 'b), 'a) => 'b;
/* let remove: (t('a, 'b), 'a) => unit;
let length: t('a, 'b) => int; */