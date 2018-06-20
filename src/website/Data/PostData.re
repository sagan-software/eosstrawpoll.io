type post = {
  id: int,
  text: string,
  created: int,
  parentId: int,
  parentAuthor: string,
};

let decode = json =>
  Json.Decode.{
    id: json |> field("id", int),
    text: json |> field("text", string),
    created: json |> field("created", int),
    parentId: json |> field("parent_id", int),
    parentAuthor: json |> field("parent_author", string),
  };

type t =
  | NotAsked
  | Loading
  | Success(array(post), bool)
  | Failure(string);

let fetch = (eos, author, ~lowerBound, ~upperBound, ~limit=50) =>
  Eos.getTableRows(
    eos,
    ~json=true,
    ~code=Env.codeName,
    ~scope=author,
    ~table="posts",
    ~tableKey="id",
    ~lowerBound,
    ~upperBound,
    ~limit,
  )
  |> Js.Promise.then_(result => {
       Js.log3("options", lowerBound, upperBound);
       Js.log2("post data result", result);
       Js.Promise.resolve(
         Success(
           result |. Eos.TableRows.rows |> Array.map(decode),
           result |. Eos.TableRows.more,
         ),
       );
     });
