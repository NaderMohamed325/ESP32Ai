const axios = require("axios");

async function predictHealthStatus(hr, spo2) {
  try {
    const response = await axios.post("http://localhost:8000/predict", {
      heartRate: hr,
      spo2: spo2,
    });
    return response.data.status;
  } catch (e) {
    console.error("ML server error:", e.message);
    return "Error";
  }
}

module.exports = { predictHealthStatus };
