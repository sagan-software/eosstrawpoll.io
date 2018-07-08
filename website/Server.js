// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Mongodb = require("mongodb");
var Process = require("process");
var Winston = require("winston");
var Winston$ReactTemplate = require("./External/Winston.js");
var Server_Database$ReactTemplate = require("./Server_Database.js");
var Server_WebServer$ReactTemplate = require("./Server_WebServer.js");
var Server_DataGenerator$ReactTemplate = require("./Server_DataGenerator.js");
var Server_DataProcessor$ReactTemplate = require("./Server_DataProcessor.js");
var Server_GraphQlSchema$ReactTemplate = require("./Server_GraphQlSchema.js");
var Server_GraphQlServer$ReactTemplate = require("./Server_GraphQlServer.js");

var logger = Winston$ReactTemplate.make("debug", /* array */[Winston$ReactTemplate.$$console(Winston$ReactTemplate.Format[/* combine */0](/* array */[
                Winston.format.timestamp(),
                Winston.format.ms(),
                Winston.format.metadata(),
                Winston.format.cli(),
                Winston.format.simple()
              ]))]);

logger.info("Starting server...", /* () */0);

logger.debug("Connecting to MongoDB...", process.env.MONGO_URI);

function promiseToResult(promise) {
  return promise.then((function (d) {
                  return Promise.resolve(/* Ok */Block.__(0, [d]));
                })).catch((function (e) {
                return Promise.resolve(/* Error */Block.__(1, [e]));
              }));
}

promiseToResult(Mongodb.MongoClient.connect(process.env.MONGO_URI)).then((function (mongo) {
        if (mongo.tag) {
          logger.error("Error connecting to MongoDB", mongo[0]);
          return Promise.resolve((Process.exit(1), /* () */0));
        } else {
          var mongo$1 = mongo[0];
          logger.info("Connected to MongoDB", process.env.MONGO_URI);
          var schema = Server_GraphQlSchema$ReactTemplate.make(mongo$1);
          var apolloClient = Server_GraphQlServer$ReactTemplate.makeApolloClient(schema);
          return Curry._1(Server_Database$ReactTemplate.Polls[/* collection */1], mongo$1).createIndex({
                        id: -1
                      }).then((function () {
                        Server_DataProcessor$ReactTemplate.start(mongo$1, logger);
                        Server_WebServer$ReactTemplate.start(apolloClient, schema, logger);
                        Server_DataGenerator$ReactTemplate.start(mongo$1, logger);
                        return Promise.resolve(/* () */0);
                      }));
        }
      }));

var Database = 0;

var DataGenerator = 0;

var DataProcessor = 0;

var GraphQlSchema = 0;

var GraphQlServer = 0;

var WebServer = 0;

exports.Database = Database;
exports.DataGenerator = DataGenerator;
exports.DataProcessor = DataProcessor;
exports.GraphQlSchema = GraphQlSchema;
exports.GraphQlServer = GraphQlServer;
exports.WebServer = WebServer;
exports.logger = logger;
exports.promiseToResult = promiseToResult;
/* logger Not a pure module */
