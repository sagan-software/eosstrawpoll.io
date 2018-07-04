include Belt;

module Cn = HomePageStyles;

let component = ReasonReact.statelessComponent(__MODULE__);

module GetPolls = [%graphql
  {|
  query polls {
    polls {
      id
      pollId
      pollCreator
      title
      whitelist
      blacklist
      openTime
      closeTime
      options
      blockTime
    }
  }
|}
];

module GetPollsQuery = ReasonApollo.CreateQuery(GetPolls);

let make = (~context: Context.t, _children) => {
  ...component,
  render: _self =>
    <main className=(Cn.main |> TypedGlamor.toString)>
      <Helmet>
        <title> (ReasonReact.string("Home page")) </title>
        <meta property="og:title" content="EOS Straw Poll" />
        <meta property="og:description" content="Home page!!!" />
      </Helmet>
      <div className=(Cn.slogan |> TypedGlamor.toString)>
        ("Create " |> ReasonReact.string)
        <strong> ("instant, real-time polls" |> ReasonReact.string) </strong>
        (" on EOS" |> ReasonReact.string)
      </div>
      <div className=(Cn.content |> TypedGlamor.toString)>
        <div className=(Cn.form |> TypedGlamor.toString)>
          <PollForm context />
        </div>
        <GetPollsQuery>
          ...(
               ({result}) =>
                 switch (result) {
                 | Loading => ReasonReact.string("Loading...")
                 | Error(error) => ReasonReact.string(error##message)
                 | Data(response) =>
                   <div className=(Cn.pollLists |> TypedGlamor.toString)>
                     <div className=(Cn.pollList |> TypedGlamor.toString)>
                       <h2
                         className=(Cn.pollListTitle |> TypedGlamor.toString)>
                         ("Popular Polls" |> ReasonReact.string)
                       </h2>
                       (
                         response##polls
                         |> Js.Array.mapi((p, i) => {
                              let date =
                                p##blockTime ++ "Z" |> Js.Date.fromString;
                              <div
                                key=p##id
                                className=(Cn.poll |> TypedGlamor.toString)>
                                <h3
                                  className=(
                                    Cn.pollTitle |> TypedGlamor.toString
                                  )>
                                  <Link
                                    route=(
                                      Route.Poll(p##pollCreator, p##pollId)
                                    )>
                                    (ReasonReact.string(p##title))
                                  </Link>
                                </h3>
                                <p
                                  className=(
                                    Cn.pollInfo |> TypedGlamor.toString
                                  )>
                                  ("37 votes in 2 hours" |> ReasonReact.string)
                                </p>
                              </div>;
                            })
                         |> ReasonReact.array
                       )
                     </div>
                     <div className=(Cn.pollList |> TypedGlamor.toString)>
                       <h2
                         className=(Cn.pollListTitle |> TypedGlamor.toString)>
                         ("Recently Created" |> ReasonReact.string)
                       </h2>
                       (
                         response##polls
                         |> Js.Array.mapi((p, i) => {
                              let date =
                                p##blockTime ++ "Z" |> Js.Date.fromString;
                              <div
                                key=p##id
                                className=(Cn.poll |> TypedGlamor.toString)>
                                <h3
                                  className=(
                                    Cn.pollTitle |> TypedGlamor.toString
                                  )>
                                  <Link
                                    route=(
                                      Route.Poll(p##pollCreator, p##pollId)
                                    )>
                                    (ReasonReact.string(p##title))
                                  </Link>
                                </h3>
                                <p
                                  className=(
                                    Cn.pollInfo |> TypedGlamor.toString
                                  )>
                                  ("Created " |> ReasonReact.string)
                                  <DateFormat date />
                                  (ReasonReact.string(" by "))
                                  <Link
                                    route=(Route.Profile(p##pollCreator))
                                    className=(
                                      Cn.pollCreator |> TypedGlamor.toString
                                    )>
                                    (ReasonReact.string(p##pollCreator))
                                  </Link>
                                </p>
                              </div>;
                            })
                         |> ReasonReact.array
                       )
                     </div>
                     <div className=(Cn.pollList |> TypedGlamor.toString)>
                       <h2
                         className=(Cn.pollListTitle |> TypedGlamor.toString)>
                         ("Closing Soon" |> ReasonReact.string)
                       </h2>
                       (
                         response##polls
                         |> Js.Array.mapi((p, i) => {
                              let date =
                                p##blockTime ++ "Z" |> Js.Date.fromString;
                              <div
                                key=p##id
                                className=(Cn.poll |> TypedGlamor.toString)>
                                <h3
                                  className=(
                                    Cn.pollTitle |> TypedGlamor.toString
                                  )>
                                  <Link
                                    route=(
                                      Route.Poll(p##pollCreator, p##pollId)
                                    )>
                                    (ReasonReact.string(p##title))
                                  </Link>
                                </h3>
                                <p
                                  className=(
                                    Cn.pollInfo |> TypedGlamor.toString
                                  )>
                                  ("Closes in " |> ReasonReact.string)
                                  <DateFormat date />
                                </p>
                              </div>;
                            })
                         |> ReasonReact.array
                       )
                     </div>
                   </div>
                 }
             )
        </GetPollsQuery>
      </div>
    </main>,
};
