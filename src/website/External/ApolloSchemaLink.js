// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var ApolloLinkSchema = require("apollo-link-schema");

function make(schema) {
  return new ApolloLinkSchema.SchemaLink({
              schema: schema
            });
}

exports.make = make;
/* apollo-link-schema Not a pure module */