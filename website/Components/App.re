open Webapi.Dom;

module Cn = AppStyles;

type state = {
  context: Context.t,
  route: Route.route,
};

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

let component = ReasonReact.reducerComponent(__MODULE__);

let clickedLogin = ({ReasonReact.state} as self, scatter, _event) =>
  Scatter.getIdentity(scatter, ~accounts=[|Env.scatterNetwork|], ())
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
  initialState: () => {route, context: Context.initial},
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
      | Some(scatter) => self.send(ScatterLoaded(scatter))
      | None => ()
      }
    ),
  render: self => {
    let context = self.state.context;
    <ReasonApollo.Provider client=apolloClient>
      <div className=(Cn.container |> TypedGlamor.toString)>
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
            content=(self.state.route |> Route.toAbsolute)
          />
          <link rel="stylesheet" href="https://use.typekit.net/pix7uhg.css" />
        </Helmet>
        <header className=(Cn.headerContainer |> TypedGlamor.toString)>
          <div className=(Cn.header |> TypedGlamor.toString)>
            <Link
              className=(Cn.appLogo |> TypedGlamor.toString) route=Route.Home>
              (Cn.appLogoIcon |> TypedGlamor.toString |> Icon.eos)
              <strong> (ReasonReact.string("EOS Straw Poll")) </strong>
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
                  <nav className=(Cn.userNav |> TypedGlamor.toString)>
                    <Link route=(Route.Profile(name))>
                      <img
                        className=(Cn.userAvatar |> TypedGlamor.toString)
                        src={j|https://api.adorable.io/avatars/20/$name@eosstrawpoll|j}
                      />
                      (ReasonReact.string(name))
                    </Link>
                    <a> Icon.cog </a>
                    <a onClick=(clickedLogout(self, scatter))>
                      Icon.logout
                    </a>
                  </nav>;
                /* User has scatter but isn't logged in */
                | None =>
                  <a
                    className=(Cn.loginLink |> TypedGlamor.toString)
                    onClick=(clickedLogin(self, scatter))>
                    (ReasonReact.string("Login with Scatter"))
                  </a>
                }
              | None =>
                /* User does not have scatter */
                <a href="https://get-scatter.com/">
                  (ReasonReact.string("Get Scatter"))
                </a>
              }
            )
          </div>
        </header>
        (
          switch (self.state.route) {
          | Route.Home => <HomePage context />
          | Route.About => <AboutPage />
          | Route.Profile(accountName) => <ProfilePage context accountName />
          | Route.Poll(accountName, pollId) =>
            <PollPage context accountName pollId />
          | Route.PollResults(accountName, pollId) =>
            <PollResultsPage context accountName pollId />
          }
        )
        <footer className=(Cn.footerContainer |> TypedGlamor.toString)>
          <div className=(Cn.footer |> TypedGlamor.toString)>
            <div>
              <h3> ("Like EOS Straw Poll?" |> ReasonReact.string) </h3>
              <p>
                (
                  "Please consider donating to help cover server costs and fund development. Thank you!"
                  |> ReasonReact.string
                )
              </p>
              <form className=(Cn.donateForm |> TypedGlamor.toString)>
                <input
                  type_="number"
                  placeholder="1 EOS"
                  className=(Cn.donateInput |> TypedGlamor.toString)
                />
                <button
                  type_="submit"
                  className=(Cn.donateButton |> TypedGlamor.toString)>
                  ("Donate " |> ReasonReact.string)
                </button>
              </form>
            </div>
            <div>
              <h3> ("Top Donators" |> ReasonReact.string) </h3>
              <ol>
                <li>
                  <Link route=(Route.Profile("saganonroids"))>
                    ("saganonroids" |> ReasonReact.string)
                  </Link>
                  <code> ("20.1 EOS" |> ReasonReact.string) </code>
                </li>
                <li>
                  <Link route=(Route.Profile("saganonroids"))>
                    ("saganonroids" |> ReasonReact.string)
                  </Link>
                  <code> ("20.1 EOS" |> ReasonReact.string) </code>
                </li>
                <li>
                  <Link route=(Route.Profile("saganonroids"))>
                    ("saganonroids" |> ReasonReact.string)
                  </Link>
                  <code> ("20.1 EOS" |> ReasonReact.string) </code>
                </li>
                <li>
                  <Link route=(Route.Profile("saganonroids"))>
                    ("saganonroids" |> ReasonReact.string)
                  </Link>
                  <code> ("20.1 EOS" |> ReasonReact.string) </code>
                </li>
                <li>
                  <Link route=(Route.Profile("saganonroids"))>
                    ("saganonroids" |> ReasonReact.string)
                  </Link>
                  <code> ("20.1 EOS" |> ReasonReact.string) </code>
                </li>
              </ol>
            </div>
            <div>
              <h3> ("Recent Donations" |> ReasonReact.string) </h3>
              <ol>
                <li>
                  <Link route=(Route.Profile("saganonroids"))>
                    ("saganonroids" |> ReasonReact.string)
                  </Link>
                  <code> ("1 EOS" |> ReasonReact.string) </code>
                </li>
                <li>
                  <Link route=(Route.Profile("saganonroids"))>
                    ("saganonroids" |> ReasonReact.string)
                  </Link>
                  <code> ("1 EOS" |> ReasonReact.string) </code>
                </li>
                <li>
                  <Link route=(Route.Profile("saganonroids"))>
                    ("saganonroids" |> ReasonReact.string)
                  </Link>
                  <code> ("1 EOS" |> ReasonReact.string) </code>
                </li>
                <li>
                  <Link route=(Route.Profile("saganonroids"))>
                    ("saganonroids" |> ReasonReact.string)
                  </Link>
                  <code> ("1 EOS" |> ReasonReact.string) </code>
                </li>
                <li>
                  <Link route=(Route.Profile("saganonroids"))>
                    ("saganonroids" |> ReasonReact.string)
                  </Link>
                  <code> ("1 EOS" |> ReasonReact.string) </code>
                </li>
              </ol>
            </div>
            <div>
              <h3> ("Links" |> ReasonReact.string) </h3>
              <ol>
                <li>
                  <a href=("https://twitter.com/" ++ Env.twitterName)>
                    ("Twitter" |> ReasonReact.string)
                  </a>
                </li>
                <li>
                  <a href=("https://github.com/" ++ Env.twitterName)>
                    ("Github" |> ReasonReact.string)
                  </a>
                </li>
                <li>
                  <a href="#steemit"> ("Steemit" |> ReasonReact.string) </a>
                </li>
                <li>
                  <a href="#roadmap"> ("Roadmap" |> ReasonReact.string) </a>
                </li>
                <li>
                  <Link route=Route.About>
                    (ReasonReact.string("About"))
                  </Link>
                </li>
              </ol>
            </div>
          </div>
        </footer>
      </div>
    </ReasonApollo.Provider>;
  },
};
