module Express = {
  [@bs.module "apollo-server-express"]
  external graphql_ : {. "schema": GraphQl.schema} => Express.Middleware.t =
    "graphqlExpress";
  let graphql = (~schema) => graphql_({"schema": schema});
  [@bs.module "apollo-server-express"]
  external graphiql_ :
    {
      .
      "endpointURL": string,
      "subscriptionsEndpoint": string,
    } =>
    Express.Middleware.t =
    "graphiqlExpress";
  let graphiql = (~endpointUrl, ~subscriptionsEndpoint) =>
    graphiql_({
      "endpointURL": endpointUrl,
      "subscriptionsEndpoint": subscriptionsEndpoint,
    });
};

[@bs.module "react-apollo"]
external renderToStringWithData :
  ReasonReact.reactElement => Js.Promise.t(string) =
  "";

[@bs.send]
external extract : ApolloClient.generatedApolloClient => Js.Json.t = "";
