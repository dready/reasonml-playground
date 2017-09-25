let component = ReasonReact.statelessComponent "TimeInput";

/* underscore before names indicate unused variables. We name them for clarity */
let make ::name ::required=true ::placeholder="00:00" ::value="" _children => {
  ...component,
  render: fun _self =>
    <input
      _type="text"
      placeholder
      name
      id=name
      required=(Js.Boolean.to_js_boolean required)
      value
    />
};
