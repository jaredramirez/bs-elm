[@bs.send] external getElementById : string => option(Dom.element) = "";

type elmModule = {
  fullscreen: unit => unit,
  embed: Dom.element => unit
};

type elmApp = {main: elmModule};

[@bs.module] external elm : elmApp = "../elm/Main.elm";

Js.log("this is reason");
