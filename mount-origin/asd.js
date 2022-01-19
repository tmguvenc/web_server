goog.require('proto.messagefield');

var reader = new FileReader();
var xValues = [];
var yValues = [];
var i = 0;

var ws = new WebSocket("ws://localhost:9000", "callback_rtds");
ws.onopen = function () {
  var mf = new proto.MessageField();
  mf.setName("asd");
  mf.setValue(54.3);
  var bin = mf.serializeBinary();
  ws.send(bin);
  console.log("connected");
};
ws.onmessage = function (message) {
  reader.readAsText(message.data);
};
ws.onclose = function () {
  console.log("connection closed");
};
for (i = 0; i < 101; i++) {
  xValues.push(i);
}


function connect() {
  reader.addEventListener("load", () => {
    if (yValues.length == 75) {
      xValues.shift();
      xValues.push(i);
      i++;
      yValues.shift();
    }
    yValues.push(reader.result);
    chart.update();
  }, false);

}

function create_chart(chart_name) {
  return new Chart(chart_name, {
    type: "line",
    data: {
      labels: xValues,
      datasets: [{
        fill: false,
        lineTension: 0,
        pointRadius: 0,
        backgroundColor: "rgba(0,0,255,1.0)",
        borderColor: "rgba(0,0,255,0.5)",
        data: yValues
      }],
    },
    options: {
      legend: { display: false }
    }
  });
}
