# main.py
from fastapi import FastAPI
from pydantic import BaseModel
import joblib

class HealthData(BaseModel):
    heartRate: int
    spo2: float

app = FastAPI()
model = joblib.load("model.pkl")

@app.post("/predict")
def predict(data: HealthData):
    pred = model.predict([[data.heartRate, data.spo2]])[0]
    return {"status": pred}
