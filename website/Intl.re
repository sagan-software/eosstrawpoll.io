include Intl_English;

let translate = (language, words) =>
  switch (language) {
  | _ => toEnglish(words)
  };
