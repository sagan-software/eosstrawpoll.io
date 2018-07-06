# EOS Straw Poll

## TODO

- Polish profile page
  - list of polls created
  - list of votes casted
  - list of comments posted
  - list of donations
  - if this is the current user's profile then
    - let them destroy polls
- Polish poll page
  - better looking voting options
  - show whitelist
  - show blacklist
  - show min/max number of choices
  - show poll creator
  - drag and drop choices to rank them
  - if this is the current user's poll then let them close it
  - comment form
  - comment list
- Polish profile results page
  - buttons for changing ranking algorithm
    - standard, tally up all the votes
    - staked, tally up the voter's staked voting power
    - ranked choice voting and instant run off
  - bar charts
  - if this is the current user's poll then let them close it
- Settings page
  - default whitelist
  - default blacklist
  - theme
- Polish home page
  - add advanced options to form
  - fix poll lists
    - popular polls list should rank polls by popularity
    - closing soon should show polls that have closed recently or are closing soon
  - donators lists
  - donation form
  - better validation error messages
  - better animations
- GraphQL subscriptions to keep everything up to date
- Better transitions between pages

## Notes

Score = (P-1) / (T+2)^G

where,
P = points of an item (and -1 is to negate submitters vote)
T = time since submission (in hours)
G = Gravity, defaults to 1.8 in news.arc

P = number of votes
T = hours since openTime
G = 1.8

db.polls.aggregate([
{$match: {openTime:{$lt: Date.now() / 1000}, closeTime: {$gt: Date.now() / 1000 - 60 _ 60 _ 24}}},
{$lookup: {from: "votes", localField: "id", foreignField: "pollRef", as: "votes"}},
{$addFields:{
denominator: {
$pow: [
{
$add: [
{
$divide: [
{
$subtract: [
Date.now() / 1000,
"$openTime"
]
},
60 \* 60
]
},
2
]
},
1.8
]
},
numVotes: {$size:"$votes"}
}},
{$addFields:{
score: {
$divide:[
"$numVotes","$denominator"
]
}
}},
{$sort:{score:-1}},
{$limit: 2},
{$project:{
\_id:"$\_id",
id:"$id",
pollId:"$pollId",
pollCreator:"$pollCreator",
title:"$title",
description:"$description",
options:"$options",
whitelist:"$whitelist",
blacklist:"$blacklist",
minChoices:"$minChoices",
maxChoices:"$maxChoices",
openTime:"$openTime",
closeTime:"$closeTime",
blockId:"$blockId",
blockNum:"$blockNum",
blockTime:"$blockTime",
trxId:"$trxId",
metadata:"$metadata",
numVotes:"$numVotes",
score:"$score"
}}
]).toArray()
