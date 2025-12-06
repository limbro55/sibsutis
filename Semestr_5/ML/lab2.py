import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import KFold
import matplotlib.pyplot as plt

CSV_PATH = "data3.csv"
N_SPLITS = 3
Q_VALUES = [2, 3, 4]
K_VALUES = [1, 3, 5, 7]


def pairwise_distances(A, B):
    A_sq = np.sum(A**2, axis=1)[:, None]
    B_sq = np.sum(B**2, axis=1)[None, :]
    prod = A.dot(B.T)
    d2 = A_sq + B_sq - 2 * prod
    np.maximum(d2, 0, out=d2)
    return np.sqrt(d2)


def get_topk_indices(dist_matrix, k):
    if k >= dist_matrix.shape[1]:
        return np.argsort(dist_matrix, axis=1)
    idx = np.argpartition(dist_matrix, k-1, axis=1)[:, :k]
    rows = np.arange(dist_matrix.shape[0])[:, None]
    sorted_local = np.argsort(dist_matrix[rows, idx], axis=1)
    return idx[rows, sorted_local]


def weighted_vote(neigh_labels, k, q):
    weights = ((k + 1 - np.arange(1, k+1)) / k) ** q
    preds = []
    for row in neigh_labels:
        scores = {}
        for i, label in enumerate(row):
            scores[label] = scores.get(label, 0) + weights[i]
        preds.append(max(scores.items(), key=lambda x: x[1])[0])
    return np.array(preds)


def evaluate_knn(X, y):
    indices = np.random.permutation(len(X))
    test_size = len(X) // 3
    test_idx = indices[:test_size]
    train_idx = indices[test_size:]

    X_train, y_train = X[train_idx], y[train_idx]
    X_test, y_test = X[test_idx], y[test_idx]

    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    X_test = scaler.transform(X_test)

    kf = KFold(n_splits=N_SPLITS, shuffle=True, random_state=42)
    cv_results = {}

    for k in K_VALUES:
        for q in Q_VALUES:
            fold_scores = []
            for tr_idx, val_idx in kf.split(X_train):
                X_tr, X_val = X_train[tr_idx], X_train[val_idx]
                y_tr, y_val = y_train[tr_idx], y_train[val_idx]

                dmat = pairwise_distances(X_val, X_tr)
                neigh = get_topk_indices(dmat, k)
                neigh_labels = y_tr[neigh]
                preds = weighted_vote(neigh_labels, k, q)
                fold_scores.append(np.mean(preds == y_val))

            cv_results[(k, q)] = fold_scores
            print(f"k={k}, q={q} | mean={np.mean(fold_scores):.4f}")

    mean_scores = {p: np.mean(v) for p, v in cv_results.items()}
    best_k, best_q = max(mean_scores.items(), key=lambda x: x[1])[0]

    d_test = pairwise_distances(X_test, X_train)
    neigh_test = get_topk_indices(d_test, best_k)
    preds_test = weighted_vote(y_train[neigh_test], best_k, best_q)
    test_acc = np.mean(preds_test == y_test)

    results = {
        "best_k": best_k,
        "best_q": best_q,
        "test_accuracy": test_acc,
        "cv_raw": cv_results,
        "cv_mean": mean_scores,
    }

    return results


def pretty_print_results(res):
    print("==============================================================")
    print("   ЭКСПЕРИМЕНТ С KNN С ВЗВЕШЕННЫМ ГОЛОСОВАНИЕМ (k, q)")
    print("==============================================================\n")

    print("Лучшие параметры:")
    print(f"k = {res['best_k']}")
    print(f"q = {res['best_q']}\n")

    print("Средняя точность по комбинациям:")
    for (k, q), score in sorted(res["cv_mean"].items()):
        print(f"k={k}, q={q}  ->  {score:.4f}")

    values = list(res['cv_mean'].values())
    print("\n===========================================")
    print(f"Средняя точность CV: {np.mean(values):.4f}")
    print(f"Стандартное отклонение: {np.std(values):.4f}")
    print(f"Лучшая точность: {np.max(values):.4f}")
    print(f"Худшая точность: {np.min(values):.4f}")
    print("===========================================\n")

    print(f"Точность на тестовой выборке: {res['test_accuracy']:.4f}")


# Основной запуск
if __name__ == "__main__":
    df = pd.read_csv(CSV_PATH)
    X = df.iloc[:, :-1].values.astype(float)
    y = df.iloc[:, -1].values

    res = evaluate_knn(X, y)
    pretty_print_results(res)