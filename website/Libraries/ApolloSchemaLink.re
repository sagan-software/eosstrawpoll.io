[@bs.module "apollo-link-schema"] [@bs.new]
external make_ : {. "schema": GraphQl.schema} => ReasonApolloTypes.apolloLink =
  "SchemaLink";

let make = (~schema) => make_({"schema": schema});
