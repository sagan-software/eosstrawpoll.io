open MaterialUi;

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
      numVotes
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
      numVotes
    }
  }
|}
];

module PollList = {
  let renderPoll = p => {
    let date = p##blockTime ++ "Z" |> Js.Date.fromString;
    let numVotes = p##numVotes;
    <ListItem key=p##id>
      <ListItemText
        primary=(p##title |> ReasonReact.string)
        secondary=({j|$numVotes votes|j} |> ReasonReact.string)
      />
    </ListItem>;
  };

  let render = polls =>
    <Grid item=true xs=`V4>
      <Paper>
        <Typography variant=`Headline>
          ("Popular Polls" |> ReasonReact.string)
        </Typography>
        <List>
          (polls |> Js.Array.map(renderPoll) |> ReasonReact.array)
        </List>
      </Paper>
    </Grid>;
};

module GetPollsQuery = ReasonApollo.CreateQuery(GetPolls);

let make = (~context: Context.t, _children) => {
  ...component,
  render: _self =>
    <main>
      <Helmet>
        <title> (ReasonReact.string("Home page")) </title>
        <meta property="og:title" content="EOS Straw Poll" />
        <meta property="og:description" content="Home page!!!" />
      </Helmet>
      <Typography align=`Center variant=`Display3>
        ("Create " |> ReasonReact.string)
        <strong> ("instant, real-time polls" |> ReasonReact.string) </strong>
        (" on EOS" |> ReasonReact.string)
      </Typography>
      <PollForm context />
      <GetPollsQuery>
        ...(
             ({result}) =>
               switch (result) {
               | Loading => ReasonReact.string("Loading...")
               | Error(error) => ReasonReact.string(error##message)
               | Data(response) =>
                 <Grid container=true spacing=Grid.V16>
                   (PollList.render(response##popularPolls))
                   (PollList.render(response##newPolls))
                   (PollList.render(response##closingSoon))
                 </Grid>
               }
           )
      </GetPollsQuery>
    </main>,
};
