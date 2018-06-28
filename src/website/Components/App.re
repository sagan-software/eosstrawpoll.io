open Webapi.Dom;

module Styles = AppStyles;

type state = {
  context: Context.t,
  route: Route.route,
};

let temp = [%bs.raw {| global.Eos = require('eosjs') |}];

type action =
  | ChangeRoute(Route.route)
  | ChangeIdentity(option(Scatter.Identity.t))
  | ScatterLoaded(Scatter.Instance.t);

let reducer = (action, state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({...state, route})
  | ChangeIdentity(identity) =>
    ReasonReact.Update({
      ...state,
      context: {
        ...state.context,
        identity,
      },
    })
  | ScatterLoaded(scatter) =>
    ReasonReact.Update({
      ...state,
      context: {
        ...state.context,
        scatter: Some(scatter),
        identity: Scatter.identity(scatter),
      },
    })
  };

let component = ReasonReact.reducerComponent("App");

let clickedLogin = ({ReasonReact.state} as self, scatter, _event) =>
  Scatter.getIdentity(scatter, ~accounts=[|Env.network|], ())
  |> Js.Promise.then_(identity => {
       Js.log(identity);
       self.send(ChangeIdentity(Some(identity)));
       Js.Promise.resolve();
     })
  |> ignore;

let clickedLogout = ({ReasonReact.state} as self, scatter, _event) =>
  Scatter.forgetIdentity(scatter)
  |> Js.Promise.then_(_result => {
       self.send(ChangeIdentity(None));
       Js.Promise.resolve();
     })
  |> ignore;

let make = (~apolloClient, ~route=Route.Home, _children) => {
  ...component,
  reducer,
  initialState: () => {route, context: Context.empty},
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
    Scatter.onLoad(_event =>
      switch (Scatter.instance) {
      | Some(scatter) =>
        self.send(ScatterLoaded(scatter));
        Api.Contract.make(scatter)
        |> Js.Promise.then_(contract => Js.Promise.resolve())
        /* Api.create(
             contract,
             ~creator="alice",
             ~title="NEATO NEATO NEAT NEAT NEATO",
             ~options=[|"Choice A", "Choice B"|],
             (),
           ), */
        |> Js.Promise.then_(result => {
             Js.log2("Created", result);
             Js.Promise.resolve();
           })
        |> ignore;
      | None => ()
      }
    ),
  render: self => {
    let context = self.state.context;
    <ReasonApollo.Provider client=apolloClient>
      <div className=(Styles.container |> TypedGlamor.toString)>
        <Helmet>
          <html prefix="og: http://ogp.me/ns#" />
          <meta name="description" content="" />
          <meta
            name="viewport"
            content="width=device-width, initial-scale=1, shrink-to-fit=no"
          />
          <meta property="og:site_name" content="EOS Straw Poll" />
          <meta property="og:title" content="EOS Straw Poll" />
          <meta property="og:description" content="Straw polls on EOS!" />
          <meta
            property="og:url"
            content=(Route.toAbsolute(self.state.route))
          />
        </Helmet>
        <header className=(Styles.header |> TypedGlamor.toString)>
          <Link
            className=(Styles.appLogo |> TypedGlamor.toString)
            route=Route.Home>
            (ReasonReact.string("EOS Straw Poll"))
          </Link>
          (
            switch (context.scatter) {
            | Some(scatter) =>
              /* User has scatter */
              switch (context.identity) {
              | Some(identity) =>
                /* User has scatter and is logged in */
                let name =
                  (identity |. Scatter.Identity.accounts)[0]
                  |. Scatter.Account.name;
                <nav className=(Styles.userNav |> TypedGlamor.toString)>
                  <Link route=(Route.Profile(name))>
                    (ReasonReact.string(name))
                  </Link>
                  <button onClick=(clickedLogout(self, scatter))>
                    (ReasonReact.string("Logout"))
                  </button>
                </nav>;
              /* User has scatter but isn't logged in */
              | None =>
                <button
                  className=(Styles.loginLink |> TypedGlamor.toString)
                  onClick=(clickedLogin(self, scatter))>
                  (ReasonReact.string("Login"))
                </button>
              }
            | None =>
              /* User does not have scatter */
              <a href="https://get-scatter.com/">
                (ReasonReact.string("Get Scatter"))
              </a>
            }
          )
        </header>
        <main className=(Styles.main |> TypedGlamor.toString)>
          (
            switch (self.state.route) {
            | Route.Home => <HomePage context />
            | Route.About => <AboutPage />
            | Route.Profile(accountName) =>
              <ProfilePage context accountName />
            | Route.Poll(accountName, pollId) =>
              <PollPage context accountName pollId />
            | Route.PollResults(accountName, pollId) =>
              <PollResultsPage context accountName pollId />
            }
          )
        </main>
        <footer className=(Styles.footer |> TypedGlamor.toString)>
          <Link route=Route.About> (ReasonReact.string("About")) </Link>
        </footer>
      </div>
    </ReasonApollo.Provider>;
  },
};
