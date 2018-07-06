[@bs.val] [@bs.scope "process.env"] external nodeEnv : string = "NODE_ENV";

[@bs.val] [@bs.scope "process.env"] external metadata : string = "APP_LABEL";

[@bs.val] [@bs.scope "process.env"]
external twitterName : string = "TWITTER_NAME";

[@bs.val] [@bs.scope "process.env"]
external githubName : string = "GITHUB_NAME";

[@bs.val] [@bs.scope "process.env"] external siteUrl : string = "SITE_URL";

[@bs.val] [@bs.scope "process.env"] external sitePort : string = "SITE_PORT";

[@bs.val] [@bs.scope "process.env"]
external siteWsUrl : string = "SITE_WS_URL";

[@bs.val] [@bs.scope "process.env"] external staticUrl : string = "STATIC_URL";

[@bs.val] [@bs.scope "process.env"] external eosUrl : string = "EOS_URL";

[@bs.val] [@bs.scope "process.env"]
external contractAccount : string = "CONTRACT_ACCOUNT";

[@bs.val] [@bs.scope "process.env"] external mongoUri : string = "MONGO_URI";

[@bs.val] [@bs.scope "process.env"]
external mongoAppDb : string = "MONGO_APP_DB";

[@bs.val] [@bs.scope "process.env"]
external mongoEosDb : string = "MONGO_EOS_DB";

[@bs.val] [@bs.scope "process.env"] external devPubKey : string = "DEV_PUBKEY";

[@bs.val] [@bs.scope "process.env"]
external devPrivKey : string = "DEV_PRIVKEY";

[@bs.val] [@bs.scope "process.env"]
external devAccounts : string = "DEV_ACCOUNTS";

[@bs.val] [@bs.scope "process.env"]
external devDataGenRate : string = "DEV_DATAGEN_RATE";

let isDev = nodeEnv == "development";

let scatterNetwork =
  Scatter.Network.make(
    ~protocol=`http,
    ~blockchain=`eos,
    ~host="127.0.0.1",
    ~port=8888,
  );

let eosConfig = Eos.Config.t(~httpEndpoint=eosUrl, ());
