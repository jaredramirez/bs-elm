module R = Js.Result;

module D = Js.Dict;

module O = Js.Option;

/* Get element by id from DOM */
[@bs.val] [@bs.return nullable] [@bs.scope "document"]
external getElementById : string => option(Dom.element) = "getElementById";

/* Abstract type to represent an Elm module */
type elmModule('instance);

/* Function to launch am Elm module in fullscreen mode */
[@bs.send] external fullscreen : elmModule('instance) => 'instance = "";

/* Function to launch am Elm module binding to a DOM element mode */
[@bs.send]
external fullscreenWithFlags : (elmModule('instance), 'flags) => 'instance =
  "fullscreen";

/* Function to launch am Elm module in fullscreen mode with flags*/
[@bs.send]
external embed : (elmModule('instance), Dom.element) => 'instance = "";

/* Function to launch am Elm module binding to a DOM element mode with flags */
[@bs.send]
external embedWithFlags :
  (elmModule('instance), Dom.element, 'flags) => 'instance =
  "embed";

/* Intance of Elm program */
type elmInstance = {.};

/* Intance of Elm program with ports */
type elmInstanceWithPorts('ports) = {. "ports": 'ports};

/* Type of an Elm port sending data from Elm to Reason */
type elmInPort('data) = {
  .
  [@bs.meth] "subscribe": ('data => unit) => unit,
  [@bs.meth] "unsubscribe": unit => unit
};

/* Type of an Elm port sending data from Reason to Elm */
type elmOutPort('data) = {. [@bs.meth] "send": 'data => unit};

/* Base type of an Elm program */
type elmProgramBase('instance) = D.t(elmModule('instance));

/* Type of an Elm program */
type elmProgram = elmProgramBase(elmInstance);

/* Type of an Elm program with ports on the instance */
type elmProgramWithPorts('ports) =
  elmProgramBase(elmInstanceWithPorts('ports));

/* Helper to mounting an Elm program */
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

/* Function mount an Elm program */
let mount =
    (
      ~flags: option('flags)=?,
      ~elementId: option(string)=?,
      ~moduleName: string="Main",
      elmProgram: elmProgramBase('instance)
    )
    : R.t('instance, string) => {
  let maybeModule = D.get(elmProgram, moduleName);
  switch maybeModule {
  | Some(module_) => mountHelper(flags, elementId, module_)
  | None => R.Error("Module not found.")
  };
};
