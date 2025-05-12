import joblib
from sklearn.ensemble import RandomForestClassifier
import numpy as np

X = np.array([
    [80, 98], [120, 92], [100, 95], [60, 97], [130, 89]
])
y = ["Normal", "Tachycardia", "Normal", "Normal", "Hypoxia"]

model = RandomForestClassifier().fit(X, y)
joblib.dump(model, "model.pkl")
