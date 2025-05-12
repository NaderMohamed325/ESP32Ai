const express = require("express");
const bodyParser = require("body-parser");
const { predictHealthStatus } = require("./ml_model");


const app = express();
app.use(bodyParser.json());

app.post("/api/data", async (req, res) => {
  const { heartRate, spo2 } = req.body;
  console.log(heartRate, spo2);
  const prediction = await predictHealthStatus(heartRate, spo2);
 
  res.json({ status: prediction });
});


app.listen(3000, () => console.log("Node server on port 3000"));
