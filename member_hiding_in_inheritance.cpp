#include <iostream>

struct Base {
    Base() : mem(0) {}  // 初始化 Base 类的 mem 为 0
protected:
    int mem;  // 基类中的成员变量 mem
};

struct Derived : Base {
    Derived(int i) : mem(i) {}  // 用 i 初始化派生类中的 mem，隐藏了 Base::mem

    int get_mem() { return mem; }  // 返回派生类中的 mem
protected:
    int mem;  // 派生类中的成员变量 mem，隐藏了 Base::mem
};

int main() {
    Derived d(42);  // 初始化 Derived 对象 d，Derived::mem 被初始化为 42
    std::cout << d.get_mem() << std::endl;  // 打印 Derived::mem 的值，输出 42
    return 0;
}
