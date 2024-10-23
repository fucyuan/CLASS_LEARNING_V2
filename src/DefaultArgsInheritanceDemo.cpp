#include <iostream>

// 基类
class Base {
public:
    // 带有两个参数的构造函数，其中第二个参数有默认值
    Base(int x, int y = 5) {
        std::cout << "Base constructor called with x = " << x << ", y = " << y << std::endl;
    }
};

// 派生类
class Derived : public Base {
public:
    // 派生类从基类继承了两个构造函数版本
    using Base::Base;  // 使用基类构造函数

    // 额外的构造函数可以在这里定义
};

int main() {
    Derived d1(10);     // 调用 Base 构造函数，其中 x = 10, y 使用默认值 5
    Derived d2(10, 20); // 调用 Base 构造函数，其中 x = 10, y = 20
    return 0;
}
