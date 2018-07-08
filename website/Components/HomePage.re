include Belt;

module Cn = HomePageStyles;

let component = ReasonReact.statelessComponent(__MODULE__);

module GetPolls = [%graphql
  {|
  query polls {
    popularPolls: polls(sortBy: POPULARITY) {
      id
      pollName
      pollCreator
      title
      whitelist
      blacklist
      openTime
      closeTime
      blockTime
      numVotes
    }
    newPolls: polls {
      id
      pollName
      pollCreator
      title
      whitelist
      blacklist
      openTime
      closeTime
      blockTime
    }
    closingSoon: polls(sortBy: CLOSING) {
      id
      pollName
      pollCreator
      title
      whitelist
      blacklist
      openTime
      closeTime
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
                         response##popularPolls
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
                                      Route.Poll(p##pollCreator, p##pollName)
                                    )>
                                    (ReasonReact.string(p##title))
                                  </Link>
                                </h3>
                                <p
                                  className=(
                                    Cn.pollInfo |> TypedGlamor.toString
                                  )>
                                  (
                                    string_of_int(p##numVotes)
                                    ++ " votes"
                                    |> ReasonReact.string
                                  )
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
                         response##newPolls
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
                                      Route.Poll(p##pollCreator, p##pollName)
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
                         response##closingSoon
                         |> Js.Array.mapi((p, i) => {
                              let date =
                                float_of_int(p##closeTime)
                                *. 1000.
                                |> Js.Date.fromFloat;
                              Js.log3("!!!!!!!!!!!", date, p);
                              <div
                                key=p##id
                                className=(Cn.poll |> TypedGlamor.toString)>
                                <h3
                                  className=(
                                    Cn.pollTitle |> TypedGlamor.toString
                                  )>
                                  <Link
                                    route=(
                                      Route.Poll(p##pollCreator, p##pollName)
                                    )>
                                    (ReasonReact.string(p##title))
                                  </Link>
                                </h3>
                                <p
                                  className=(
                                    Cn.pollInfo |> TypedGlamor.toString
                                  )>
                                  ("Closes " |> ReasonReact.string)
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
