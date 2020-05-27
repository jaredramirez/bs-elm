/* Abstract type to represent an Elm program
     This should not be used directly.
     Use `elmProgram` or `elmProgramWithPorts` instead.
   */
type elmProgramBase('runtime);

/* Type to represent an Elm program without ports */
type elmRuntime = unit;
type elmProgram = elmProgramBase(elmRuntime);

/* Type to represent an Elm program with ports */
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

/* Function to mount elm application */
let mount:
  (
    ~flags: 'flags=?,
    ~elementId: string=?,
    ~moduleName: string=?,
    elmProgramBase('runtime)
  ) =>
  Belt.Result.t('runtime, string);
