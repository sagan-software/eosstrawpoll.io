[@bs.val] [@bs.scope "window"]
external apolloData : ApolloInMemoryCache.inMemoryCacheRestoreData =
  "__APOLLO_STATE__";

let cache =
  ApolloInMemoryCache.createInMemoryCache()
  |> ApolloInMemoryCache.restore(apolloData);

let httpLink =
  ApolloLinks.createHttpLink(~uri="http://localhost:3001/graphql", ());

let wsLink =
  ApolloLinks.webSocketLink(
    ~uri="ws://localhost:3001/subscriptions",
    ~reconnect=true,
    (),
  );

let link =
  ApolloLinks.split(
    splitTest => {
      let mainDef = ApolloUtilities.getMainDefinition(splitTest##query);
      mainDef##kind == "OperationDefinition"
      && mainDef##operation == "subscription";
    },
    wsLink,
    httpLink,
  );

let apolloClient = ReasonApollo.createApolloClient(~link, ~cache, ());

ReactDOMRe.hydrateToElementWithId(<App apolloClient />, "app");

ReasonReact.Router.push("");
