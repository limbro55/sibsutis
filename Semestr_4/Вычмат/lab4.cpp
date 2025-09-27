#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

// Функции системы уравнений
double func1(double x, double y) {
    return pow(x, 2) + pow(y, 2) - 6;
}

double func2(double x, double y) {
    return x - y - 2;
}

// Вычисление матрицы производных
void computeJacobian(double x, double y, double W[2][2]) {
    W[0][0] = 2 * x;
    W[0][1] = 2 * y;
    W[1][0] = 1;
    W[1][1] = -1;
}

//обратнаяя матрицы
void computeInverseMatrix(const double W[2][2], double W_inv[2][2]) {
    double det = W[0][0] * W[1][1] - W[0][1] * W[1][0];
    W_inv[0][0] = W[1][1] / det;
    W_inv[0][1] = -W[0][1] / det;
    W_inv[1][0] = -W[1][0] / det;
    W_inv[1][1] = W[0][0] / det;
}

void printMatrix(const double mat[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

void printVector(const double vec[2]) {
    for (int i = 0; i < 2; i++) {
        cout << vec[i] << endl;
    }
}

// Матричный метод
void matrixMethod(double x_init, double y_init, double eps) {
    double x_mas[2] = {x_init, y_init};
    int step = 1;
    
    cout << "\n=== МАТРИЧНЫЙ МЕТОД ===" << endl;
    
    while (true) {
        //вектор и якоби
        double F[2] = {func1(x_mas[0], x_mas[1]), func2(x_mas[0], x_mas[1])};
        double W[2][2], W_inv[2][2];
        
        computeJacobian(x_mas[0], x_mas[1], W);
        computeInverseMatrix(W, W_inv);
        
        cout << "\nШАГ #" << step << endl;
        cout << "Вектор функций F(x):" << endl;
        printVector(F);
        cout << "Обратная матрица W^-1:" << endl;
        printMatrix(W_inv);
        
        // выч нового приближения
        double new_x[2];
        for (int i = 0; i < 2; i++) {
            new_x[i] = x_mas[i];
            for (int j = 0; j < 2; j++) {
                new_x[i] -= W_inv[i][j] * F[j];
            }
        }
        
        // проверка сходимости
        double e[2] = {abs(new_x[0] - x_mas[0]), abs(new_x[1] - x_mas[1])};
        if (e[0] < eps && e[1] < eps) break;
        
        cout << "Ошибки:" << endl;
        cout << "E1 = " << e[0] << endl;
        cout << "E2 = " << e[1] << endl;
        
        // обновление знач
        x_mas[0] = new_x[0];
        x_mas[1] = new_x[1];
        
        cout << "Новое приближение:" << endl;
        cout << "x1 = " << x_mas[0] << endl;
        cout << "x2 = " << x_mas[1] << endl;
    
        step++;
    }
}

// Метод Гаусса
void gaussMethod(double x_init, double y_init, double eps) {
    double x_mas[2] = {x_init, y_init};
    int step = 1;
    
    cout << "\n=== МЕТОД ГАУССА ===" << endl;
    
    while (true) {
        //вектор
        double F[2] = {func1(x_mas[0], x_mas[1]), func2(x_mas[0], x_mas[1])};
        double W[2][2];
        computeJacobian(x_mas[0], x_mas[1], W);
        
        cout << "\nШАГ #" << step << endl;
        cout << "Вектор функций F(x):" << endl;
        printVector(F);
        
        // Прямой ход
        for (int i = 0; i < 2; i++) {
            // Выбор главного элемента
            int max_row = i;
            for (int j = i+1; j < 2; j++) {
                if (abs(W[j][i]) > abs(W[max_row][i])) {
                    max_row = j;
                }
            }
            
            if (max_row != i) {
                swap(W[i], W[max_row]);
                swap(F[i], F[max_row]);
            }
            
            // 1 на диагонале
            double pivot = W[i][i];
            for (int j = i; j < 2; j++) W[i][j] /= pivot;
            F[i] /= pivot;
            
            // нули под диагонаью
            for (int k = i+1; k < 2; k++) {
                double factor = W[k][i];
                for (int j = i; j < 2; j++) W[k][j] -= factor * W[i][j];
                F[k] -= factor * F[i];
            }
        }
        
        // обратный ход
        double delta[2] = {0};
        for (int i = 1; i >= 0; i--) {
            delta[i] = F[i];
            for (int j = i+1; j < 2; j++) {
                delta[i] -= W[i][j] * delta[j];
            }
        }
        
        // Новое приближение
        double new_x[2] = {x_mas[0] - delta[0], x_mas[1] - delta[1]};
        
        // Ошибки
        double errors[2] = {abs(delta[0]), abs(delta[1])};
        
        cout << "Ошибки:" << endl;
        cout << "E1 = " << errors[0] << endl;
        cout << "E2 = " << errors[1] << endl;
        
        // Обновление
        x_mas[0] = new_x[0];
        x_mas[1] = new_x[1];
        
        cout << "Новое приближение:" << endl;
        cout << "x1 = " << x_mas[0] << endl;
        cout << "x2 = " << x_mas[1] << endl;
        
        if (errors[0] < eps && errors[1] < eps) break;
        step++;
    }
}

int main() {
    const double x_init = 2.0;
    const double y_init = 1.0;
    const double eps = 1e-11;
    
    matrixMethod(x_init, y_init, eps);
    gaussMethod(x_init, y_init, eps);
    
    return 0;
}