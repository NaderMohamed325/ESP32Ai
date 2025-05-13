const axios = require("axios");

async function predictHealthStatus(hr, spo2) {
  try {
    const response = await axios.post(
      "https://patient-luck-production.up.railway.app/predict",
      {
        heartRate: hr,
        spo2: spo2,
      },
      {
        headers: {
          "Content-Type": "application/json",
        },
      }
    );
    return response.data.status;
  } catch (e) {
    console.error("ML server error:", e.response?.data || e.message);
    return "Error";
  }
}

module.exports = { predictHealthStatus };
