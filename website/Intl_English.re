include Intl_Types;

let toEnglish = words =>
  switch (words) {
  | Market => "Market"
  | Games => "Games"
  | Treasury => "Treasury"
  | Governance => "Governance"
  | Stats => "Accounts"
  | Login => "Login"
  | Upload => "Upload"
  | About => "About"
  };
