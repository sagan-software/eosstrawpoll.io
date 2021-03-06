// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Graphql = require("graphql");
var ReasonApollo = require("reason-apollo/src/ReasonApollo.bs.js");
var ApolloInMemoryCache = require("reason-apollo/src/ApolloInMemoryCache.bs.js");
var SubscriptionsTransportWs = require("subscriptions-transport-ws");
var ApolloSchemaLink$ReactTemplate = require("./External/ApolloSchemaLink.js");

function make(schema, server, path) {
  return new SubscriptionsTransportWs.SubscriptionServer({
              execute: Graphql.execute,
              subscribe: Graphql.subscribe,
              schema: schema
            }, {
              server: server,
              path: path
            });
}

var SubscriptionServer = /* module */[/* make */make];

var inMemoryCache = ApolloInMemoryCache.createInMemoryCache(/* None */0, /* None */0, /* () */0);

function makeApolloClient(schema) {
  return ReasonApollo.createApolloClient(ApolloSchemaLink$ReactTemplate.make(schema), inMemoryCache, /* Some */[true], /* None */0, /* None */0, /* None */0, /* () */0);
}

exports.SubscriptionServer = SubscriptionServer;
exports.inMemoryCache = inMemoryCache;
exports.makeApolloClient = makeApolloClient;
/* inMemoryCache Not a pure module */
