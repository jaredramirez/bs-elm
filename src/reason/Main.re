module R = Js.Result;

/* PORTS */
type infoForReasonPayload;

external infoForReasonPayloadToTodo :
  infoForReasonPayload =>
  {
    .
    "text": string,
    "isComplete": bool
  } =
  "%identity";

type infoForReasonTag = [ | [@bs.as "addTodo"] `AddTodo];

type ports = {
  .
  "infoForReason":
    ReasonElm.elmInPort(
      {
        .
        "tag": infoForReasonTag,
        "payload": infoForReasonPayload
      }
    )
};

/* ELM PROGRAM */
[@bs.module]
external elmProgram : ReasonElm.elmProgramWithPorts(ports) = "../elm/Main.elm";

let instance = ReasonElm.mount(~flags={"hello": "world"}, elmProgram);

switch instance {
| R.Ok(i) =>
  i##ports##infoForReason##subscribe(info => {
    let tag = info##tag;
    switch tag {
    | `AddTodo =>
      let payload = infoForReasonPayloadToTodo(info##payload);
      Js.log(payload##text);
      Js.log(payload##isComplete);
      ();
    };
    ();
  });
  ();
| R.Error(message) => Js.log(message)
};
