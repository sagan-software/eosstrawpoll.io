let renderPost = (post: PostData.post) =>
  <div key=(string_of_int(post.id))> (ReasonReact.string(post.text)) </div>;

type action =
  | ChangeProfileData(ProfileData.t)
  | ChangePostData(PostData.t);

type state = {
  eos: Eos.t,
  accountName: string,
  postData: PostData.t,
  profileData: ProfileData.t,
};

let reducer = (action, state) =>
  switch (action) {
  | ChangeProfileData(profileData) =>
    ReasonReact.Update({...state, profileData})
  | ChangePostData(postData) => ReasonReact.Update({...state, postData})
  };

let component = ReasonReact.reducerComponent("ProfilePage");

let numPerPage = 2;

let make = (~eos, ~accountName, _children) => {
  ...component,
  reducer,
  initialState: () => {
    eos,
    accountName,
    postData: PostData.NotAsked,
    profileData: ProfileData.NotAsked,
  },
  didMount: self => {
    self.send(ChangePostData(PostData.Loading));
    ProfileData.fetch(eos, accountName)
    |> Js.Promise.then_(profileData => {
         Js.log2("profileData", profileData);
         self.send(ChangeProfileData(profileData));
         switch (profileData) {
         | ProfileData.Success(profile) =>
           PostData.fetch(
             eos,
             accountName,
             ~lowerBound=Js.Math.max_int(0, profile.numPosts - numPerPage),
             ~upperBound=profile.numPosts,
             ~limit=numPerPage,
           )
           |> Js.Promise.then_(postData => {
                self.send(ChangePostData(postData));
                Js.Promise.resolve();
              });
           Js.Promise.resolve();
         | _ => Js.Promise.resolve()
         };
       });
    ();
  },
  render: self =>
    <div>
      <h1> (ReasonReact.string(accountName)) </h1>
      (ReasonReact.string("Profile"))
      <div>
        (
          switch (self.state.postData) {
          | PostData.NotAsked => ReasonReact.string("Loading...")
          | PostData.Loading => ReasonReact.string("Loading...")
          | PostData.Success(posts, more) =>
            <div>
              (posts |> Array.map(renderPost) |> ReasonReact.array)
              <p> (ReasonReact.string({j|Has more? $more |j})) </p>
            </div>
          | PostData.Failure(_message) =>
            ReasonReact.string("Failed to load")
          }
        )
      </div>
    </div>,
};
