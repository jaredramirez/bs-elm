module R = Js.Result;

/* PORTS */
type ports = {
  .
  "infoForReason": ReasonElm.elmInPort(string),
  "infoForElm": ReasonElm.elmOutPort(string)
};

/* ELM PROGRAM */
[@bs.module]
external elmProgram : ReasonElm.elmProgramWithPorts(ports) = "../elm/Main.elm";

let instance =
  ReasonElm.mount(
    ~flags={"title": "Buttons (title set in Reason via flags)"},
    elmProgram
  );

switch instance {
| R.Ok(i) =>
  let infoForReason = i##ports##infoForReason;
  let infoForElm = i##ports##infoForElm;
  infoForReason##subscribe(info => infoForElm##send("You pressed " ++ info));
| R.Error(message) => Js.log(message)
};
