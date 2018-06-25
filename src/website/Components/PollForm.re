module ValidationResult = {
  type t =
    | Valid
    | Invalid(string);
};
