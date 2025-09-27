#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// Функция, корень которой ищем
double func(double x) {
    return pow(x, 2) - 2;
}

// Производная функции
double pr(double x) {
    return 2 * x;
}

// Метод половинного деления
void bisection_method(double a, double b, double epsilon) {
    printf("Metod polovin\n");
    int step = 0;
    double c;

    while (fabs(b - a) > epsilon) {
        step++;
        c = (a + b) / 2; // Середина отрезка
        if (func(a) * func(c) < 0) {
            b = c; // Корень в левой половине
        } else {
            a = c; // Корень в правой половине
        }
        printf("step %d: a = %.8f, b = %.8f, c = %.8f\n", step, a, b, c);
    }
    printf("Result: x = %.8f (found in %d steps)\n", c, step);
}

// Метод хорд
void chord_method(double a, double b, double epsilon) {
    printf("Metod Hord\n");
    int step = 0;
    double c;
    double c_pred ;
    double e; 

    while (fabs(b - a) > epsilon && e>epsilon) {
        step++;

        c_pred = c;
        c = (a * func(b) - b * func(a)) / (func(b) - func(a)); // Точка пересечения хорды
        e = c - c_pred;
        
        if (func(a) * func(c) < 0) {
            b = c; // Корень в левой половине
        } else {
            a = c; // Корень в правой половине
        }
        printf("step %d: a = %.8f, b = %.8f, c = %.8f\n", step, a, b, c);
    }
    printf("Result: x = %.8f (found in %d steps)\n", c, step);
}

// Метод Ньютона
void newton_method(double x0, double epsilon) {
    printf("Metod Nytona\n");
    int step = 0;
    double x = x0;

    while (fabs(func(x)) > epsilon) {
        step++;
        x = x - func(x) / pr(x); // Итерация Ньютона
        printf("step %d: x = %.8f\n", step, x);
    }
    printf("Result: x = %.8f (found in %d steps)\n", x, step);
}

int main() {
    double a = 1.0; // Начало интервала
    double b = 2.0; // Конец интервала
    double epsilon = 1e-8; // Точность

    // Метод половинного деления
    bisection_method(a, b, epsilon);

    // Метод хорд
    chord_method(a, b, epsilon);

    // Метод Ньютона
    newton_method(b, epsilon); // Начальное приближение для Ньютона

    return 0;
}