# ================================================
#  Решающее дерево на Titanic
#  Полное решение задания (пункты 1–5)
# ================================================

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.metrics import accuracy_score
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder
from sklearn.impute import SimpleImputer
from sklearn.pipeline import Pipeline
import os

url = "https://raw.githubusercontent.com/datasciencedojo/datasets/master/titanic.csv"
df = pd.read_csv(url)

# Целевая переменная
y = df["Survived"]

# Выбираем адекватные признаки
X = df[[
    "Pclass", "Sex", "Age", "SibSp", "Parch",
    "Fare", "Embarked"
]]

# Пропуски:
# Age — много пропусков
# Embarked — несколько пропусков
# Fare — редкие пропуски
num_cols = ["Age", "Fare", "SibSp", "Parch"]
cat_cols = ["Pclass", "Sex", "Embarked"]

# Числовые: заполняем медианой
num_transformer = SimpleImputer(strategy="median")

# Категориальные: "missing" + One Hot Encoding
cat_transformer = Pipeline(steps=[
    ("imputer", SimpleImputer(strategy="most_frequent")),
    ("ohe", OneHotEncoder(handle_unknown="ignore"))
])

# Общий препроцессор
preprocessor = ColumnTransformer(
    transformers=[
        ("num", num_transformer, num_cols),
        ("cat", cat_transformer, cat_cols),
    ]
)

# Деление 80/20
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, stratify=y, random_state=42
)

base_model = Pipeline([
    ("prep", preprocessor),
    ("clf", DecisionTreeClassifier(random_state=42))
])

base_model.fit(X_train, y_train)
base_pred = base_model.predict(X_test)
acc_base = accuracy_score(y_test, base_pred)

print(f"2.2 Accuracy базовой модели: {acc_base:.4f}")

# Определяем важности признаков
clf = base_model.named_steps["clf"]
feature_names = (
    num_cols +
    list(base_model.named_steps["prep"]
         .named_transformers_["cat"]
         .named_steps["ohe"]
         .get_feature_names_out(cat_cols))
)

importances = pd.Series(clf.feature_importances_, index=feature_names)
print("\n2.3 Топ-3 признака базовой модели:")
print(importances.sort_values(ascending=False).head(3))


max_depth_values = range(2, 15)
max_leaf_nodes_values = range(4, 40, 2)

results = []

for md in max_depth_values:
    for mln in max_leaf_nodes_values:
        model = Pipeline([
            ("prep", preprocessor),
            ("clf", DecisionTreeClassifier(
                max_depth=md,
                max_leaf_nodes=mln,
                random_state=42
            ))
        ])

        model.fit(X_train, y_train)
        pred = model.predict(X_test)
        acc = accuracy_score(y_test, pred)

        results.append({
            "max_depth": md,
            "max_leaf_nodes": mln,
            "accuracy": acc
        })

results_df = pd.DataFrame(results)

best_row = results_df.loc[results_df["accuracy"].idxmax()]
best_md = int(best_row["max_depth"])
best_mln = int(best_row["max_leaf_nodes"])
best_acc = float(best_row["accuracy"])

print(f"\n4.1 Лучшая комбинация: max_depth={best_md}, max_leaf_nodes={best_mln}")
print(f"Лучшая accuracy: {best_acc:.4f}")

# 4.2 Визуализация зависимости accuracy
pivot = results_df.pivot(index="max_depth", columns="max_leaf_nodes", values="accuracy")

plt.figure(figsize=(12, 6))
sns.heatmap(pivot, annot=False, cmap="viridis")
plt.title("Accuracy в зависимости от max_depth и max_leaf_nodes")
plt.xlabel("max_leaf_nodes")
plt.ylabel("max_depth")
plt.tight_layout()
plt.show()

# 4.3 Сравнение
print(f"\n4.3 Сравнение:")
print(f"Базовая точность  = {acc_base:.4f}")
print(f"Лучшая точность   = {best_acc:.4f}")
print(f"Улучшение         = {best_acc - acc_base:.4f}")


final_model = Pipeline([
    ("prep", preprocessor),
    ("clf", DecisionTreeClassifier(
        max_depth=best_md,
        max_leaf_nodes=best_mln,
        random_state=42
    ))
])

final_model.fit(X_train, y_train)

plt.figure(figsize=(25, 12))
plot_tree(
    final_model.named_steps["clf"],
    feature_names=feature_names,
    class_names=["Died", "Survived"],
    filled=True, rounded=True, fontsize=8
)

os.makedirs("output", exist_ok=True)
plt.savefig("output/titanic_tree.png", dpi=200)
plt.show()

print("\n5.3 Дерево сохранено → output/titanic_tree.png")
