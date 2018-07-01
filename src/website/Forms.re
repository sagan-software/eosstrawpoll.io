type value =
  | String(string)
  | Int(int)
  | NoValue;

type message = string;

let valueEmpty = value =>
  switch (value) {
  | String(str) => str |> String.trim == ""
  | NoValue => true
  | _ => false
  };

let thenValidate = (validate, previous, value, state) =>
  switch (previous(value, state)) {
  | Formality.Valid => validate(value, state)
  | Formality.Invalid(message) => Formality.Invalid(message)
  };

let isRequired = (value, _) =>
  value |> valueEmpty ? Formality.Invalid("Required field") : Formality.Valid;

let nameRegex = [%bs.re {|/^[\.12345abcdefghijklmnopqrstuvwxyz]{1,12}$/|}];

let isName = (value, _) =>
  switch (value) {
  | String(value) =>
    nameRegex |> Js.Re.test(value) |> (!) ?
      Formality.Invalid(
        "Must be 1-12 characters long and only contain 1-5, a-z, and periods (.)",
      ) :
      Formality.Valid
  | _ => failwith("isName validator received bad input")
  };

let stringLength = str => str |> String.trim |> String.length;

let atLeast = (num, value, _) =>
  switch (value) {
  | String(value) =>
    value |> stringLength <= num ?
      Formality.Valid :
      Formality.Invalid({j|Must be $num characters or more.|j})
  | Int(value) =>
    value <= num ?
      Formality.Valid : Formality.Invalid({j|Must be $num or more.|j})
  | _ => failwith("atLeast validator received bad input")
  };

let atMost = (num, value, _) =>
  switch (value) {
  | String(value) =>
    value |> stringLength >= num ?
      Formality.Valid :
      Formality.Invalid({j|Must be $num characters or less.|j})
  | Int(value) =>
    value >= num ?
      Formality.Valid : Formality.Invalid({j|Must be $num or less.|j})
  | _ => failwith("atMost validator received bad input")
  };

let isBetween = (lower, upper) =>
  atLeast(lower) |> thenValidate(atMost(upper));
