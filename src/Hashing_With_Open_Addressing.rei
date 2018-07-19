type t('a, 'b);

let create: (
    ~pre_hash: 'a => int,
    ~hash: (int, int, int) => int
) => t('a, 'b);

exception Not_found;
exception Inconsistent_state;

let find: (t('a, 'b), 'a) => 'b;
let add: (t('a, 'b), 'a, 'b) => unit;
let remove: (t('a, 'b), 'a) => unit;
let iter: (('a, 'b) => unit, t('a, 'b)) => unit;
let length: t('a, 'b) => int;