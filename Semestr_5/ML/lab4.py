import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split, GridSearchCV, KFold, cross_val_score
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.linear_model import LinearRegression, Lasso, ElasticNet
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score

# ---------- 1. Подготовка данных ----------

url = "https://raw.githubusercontent.com/SampattKumar/Linear-Regression-Car-Dataset/master/CarPrice_Assignment.csv"
df = pd.read_csv(url)

# Удаляем ненужную колонку
if "car_ID" in df.columns:
    df.drop(columns=["car_ID"], inplace=True)

# Приводим price к числу
df["price"] = pd.to_numeric(df["price"], errors="coerce")
df.dropna(subset=["price"], inplace=True)

# Категориальные и числовые признаки
cat_cols = df.select_dtypes(include=["object"]).columns.tolist()
num_cols = df.select_dtypes(include=[np.number]).columns.tolist()
num_cols.remove("price")

# Label Encoding
for col in cat_cols:
    df[col] = df[col].fillna("missing")
    df[col] = LabelEncoder().fit_transform(df[col].astype(str))

X = df[num_cols + cat_cols]
y = df["price"]

# Разделение
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# Масштабирование числовых
scaler = StandardScaler()
X_train[num_cols] = scaler.fit_transform(X_train[num_cols])
X_test[num_cols] = scaler.transform(X_test[num_cols])

# ---------- 2. Модели ----------
models = {
    "LinearRegression": LinearRegression(),
    "Lasso": Lasso(random_state=42),
    "ElasticNet": ElasticNet(random_state=42)
}

fitted = {}
for name, m in models.items():
    m.fit(X_train, y_train)
    fitted[name] = m
    print(name, "обучена")

# ---------- 3. Метрики ----------
def evaluate(model):
    y_pred = model.predict(X_test)
    return {
        "MSE": mean_squared_error(y_test, y_pred),
        "RMSE": np.sqrt(mean_squared_error(y_test, y_pred)),
        "MAE": mean_absolute_error(y_test, y_pred),
        "R2": r2_score(y_test, y_pred),
        "y_pred": y_pred
    }

results = {}
for name, m in fitted.items():
    print(f"\n{name}:")
    results[name] = evaluate(m)
    for metric, value in results[name].items():
        if metric != "y_pred":
            print(f" {metric}: {value:.4f}")

# ---------- 3.2 Графики predicted vs actual ----------
for name, res in results.items():
    plt.figure(figsize=(6,6))
    plt.scatter(y_test, res["y_pred"], alpha=0.6)
    plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], "r--")
    plt.title(f"{name} — Predicted vs Actual")
    plt.xlabel("Фактические значения")
    plt.ylabel("Предсказанные значения")
    plt.grid(True)
    plt.show()

# ---------- 3.3 Коэффициенты моделей ----------
coef_df = pd.DataFrame(index=X.columns)
for name, m in fitted.items():
    if hasattr(m, "coef_"):
        coef_df[name] = m.coef_

print("\nКоэффициенты моделей:")
display(coef_df)

# ---------- 4. Подбор гиперпараметров ----------

cv = KFold(n_splits=5, shuffle=True, random_state=42)

lasso_params = {"alpha": [0.0001, 0.001, 0.01, 0.1, 1, 10]}
enet_params = {
    "alpha": [0.0001, 0.001, 0.01, 0.1, 1, 10],
    "l1_ratio": [0.1, 0.3, 0.5, 0.7, 0.9]
}

gs_lasso = GridSearchCV(Lasso(random_state=42, max_iter=10000),
                        lasso_params, scoring="neg_mean_squared_error", cv=cv)
gs_enet = GridSearchCV(ElasticNet(random_state=42, max_iter=10000),
                       enet_params, scoring="neg_mean_squared_error", cv=cv)

gs_lasso.fit(X_train, y_train)
gs_enet.fit(X_train, y_train)

print("\nЛучшие параметры Lasso:", gs_lasso.best_params_)
print("Лучшие параметры ElasticNet:", gs_enet.best_params_)

# ---------- 4.2 Кросс-валидация ----------
for name, model in {
    "LinearRegression": LinearRegression(),
    "Lasso_best": gs_lasso.best_estimator_,
    "ElasticNet_best": gs_enet.best_estimator_
}.items():
    scores = cross_val_score(model, X_train, y_train, cv=cv, scoring="r2")
    print(f"\n{name}: CV R2 = {scores.mean():.4f} ± {scores.std():.4f}")

# ---------- 4.3 Улучшение качества ----------
best_lasso = gs_lasso.best_estimator_
best_enet = gs_enet.best_estimator_

best_lasso.fit(X_train, y_train)
best_enet.fit(X_train, y_train)

print("\nLasso до/после:")
print(" RMSE default:", results["Lasso"]["RMSE"])
print(" RMSE tuned:", evaluate(best_lasso)["RMSE"])

print("\nElasticNet до/после:")
print(" RMSE default:", results["ElasticNet"]["RMSE"])
print(" RMSE tuned:", evaluate(best_enet)["RMSE"])
