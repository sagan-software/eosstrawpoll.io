// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var Env$ReactTemplate = require("../Env.js");

function decode(json) {
  return /* record */[
          /* username */Json_decode.field("username", Json_decode.string, json),
          /* displayName */Json_decode.field("display_name", Json_decode.string, json),
          /* biography */Json_decode.field("biography", Json_decode.string, json),
          /* location */Json_decode.field("location", Json_decode.string, json),
          /* profilePhotoHash */Json_decode.field("profile_photo_hash", Json_decode.string, json),
          /* headerPhotoHash */Json_decode.field("header_photo_hash", Json_decode.string, json),
          /* numPosts */Json_decode.field("num_posts", Json_decode.$$int, json),
          /* numFollowing */Json_decode.field("num_following", Json_decode.$$int, json),
          /* numFollowers */Json_decode.field("num_followers", Json_decode.$$int, json),
          /* numLiked */Json_decode.field("num_liked", Json_decode.$$int, json),
          /* created */Json_decode.field("created", Json_decode.$$int, json),
          /* lastPostId */Json_decode.field("last_post_id", Json_decode.$$int, json)
        ];
}

function fetch(eos, author) {
  return eos.getTableRows(true, Env$ReactTemplate.codeName, author, "profile", "id", 0, -1, 1).then((function (result) {
                return Promise.resolve(/* Success */Block.__(0, [decode(Caml_array.caml_array_get(result.rows, 0))]));
              }));
}

exports.decode = decode;
exports.fetch = fetch;
/* Env-ReactTemplate Not a pure module */