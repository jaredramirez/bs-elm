module R = Js.Result;

module D = Js.Dict;

module O = Js.Option;

/* DOM Manipulation */
[@bs.val] [@bs.return nullable] [@bs.scope "document"]
external getElementById : string => option(Dom.element) = "getElementById";

/* Elm Types */
type elmModule('instance);

type elmProgramBase('instance) = D.t(elmModule('instance));

type elmProgram = elmProgramBase({.});

type elmProgramWithPorts('ports) = elmProgramBase({. "ports": 'ports});

/* Elm Module External Functions */
[@bs.send] external fullscreen : elmModule('instance) => 'instance = "";

[@bs.send]
external fullscreenWithFlags : (elmModule('instance), 'flags) => 'instance =
  "fullscreen";

[@bs.send]
external embed : (elmModule('instance), Dom.element) => 'instance = "";

[@bs.send]
external embedWithFlags :
  (elmModule('instance), Dom.element, 'flags) => 'instance =
  "embed";

/* Ports Helper Types */
type elmInPort('data) = {
  .
  [@bs.meth] "subscribe": ('data => unit) => unit,
  [@bs.meth] "unsubscribe": unit => unit
};

type elmOutPort('data) = {. [@bs.meth] "send": 'data => unit};

/* Mount Program Functions*/
let mountHelper =
    (
      maybeFlags: option('flags),
      maybeElementId: option(string),
      module_: elmModule('instance)
    )
    : R.t('instance, string) =>
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
      elmProgram: elmProgramBase('instance)
    )
    : R.t('instance, string) => {
  let maybeModule = D.get(elmProgram, "Main");
  switch maybeModule {
  | Some(module_) => mountHelper(flags, elementId, module_)
  | None => R.Error("Module not found.")
  };
};
