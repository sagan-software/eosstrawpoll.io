let component = ReasonReact.statelessComponent("ProfilePage");

module AccountData = [%graphql
  {|
  query accountData($name: String!) {
    account(name:$name) {
      polls {
        id
        pollId
        pollCreator
        title
        openTime
        closeTime
        blockTime
      }
      votes {
        id
        pollId
        pollCreator
        blockTime
      }
      comments {
        id
        pollId
        pollCreator
        content
        blockTime
      }
    }
  }
|}
];

module AccountDataQuery = ReasonApollo.CreateQuery(AccountData);

let make = (~context: Context.t, ~accountName, _children) => {
  ...component,
  render: self => {
    let accountData = AccountData.make(~name=accountName, ());
    <div className=(AppStyles.main |> TypedGlamor.toString)>
      <Helmet>
        <title> (ReasonReact.string(accountName)) </title>
        <meta
          property="og:title"
          content={j|$accountName on EOS Straw Poll |j}
        />
        <meta
          property="og:description"
          content={j|$accountName has created 53 polls |j}
        />
        <meta property="og:type" content="profile" />
        <meta property="og:profile:username" content=accountName />
      </Helmet>
      <h1 className=(CommonStyles.pageHeader |> TypedGlamor.toString)>
        (ReasonReact.string(accountName))
      </h1>
      (ReasonReact.string("Profile"))
      <div>
        <AccountDataQuery variables=accountData##variables>
          ...(
               ({result}) =>
                 switch (result) {
                 | Loading => ReasonReact.string("Loading...")
                 | Error(error) =>
                   ReasonReact.string("Error: " ++ error##message)
                 | Data(response) =>
                   switch (response##account) {
                   | Some(account) =>
                     account##polls
                     |> Array.map(p =>
                          <div key=p##id>
                            <Link
                              route=(Route.Poll(p##pollCreator, p##pollId))>
                              (ReasonReact.string(p##title))
                            </Link>
                          </div>
                        )
                     |> ReasonReact.array
                   | None => ReasonReact.string("No polls created")
                   }
                 }
             )
        </AccountDataQuery>
      </div>
    </div>;
  },
};
