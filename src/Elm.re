module R = Belt.Result;

module D = Js.Dict;

module O = Js.Option;

/* Get element by id from DOM */
[@bs.val] [@bs.return nullable] [@bs.scope "document"]
external getElementById : string => option(Dom.element) = "getElementById";

/* Abstract type to represent an Elm module */
type elmModule('instance);

/* Type for init to take */
[@bs.deriving abstract]
type initOptions('flags) = {
  [@bs.optional]
  node: Dom.element,
  [@bs.optional]
  flags: 'flags,
};

/* Function to launch am Elm module */
[@bs.send]
external init : (elmModule('instance), initOptions('flags)) => 'instance =
  "";

/* Intance of Elm program */
type elmInstance = {.};

/* Intance of Elm program with ports */
type elmInstanceWithPorts('ports) = {. "ports": 'ports};

/* Type of an Elm port sending data from Elm to Reason */
type portFromElm('data) = {
  .
  [@bs.meth] "subscribe": ('data => unit) => unit,
  [@bs.meth] "unsubscribe": unit => unit,
};

/* Type of an Elm port sending data from Reason to Elm */
type portToElm('data) = {. [@bs.meth] "send": 'data => unit};

/* Base type of an Elm program */
type elmProgramBase('instance);

/* Type of an Elm program */
type elmProgram = elmProgramBase(elmInstance);

/* Type of an Elm program with ports on the instance */
type elmProgramWithPorts('ports) =
  elmProgramBase(elmInstanceWithPorts('ports));

/* Used to get modules from elmProgramBase */
[@bs.module] [@bs.return nullable]
external getModuleFromPath :
  (elmProgramBase('instance), string) => option(elmModule('instance)) =
  "lodash.get";

/* Helper to mounting an Elm program */
let mountHelper =
    (
      maybeFlags: option('flags),
      maybeElementId: option(string),
      module_: elmModule('instance),
    )
    : R.t('instance, string) => {
  let resultOptions =
    switch (maybeElementId, maybeFlags) {
    | (Some(elementId), Some(flags)) =>
      switch (getElementById(elementId)) {
      | Some(element) => R.Ok(initOptions(~node=element, ~flags, ()))
      | None => R.Error("Element with id '" ++ elementId ++ "' wasn't found.")
      }
    | (Some(elementId), None) =>
      switch (getElementById(elementId)) {
      | Some(element) => R.Ok(initOptions(~node=element, ()))
      | None => R.Error("Element with id '" ++ elementId ++ "' wasn't found.")
      }
    | (None, Some(flags)) => R.Ok(initOptions(~flags, ()))
    | (None, None) => R.Ok(initOptions())
    };
  R.map(resultOptions, options => init(module_, options));
};

/* Function mount an Elm program */
let mount =
    (
      ~flags: option('flags)=?,
      ~elementId: option(string)=?,
      ~moduleName: string="Main",
      elmProgram: elmProgramBase('instance),
    )
    : R.t('instance, string) => {
  let maybeModule = getModuleFromPath(elmProgram, "Elm." ++ moduleName);
  switch (maybeModule) {
  | Some(module_) => mountHelper(flags, elementId, module_)
  | None => R.Error("Module '" ++ moduleName ++ "' not found.")
  };
};
