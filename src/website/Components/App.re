open Webapi.Dom;

module Styles = AppStyles;

type state = {
  eos: option(Eos.t),
  route: Route.route,
  identity: option(Scatter.Identity.t),
};

module AppLink = {
  let component = ReasonReact.statelessComponent("AppLink");
  let make = (~current, ~route, ~label, _children) => {
    ...component,
    render: _self => {
      let isSelected = current == route;
      let className = Styles.appLink(isSelected) |> TypedGlamor.toString;
      <Link className route>
        (ReasonReact.string(Words.translate(Words.English, label)))
      </Link>;
    },
  };
};

module PrimaryNav = {
  let component = ReasonReact.statelessComponent("PrimaryNav");
  let make = (~current, _children) => {
    ...component,
    render: _self =>
      <nav className=(Styles.primaryNav |> TypedGlamor.toString) />,
  };
};

module SecondaryNav = {
  let component = ReasonReact.statelessComponent("SecondaryNav");
  let make = (~current, _children) => {
    ...component,
    render: _self =>
      <nav className=(Styles.secondaryNav |> TypedGlamor.toString)>
        <AppLink current route=Route.About label=Words.About />
      </nav>,
  };
};

let temp = [%bs.raw {| window.Eos = require('eosjs') |}];

Js.log2("BALLS", temp);

type action =
  | ChangeRoute(Route.route)
  | LoadedEos(Eos.t)
  | ChangeIdentity(option(Scatter.Identity.t));

let reducer = (action, state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({...state, route})
  | LoadedEos(eos) => ReasonReact.Update({...state, eos: Some(eos)})
  | ChangeIdentity(identity) => ReasonReact.Update({...state, identity})
  };

let component = ReasonReact.reducerComponent("App");

let loadEos = ({ReasonReact.state} as self) => {
  let eos =
    Scatter.eos(Env.network, Eos.make, Eos.Config.t(~verbose=false), "http");
  self.send(LoadedEos(eos));
  %bs.raw
  {| window.eos = eos |};
  eos;
};

let clickedLogin = ({ReasonReact.state} as self, _event) => {
  Scatter.getIdentity(~accounts=[|Env.network|], ())
  |> Js.Promise.then_(identity => {
       Js.log(identity);
       self.send(ChangeIdentity(Some(identity)));
       let eos = loadEos(self);
       Eos.contract(eos, Env.codeName);
     })
  |> Js.Promise.then_(contract =>
       Twitteos.create(
         contract,
         Twitteos.Create.t(~author="alice", ~text="<h1>BALLS</h1>"),
         Eos.Action.options(~authorization=[|"alice@active"|], ()),
       )
     )
  |> Js.Promise.then_(result => {
       Js.log2("result", result);
       Js.Promise.resolve();
     });
  ();
};

let clickedLogout = ({ReasonReact.state} as self, _event) => {
  Scatter.forgetIdentity()
  |> Js.Promise.then_(_result => {
       self.send(ChangeIdentity(None));
       loadEos(self);
       Js.Promise.resolve();
     });
  ();
};

let make = _children => {
  ...component,
  reducer,
  initialState: () => {eos: None, route: Route.Home, identity: None},
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          self.send(ChangeRoute(url |> Route.fromUrl))
        ),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
  didMount: self =>
    Document.addEventListener(
      "scatterLoaded",
      event => {
        Js.log2("scatter loaded", event);
        Js.log2("network", Env.network);
        Scatter.suggestNetwork(Env.network)
        |> Js.Promise.then_(result => {
             Js.log2("suggest network", result);
             loadEos(self);
             Js.Promise.resolve();
           });
        ();
      },
      document,
    ),
  render: self =>
    <div className=(Styles.box |> TypedGlamor.toString)>
      <header className=(Styles.header |> TypedGlamor.toString)>
        <Link
          className=(Styles.appLogo |> TypedGlamor.toString) route=Route.Home>
          (ReasonReact.string("Twitteos"))
        </Link>
        <PrimaryNav current=self.state.route />
        <SecondaryNav current=self.state.route />
        <nav className=(Styles.userNav |> TypedGlamor.toString)>
          (
            switch (self.state.identity) {
            | Some(identity) =>
              let name =
                (identity |. Scatter.Identity.accounts)[0]
                |. Scatter.Account.name;
              <button onClick=(clickedLogout(self))>
                (ReasonReact.string({j|Logged in as $name|j}))
              </button>;
            | None =>
              <button
                className=(Styles.loginLink |> TypedGlamor.toString)
                onClick=(clickedLogin(self))>
                (ReasonReact.string("Login"))
              </button>
            }
          )
        </nav>
      </header>
      (
        switch (self.state.eos) {
        | Some(eos) =>
          switch (self.state.route) {
          | Route.Home => <HomePage />
          | Route.About => <AboutPage />
          | Route.Profile(accountName) => <ProfilePage accountName eos />
          | Route.Post(accountName, postId) => <PostPage accountName postId />
          }
        | None => ReasonReact.string("loading...")
        }
      )
    </div>,
};
