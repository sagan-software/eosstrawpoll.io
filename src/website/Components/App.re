open Webapi.Dom;

module Styles = AppStyles;

type state = {route: Route.route};

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
      <nav className=(Styles.primaryNav |> TypedGlamor.toString)>
        <AppLink current route=Route.Market label=Words.Market />
        <AppLink current route=Route.Governance label=Words.Games />
        <AppLink current route=Route.Governance label=Words.Governance />
        <AppLink current route=Route.Stats label=Words.Upload />
      </nav>,
  };
};

module SecondaryNav = {
  let component = ReasonReact.statelessComponent("SecondaryNav");
  let make = (~current, _children) => {
    ...component,
    render: _self =>
      <nav className=(Styles.secondaryNav |> TypedGlamor.toString)>
        <AppLink current route=Route.Stats label=Words.Stats />
        <AppLink current route=Route.About label=Words.About />
      </nav>,
  };
};

type action =
  | ChangeRoute(Route.route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  reducer,
  initialState: () => {route: Route.Home},
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          self.send(ChangeRoute(url |> Route.fromUrl))
        ),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
  didMount: _self =>
    Document.addEventListener(
      "scatterLoaded",
      _event => Js.log("scatter loaded"),
      document,
    ),
  render: self =>
    <div className=(Styles.box |> TypedGlamor.toString)>
      <header className=(Styles.header |> TypedGlamor.toString)>
        <Link
          className=(Styles.appLogo |> TypedGlamor.toString) route=Route.Home>
          (ReasonReact.string("TGFP"))
        </Link>
        <PrimaryNav current=self.state.route />
        <SecondaryNav current=self.state.route />
        <nav className=(Styles.userNav |> TypedGlamor.toString)>
          <a className=(Styles.loginLink |> TypedGlamor.toString) href="#">
            (ReasonReact.string("Login"))
          </a>
        </nav>
      </header>
      (
        switch (self.state.route) {
        | Route.Home => <HomePage />
        | Route.Market => <MarketPage />
        | Route.Treasury => <TreasuryPage />
        | Route.Governance => <GovernancePage />
        | Route.Stats => <StatsPage />
        | Route.About => <AboutPage />
        }
      )
    </div>,
};
