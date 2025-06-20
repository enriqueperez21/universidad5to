# -*- coding: utf-8 -*-
"""Knn1.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1JB4HHBVZ-_VRmRycLgcFoN6UzaUZR_CO
"""

# Importar numpy
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.neighbors import KNeighborsClassifier

# Ampliar el dataset simulando más datos para evitar el problema
data_expanded = {
    "Humidity": np.random.randint(40, 100, 50),  # Humedad entre 40% y 100%
    "Pressure": np.random.uniform(950, 1050, 50),  # Presión entre 950 mb y 1050 mb
    "Rain": np.random.choice([0, 1], size=50, p=[0.6, 0.4])  # 60% No Rain, 40% Rain
}

# Crear DataFrame expandido
weather_df_expanded = pd.DataFrame(data_expanded)

# Separar variables independientes y dependientes
X = weather_df_expanded[["Humidity", "Pressure"]].values
y = weather_df_expanded["Rain"].values

# Dividir los datos en conjuntos de entrenamiento y prueba
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)

# Entrenar el modelo con los datos de entrenamiento completos
knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(X_train, y_train)

# Evaluar el modelo en los datos de prueba
test_accuracy = knn.score(X_test, y_test)
print(f"Test accuracy: {test_accuracy:.2f}")

# Aplicar cross-validation
cv_scores = cross_val_score(knn, X_train, y_train, cv=5, scoring='accuracy')  # 5 folds

# Imprimir las métricas obtenidas
print(f"Cross-validation scores: {cv_scores}")
print(f"Mean cross-validation accuracy: {np.mean(cv_scores):.2f}")
