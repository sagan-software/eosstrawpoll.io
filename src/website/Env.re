let codeName = "twitteos";

let localNetwork =
  Scatter.Network.make(
    ~protocol=`http,
    ~blockchain=`eos,
    ~host="127.0.0.1",
    ~port=8888,
  );

let network = localNetwork;
