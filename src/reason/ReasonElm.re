module R = Js.Result;

module D = Js.Dict;

module O = Js.Option;

/* DOM Manipulation */
[@bs.val] [@bs.return nullable] [@bs.scope "document"]
external getElementById : string => option(Dom.element) = "getElementById";

/* Elm Type */
type elmModule;

type elmInstance;

/* Elm Module External Functions */
[@bs.send] external fullscreen : elmModule => elmInstance = "";

[@bs.send]
external fullscreenWithFlags : (elmModule, 'flags) => elmInstance =
  "fullscreen";

[@bs.send] external embed : (elmModule, Dom.element) => elmInstance = "";

[@bs.send]
external embedWithFlags : (elmModule, Dom.element, 'flags) => elmInstance =
  "embed";

type elmProgram = D.t(elmModule);

/* Mount */
let mountHelper =
    (
      maybeFlags: option('flags),
      maybeElementId: option(string),
      module_: elmModule
    )
    : R.t(elmInstance, string) =>
  switch maybeElementId {
  | Some(elementId) =>
    let maybeElement = getElementById(elementId);
    switch maybeElement {
    | Some(element) =>
      switch maybeFlags {
      | Some(flags) => R.Ok(embedWithFlags(module_, element, flags))
      | None => R.Ok(embed(module_, element))
      }
    | None =>
      R.Error(
        "ReasonElm Error: Failed to DOM find element named '"
        ++ elementId
        ++ "' to embed."
      )
    };
  | None =>
    switch maybeFlags {
    | Some(flags) => R.Ok(fullscreenWithFlags(module_, flags))
    | None => R.Ok(fullscreen(module_))
    }
  };

let mount =
    (
      ~flags: option('flags)=?,
      ~elementId: option(string)=?,
      elmProgram: elmProgram
    )
    : R.t(elmInstance, string) => {
  let maybeModule = D.get(elmProgram, "Main");
  switch maybeModule {
  | Some(m) => mountHelper(flags, elementId, m)
  | None => R.Error("Module not found.")
  };
};
