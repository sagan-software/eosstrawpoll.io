/* [%bs.raw
     {|

   var MongoClient = require("mongodb").MongoClient;

   setTimeout(() => {
   	MongoClient.connect(
   		"mongodb://mongo-master:27017,mongo-slave1:27017,mongo-slave2:27017?replicaSet=rs",
   	).then(client => {
   		console.log("Connected to Mongo");
   		const db = client.db("EOS");
   		const actions = db.collection("actions");
   		const changeStream = actions.watch();
   		changeStream.on("change", function(change) {
   			console.log("CHANGE!", change);
   		});
   	});
   }, 20 * 1000);

   |}
   ]; */
module FullApp = {
  let component = ReasonReact.statelessComponent("FullApp");
  let make = _children => {
    ...component,
    render: _self => <App />,
    /* <div> (ReasonReact.string("Hello from Reason React")) </div>, */
  };
};

module Template = {
  let make = (~content, ~title, ()) => {j|<!DOCTYPE html>
	<html>
	<head>
		<title>$title</title>
	</head>
	<body>
		<div id="app">$content</div>
		<script src="/main.bundle.js"></script>
	</body>
	</html>
|j};
};

/* make the express app */
let app = Express.App.make();

/* Our initial rendering function, we will soon make this way better */
let renderHTML = (_next, _req, res) => {
  let content = ReactDOMServerRe.renderToString(<FullApp />);
  Express.Response.sendString(
    Template.make(~content, ~title="Server Rendering", ()),
    res,
  );
};

/* Express works on middleware and bs-express provides an easy way to make
   middleware out of functions */
renderHTML |> Express.Middleware.from |> Express.App.useOnPath(~path="/", app);

let port = 3000;

/* Getting a nice message when the server starts */
let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log("listening at localhost:" ++ string_of_int(port))
  };

/* starting up the express app */
Express.App.listen(app, ~onListen, ~port, ());
