open TypedGlamor

let _global = begin
  global "*" [
    unsafe "boxSizing" "border-box";
    margin zero;
    padding zero;
  ];

  global "html" [
    fontSize (px 10);
  ];

  global "body" [
    backgroundColor Theme.Color.background;
    color Theme.Color.text;
    fontFamilies [
      "aktiv-grotesk";
      "-apple-system";
      "BlinkMacSystemFont";
      "Segoe UI";
      "Roboto";
      "Oxygen";
      "Ubuntu";
      "Cantarell";
      "Fira Sans";
      "Droid Sans";
      "Helvetica Neue";
      "sans-serif"
    ];
  ];

  global "*:focus" [
    outlineStyle none
  ];

  global "a" [
    color Theme.Color.link;
    textDecoration none;

  ];

  global "a:hover" [
    textDecoration underline;
  ];

  global "svg" [
    unsafe "fill" "currentColor";
  ];

  global "[id^=__lpform_input]" [
    display none;
  ]

end
