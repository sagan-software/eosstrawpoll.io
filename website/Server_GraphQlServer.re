module SubscriptionServer = {
  type t;
  [@bs.module "subscriptions-transport-ws"] [@bs.new]
  external make_ :
    (
      {
        .
        "execute": GraphQl.executeT,
        "subscribe": GraphQl.subscribeT,
        "schema": GraphQl.schema,
      },
      {
        .
        "server": Node_Http.t,
        "path": string,
      }
    ) =>
    t =
    "SubscriptionServer";
  let make = (~schema, ~server, ~path) =>
    make_(
      {
        "execute": GraphQl.execute,
        "subscribe": GraphQl.subscribe,
        "schema": schema,
      },
      {"server": server, "path": path},
    );
};

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let makeApolloClient = (~schema) =>
  ReasonApollo.createApolloClient(
    ~link=ApolloSchemaLink.make(~schema),
    ~cache=inMemoryCache,
    ~ssrMode=true,
    (),
  );
