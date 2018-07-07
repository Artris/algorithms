type t('a, 'b);

let create: (('a, 'a) => bool) => t('a, 'b);
let add: (t('a, 'b), 'a, 'b) => unit;
let extract: t('a, 'b) => 'b;
let head: t('a, 'b) => 'b;
let size: t('a, 'b) => int;
let decrease_root_priority: (t('a, 'b), 'a) => unit;
let inspect: t('a, 'b) => string;
