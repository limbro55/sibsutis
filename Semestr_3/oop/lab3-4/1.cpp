#include <iostream>
#include <vector>

// Пример класса точки
class Point {
public:
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// Пример базового класса графического объекта
class Shape {
public:
    virtual void draw() = 0; // виртуальная функция отрисовки
};

// Пример класса линии, наследующего Shape
class Line : public Shape {
private:
    Point start, end;
public:
    Line(Point _start, Point _end) : start(_start), end(_end) {}

    void draw() override {
        std::cout << "Рисуем линию от (" << start.x << "," << start.y << ") до (" << end.x << "," << end.y << ")" << std::endl;
    }
};

// Пример класса для холста, который управляет всеми объектами
class Canvas {
private:
    std::vector<Shape*> shapes; // вектор для хранения всех объектов

public:
    void addShape(Shape* shape) {
        shapes.push_back(shape);
    }

    void redraw() {
        for (Shape* shape : shapes) {
            shape->draw();
        }
    }
};

int main() {
    Canvas canvas;
    Point p1(10, 10);
    Point p2(50, 50);
    Line line(p1, p2);

    canvas.addShape(&line);
    canvas.redraw();

    return 0;
}
