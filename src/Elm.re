module R = Belt.Result;

/* Get element by id from DOM */
[@bs.val] [@bs.return nullable] [@bs.scope "document"]
external getElementById: string => option(Dom.element) = "getElementById";

/* Abstract type to represent an Elm module */
type elmModule('runtime);

/* Abstract type to represent an Elm program */
type elmProgramBase('runtime);

/* Abstract type to represent an Elm program without ports */
type elmRuntime = unit;
type elmProgram = elmProgramBase(elmRuntime);

/* Abstract type to represent an Elm program with ports */
type elmRuntimeWithPorts('ports) = {ports: 'ports};
type elmProgramWithPorts('ports) =
  elmProgramBase(elmRuntimeWithPorts('ports));

/* Type to represent a port to recieve data in Reason from Elm */
type elmToReasonPort('dataForReason) = {
  subscribe: ('dataForReason => unit) => unit,
  unsubscribe: unit => unit,
};

/* Type to represent a port to send data to Elm from Reason */
type reasonToElmPort('dataForElm) = {send: 'dataForElm => unit};

/* Type for init to take */
type initOptions('flags) = {
  [@bs.as "node"]
  optNode: option(Dom.element),
  [@bs.as "flags"]
  optFlags: option('flags),
};

/* Function to launch am Elm module */
[@bs.send]
external init: (elmModule('runtime), initOptions('flags)) => 'runtime =
  "init";

/* Helper to mounting an Elm program */
let mountHelper =
    (
      ~optFlags: option('flags),
      ~optElementId: option(string),
      ~module_: elmModule('runtime),
    )
    : R.t('runtime, string) => {
  let nodeResult =
    switch (optElementId) {
    | Some(elementId) =>
      switch (getElementById(elementId)) {
      | Some(node) => R.Ok(Some(node))
      | None => R.Error("Element with id '" ++ elementId ++ "' wasn't found.")
      }
    | None => R.Ok(None)
    };
  R.map(nodeResult, optNode => init(module_, {optNode, optFlags}));
};

/* Used to get modules from elmProgramBase */
[@bs.module] [@bs.return nullable]
external lodashGet:
  (elmProgramBase('runtime), string) => option(elmModule('runtime)) =
  "lodash.get";

let getModuleFromPath =
    (elmProgram: elmProgramBase('runtime), moduleName: string)
    : option(elmModule('runtime)) =>
  switch (lodashGet(elmProgram, moduleName)) {
  | None =>
    /* If imported via bs.module, we might need to specify "Elm." to get
       the module correctly */
    lodashGet(elmProgram, "Elm." ++ moduleName)
  | Some(elmModule_) => Some(elmModule_)
  };

/* Function mount an Elm program */
let mount =
    (
      ~flags: option('flags)=?,
      ~elementId: option(string)=?,
      ~moduleName: string="Main",
      elmProgram: elmProgramBase('runtime),
    )
    : R.t('runtime, string) => {
  let optModule = getModuleFromPath(elmProgram, moduleName);
  switch (optModule) {
  | Some(module_) =>
    mountHelper(~optFlags=flags, ~optElementId=elementId, ~module_)
  | None => R.Error("Module '" ++ moduleName ++ "' not found.")
  };
};
