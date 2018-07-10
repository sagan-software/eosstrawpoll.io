open MaterialUi;

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

module AccountState = {
  type t =
    | NoScatter
    | LoggedOut(Scatter.t)
    | LoggedIn(Scatter.t, string);

  let fromScatter = scatter =>
    switch (scatter) {
    | Some(scatter) =>
      switch (scatter |. Scatter.accountName) {
      | Some(accountName) => LoggedIn(scatter, accountName)
      | None => LoggedOut(scatter)
      }
    | None => NoScatter
    };
};

module AppHeader = {
  let login = (scatter, _event) =>
    scatter
    |. Scatter.getIdentity(~accounts=[|Env.scatterNetwork|], ())
    |> ignore;

  let logout = (scatter, _event) =>
    scatter |. Scatter.forgetIdentity |> ignore;

  let render = accountState =>
    <AppBar position=`Static>
      <Toolbar>
        <Grid container=true justify=`Space_Between alignItems=`Center>
          <Grid item=true xs=`V2>
            <Typography variant=`Title color=`Primary>
              <Link route=Route.Home>
                ("EOS Straw Poll" |> ReasonReact.string)
              </Link>
            </Typography>
          </Grid>
          <Grid item=true xs=`Auto>
            (
              switch (accountState) {
              | AccountState.NoScatter =>
                <Button color=`Inherit href="https://get-scatter.com/">
                  ("Get Scatter" |> ReasonReact.string)
                </Button>
              | AccountState.LoggedOut(scatter) =>
                <Button color=`Inherit onClick=(login(scatter))>
                  ("Login with Scatter" |> ReasonReact.string)
                </Button>
              | AccountState.LoggedIn(scatter, accountName) =>
                let route = Route.Profile(accountName);
                <Grid container=true alignItems=`Center spacing=Grid.V16>
                  <Grid item=true>
                    <Chip
                      avatar={
                        <Avatar
                          src={j|https://api.adorable.io/avatars/20/$accountName@eosstrawpoll|j}
                        />
                      }
                      label=(accountName |> ReasonReact.string)
                      onClick=(_e => route |> Route.redirectTo)
                    />
                  </Grid>
                  <Grid item=true>
                    <Button color=`Inherit onClick=(logout(scatter))>
                      ("Logout" |> ReasonReact.string)
                    </Button>
                  </Grid>
                </Grid>;
              }
            )
          </Grid>
        </Grid>
      </Toolbar>
    </AppBar>;
};

module AppFooter = {
  let render =
    <Grid container=true>
      <Grid item=true xs=`V3>
        <h3> ("Like EOS Straw Poll?" |> ReasonReact.string) </h3>
        <p>
          (
            "Please consider donating to help cover server costs and fund development. Thank you!"
            |> ReasonReact.string
          )
        </p>
        <form>
          <input type_="number" placeholder="1 EOS" />
          <Button> ("Donate " |> ReasonReact.string) </Button>
        </form>
      </Grid>
      <Grid item=true xs=`V3>
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
      </Grid>
      <Grid item=true xs=`V3>
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
      </Grid>
      <Grid item=true xs=`V3>
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
          <li> <a href="#steemit"> ("Steemit" |> ReasonReact.string) </a> </li>
          <li> <a href="#roadmap"> ("Roadmap" |> ReasonReact.string) </a> </li>
          <li>
            <Link route=Route.About> (ReasonReact.string("About")) </Link>
          </li>
        </ol>
      </Grid>
    </Grid>;
};

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
  didMount: self => {
    Scatter.onLoad(_event =>
      switch (Scatter.instance) {
      | Some(scatter) => self.send(ScatterLoaded(scatter))
      | None => ()
      }
    );
    Scatter.onLogout(_event => self.send(ChangeIdentity(None)));
    Scatter.onLogin(_event =>
      Scatter.instance
      |> Js.Option.andThen((. scatter) => scatter |. Scatter.identity)
      |. ChangeIdentity
      |> self.send
    );
  },
  render: self => {
    let context = self.state.context;
    <ReasonApollo.Provider client=apolloClient>
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
        <link
          rel="stylesheet"
          href="https://fonts.googleapis.com/css?family=Roboto:300,400,500"
        />
        <link
          rel="stylesheet"
          href="https://fonts.googleapis.com/icon?family=Material+Icons"
        />
      </Helmet>
      <CssBaseline />
      (AppHeader.render(AccountState.fromScatter(context.scatter)))
      (
        switch (self.state.route) {
        | Route.Home => <HomePage context />
        | Route.About => <AboutPage />
        | Route.Profile(accountName) => <ProfilePage context accountName />
        | Route.Poll(accountName, pollName) =>
          <PollPage context accountName pollName />
        | Route.PollResults(accountName, pollName) =>
          <PollResultsPage context accountName pollName />
        }
      )
      AppFooter.render
    </ReasonApollo.Provider>;
  },
};
