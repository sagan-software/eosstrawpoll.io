let codeName = "eosstrawpoll";

let localNetwork =
  Scatter.Network.make(
    ~protocol=`http,
    ~blockchain=`eos,
    ~host="127.0.0.1",
    ~port=8888,
  );

let network = localNetwork;

let httpEndpoint = "http://127.0.01:8888";

let eosConfig = Eos.Config.t(~httpEndpoint, ());
