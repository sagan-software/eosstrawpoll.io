type profile = {
  username: string,
  displayName: string,
  biography: string,
  location: string,
  profilePhotoHash: string,
  headerPhotoHash: string,
  numPosts: int,
  numFollowing: int,
  numFollowers: int,
  numLiked: int,
  created: int,
  lastPostId: int,
};

let decode = json =>
  Json.Decode.{
    username: json |> field("username", string),
    displayName: json |> field("display_name", string),
    biography: json |> field("biography", string),
    location: json |> field("location", string),
    profilePhotoHash: json |> field("profile_photo_hash", string),
    headerPhotoHash: json |> field("header_photo_hash", string),
    numPosts: json |> field("num_posts", int),
    numFollowing: json |> field("num_following", int),
    numFollowers: json |> field("num_followers", int),
    numLiked: json |> field("num_liked", int),
    created: json |> field("created", int),
    lastPostId: json |> field("last_post_id", int),
  };

type t =
  | NotAsked
  | Loading
  | Success(profile)
  | Failure(string);

let fetch = (eos, author) =>
  Eos.getTableRows(
    eos,
    ~json=true,
    ~code=Env.codeName,
    ~scope=author,
    ~table="profile",
    ~tableKey="id",
    ~lowerBound=0,
    ~upperBound=-1,
    ~limit=1,
  )
  |> Js.Promise.then_(result =>
       Js.Promise.resolve(
         Success((result |. Eos.TableRows.rows)[0] |> decode),
       )
     );
