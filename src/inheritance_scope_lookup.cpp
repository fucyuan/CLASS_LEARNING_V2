#include <iostream>

class Base {
public:
    void show() {
        std::cout << "Base class show()" << std::endl;
    }
};

class Derived : public Base {
public:
    void display() {
        std::cout << "Derived class display()" << std::endl;
    }
    // 如果在 Derived 类中没有定义 show()，编译器会查找 Base 类中的 show()
};

int main() {
    Derived d;
    d.display();  // 调用派生类的 display() 函数
    d.show();     // 调用基类的 show() 函数
    return 0;
}
