module R = Js.Result;

/* Ports Helper Types */
type portFromElm('data) = {
  .
  [@bs.meth] "subscribe": ('data => unit) => unit,
  [@bs.meth] "unsubscribe": unit => unit
};

type portToElm('data) = {. [@bs.meth] "send": 'data => unit};

/* Elm Instance Types */
type elmInstanceWithPorts('ports) = {. "ports": 'ports};

type elmInstance = {.};

/* Elm Program Types */
type elmProgramBase('instance);

type elmProgram = elmProgramBase(elmInstance);

type elmProgramWithPorts('ports) = elmProgramBase(elmInstanceWithPorts('ports));

/* Mount Program */
let mount:
  (
    ~flags: 'flags=?,
    ~elementId: string=?,
    ~moduleName: string=?,
    elmProgramBase('instance)
  ) =>
  R.t('instance, string);
