module Timer = {
  type action =
    | Start
    | Stop
    | Pause
    | Resume;
  type mode =
    | Running
    | Pausing
    | Stopped;
  type historyItem = {
    id: int,
    action,
    time: float
  };
  type state = {
    mode,
    history: list historyItem
  };
  let action2String action =>
    switch action {
    | Start => "Start"
    | Stop => "Stop"
    | Pause => "Pause"
    | Resume => "Resume"
    };
  let component = ReasonReact.reducerComponent "Timer";
  let make _children => {
    let historyHelper state action => {
      ...state,
      history: [
        {id: List.length state.history + 1, action, time: Js_date.now ()},
        ...state.history
      ]
    };
    let start _event => Start;
    let stop _event => Stop;
    let pause _event => Pause;
    let resume _event => Resume;
    {
      ...component,
      initialState: fun () => {mode: Stopped, history: []},
      reducer: fun action state => {
        let newState = historyHelper state action;
        switch action {
        | Start => ReasonReact.Update {...newState, mode: Running}
        | Pause => ReasonReact.Update {...newState, mode: Pausing}
        | Resume => ReasonReact.Update {...newState, mode: Running}
        | Stop => ReasonReact.Update {...newState, mode: Stopped}
        }
      },
      render: fun {state, reduce} => {
        let buttons =
          switch state.mode {
          | Stopped =>
            <div>
              <button name="start" onClick=(reduce start)>
                (ReasonReact.stringToElement "start")
              </button>
            </div>
          | Running =>
            <div>
              <button name="stop" onClick=(reduce stop)>
                (ReasonReact.stringToElement "stop")
              </button>
              <button name="pause" onClick=(reduce pause)>
                (ReasonReact.stringToElement "pause")
              </button>
            </div>
          | Pausing =>
            <div>
              <button name="resume" onClick=(reduce resume)>
                (ReasonReact.stringToElement "resume")
              </button>
              <button name="stop" onClick=(reduce stop)>
                (ReasonReact.stringToElement "stop")
              </button>
            </div>
          };
        let history =
          state.history
          |> List.map (
               fun historyItem => {
                 let timeString: string =
                   Js_date.toTimeString (Js_date.fromFloat historyItem.time);
                 <li key=(string_of_int historyItem.id)>
                   (
                     ReasonReact.stringToElement (
                       timeString ^ ": " ^ action2String historyItem.action
                     )
                   )
                 </li>
               }
             );
        <div>
          buttons
          <h1> (ReasonReact.stringToElement "Timer") </h1>
          <ul> (ReasonReact.arrayToElement (Array.of_list history)) </ul>
        </div>
      }
    }
  };
};

ReactDOMRe.renderToElementWithClassName <Timer /> "timer";
