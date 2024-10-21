#include <iostream>

// 基类
class Base {
public:
    virtual void func() {
        std::cout << "Base::func" << std::endl;
    }
};

// 派生类
class Derived : public Base {
public:
    // 重写虚函数
    void func() override {
        std::cout << "Derived::func" << std::endl;
        // 错误示例：没有调用基类的函数，导致无限递归
        // func();  // 这将递归调用 Derived::func 自己

        // 正确示例：使用作用域解析运算符调用基类的版本
        Base::func();  // 调用基类的函数，避免递归
    }
};

int main() {
    Derived d;
    d.func();  // 调用 Derived 的 func
    return 0;
}
