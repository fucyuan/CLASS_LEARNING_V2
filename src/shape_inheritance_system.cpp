#include <iostream>
#include <cmath>

// 基类：图形基元
class Shape {
public:
    virtual double area() const = 0;    // 纯虚函数：计算面积
    virtual double volume() const = 0;  // 纯虚函数：计算体积（如果适用）
    virtual ~Shape() = default;         // 虚析构函数
};

// 派生类：矩形
class Rectangle : public Shape {
private:
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    double volume() const override {
        return 0.0;  // 矩形没有体积
    }
};

// 派生类：圆
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return M_PI * radius * radius;
    }

    double volume() const override {
        return 0.0;  // 圆形没有体积
    }
};

// 派生类：球体
class Sphere : public Shape {
private:
    double radius;
public:
    Sphere(double r) : radius(r) {}

    double area() const override {
        return 4 * M_PI * radius * radius;
    }

    double volume() const override {
        return (4.0/3) * M_PI * radius * radius * radius;
    }
};

int main() {
    Rectangle rect(10, 20);
    Circle circ(15);
    Sphere sphere(10);

    std::cout << "Rectangle area: " << rect.area() << std::endl;
    std::cout << "Circle area: " << circ.area() << std::endl;
    std::cout << "Sphere area: " << sphere.area() << std::endl;
    std::cout << "Sphere volume: " << sphere.volume() << std::endl;

    return 0;
}
