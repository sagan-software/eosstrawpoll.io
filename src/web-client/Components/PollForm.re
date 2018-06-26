type value = string;

type message = string;

type field =
  | Title
  | Option(int)
  | Whitelist
  | Blacklist
  | MinNumChoices
  | MaxNumChoices
  | OpenTime
  | CloseTime;

type state;
