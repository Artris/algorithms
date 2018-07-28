type t('a);

exception InvalidArgument(string);
exception InconsistentState(string);
exception ArrayIsEmpty;

let create: unit => t('a);
let length: t('a) => int;
let get: (t('a), int) => 'a;
let set: (t('a), int, 'a) => unit;
let push: (t('a), 'a) => unit;
let pop: t('a) => 'a;
let swap: (t('a), int, int) => unit;
let inspect: t('a) => string;