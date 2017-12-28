open Js.Result;

/* Elm Types */
type elmInstance = {. ports: string};

type elmModule = {
  .
  [@bs.meth] "fullscreen": unit => elmInstance,
  [@bs.meth] "embed": Dom.element => elmInstance
};

type elmApp = Js.Dict.t(elmModule);

/* DOM Manipulation */
[@bs.val]
external unsafeGetElementById : string => Js.null(Dom.element) =
  "document.getElementById";

let getElementById = (id: string) =>
  id |> unsafeGetElementById |> Js.Null.to_opt;

/* Make */
let make = (~elmApp: elmApp, ~moduleName: string, ~elementId=?, ()) => {
  let maybeElmModule = Js.Dict.get(elmApp, moduleName);
  switch maybeElmModule {
  | Some(elmModule) =>
    switch elementId {
    | Some(id) =>
      let maybeElement = getElementById(id);
      switch maybeElement {
      | Some(element) => Ok(elmModule##embed(element))
      | None =>
        Error(
          "ReasonElm Error: Failed to DOM find element named '"
          ++ id
          ++ "' to embed."
        )
      };
    | None => Ok(elmModule##fullscreen())
    }
  | None =>
    Error(
      "ReasonElm Error: Failed to find elm module named '"
      ++ moduleName
      ++ "'."
    )
  };
};
