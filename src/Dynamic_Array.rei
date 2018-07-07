type t('a);

let create: unit => t('a);
let length: t('a) => int;
let get: (t('a), int) => 'a;
let set: (t('a), int, 'a) => unit;
let push: (t('a), 'a) => unit;
let pop: t('a) => 'a;
let inspect: t('a) => string;