// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Scatter$ReactTemplate = require("./External/Scatter.js");

var isDev = process.env.NODE_ENV === "development";

var scatterNetwork = Scatter$ReactTemplate.Network[/* make */0](/* http */-988374136, /* eos */5047497, "127.0.0.1", 8888);

var eosConfig = {
  httpEndpoint: process.env.EOS_URL
};

exports.isDev = isDev;
exports.scatterNetwork = scatterNetwork;
exports.eosConfig = eosConfig;
/* isDev Not a pure module */