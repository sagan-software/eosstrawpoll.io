module Database = Server_Database;

module DataGenerator = Server_DataGenerator;

module DataProcessor = Server_DataProcessor;

module GraphQlSchema = Server_GraphQlSchema;

module GraphQlServer = Server_GraphQlServer;

module WebServer = Server_WebServer;

let logger =
  Winston.make([|
    Winston.console(
      ~format=
        Winston.Format.(
          combine([|timestamp(), ms(), metadata(), cli(), simple()|])
        ),
    ),
  |]);

logger |. Winston.info("Starting server...", ());

logger |. Winston.debug("Connecting to MongoDB...", Env.mongoUri);

let promiseToResult = promise =>
  Js.Promise.(
    promise
    |> then_(d => resolve(Belt.Result.Ok(d)))
    |> catch(e => resolve(Belt.Result.Error(e)))
  );

Env.mongoUri
|> Mongo.Client.make
|> promiseToResult
|> Js.Promise.then_(mongo => {
     switch (mongo) {
     | Belt.Result.Ok(mongo) =>
       logger |. Winston.info("Connected to MongoDB", Env.mongoUri);
       let schema = GraphQlSchema.make(~mongo);
       let apolloClient = GraphQlServer.makeApolloClient(~schema);
       DataProcessor.start(~mongo, ~logger) |> ignore;
       WebServer.start(~apolloClient, ~schema, ~logger) |> ignore;
       DataGenerator.start(~mongo, ~logger) |> ignore;
     | Belt.Result.Error(err) =>
       logger |. Winston.error("Error connecting to MongoDB", err);
       Node.Process.exit(1);
     };
     Js.Promise.resolve();
   });
