#include <iostream>

class Base {
    // 声明 Pal 为 Base 的友元类，Pal 能够访问 Base 的 private 和 protected 成员
    friend class Pal;
protected:
    int prot_mem = 42;  // 受保护成员，友元类 Pal 可以访问
private:
    int priv_mem = 100; // 私有成员，友元类 Pal 也可以访问，但派生类不能
};

class Sneaky : public Base {
private:
    int j = 10;  // 私有成员，Pal 不能访问，因为 Pal 不是 Sneaky 的友元
};

class Pal {
public:
    // Pal 是 Base 的友元，可以访问 Base 的受保护成员
    int f(Base b) {
        return b.prot_mem;  // 正确：Pal 是 Base 的友元，可以访问 protected 成员
    }

    // Pal 不是 Sneaky 的友元，不能访问 Sneaky 的私有成员
    int f2(Sneaky s) {
        // return s.j;  // 错误：Pal 不是 Sneaky 的友元，不能访问 Sneaky 的 private 成员
        return -1; // 此处返回一个默认值，避免编译错误
    }

    // 虽然 Sneaky 是 Base 的派生类，但 Pal 是 Base 的友元，仍然可以访问 Sneaky 从 Base 继承的 protected 成员
    int f3(Sneaky s) {
        return s.prot_mem;  // 正确：Pal 是 Base 的友元，可以访问 Sneaky 继承自 Base 的 protected 成员
    }
};

int main() {
    Base b;
    Sneaky s;
    Pal p;

    // 测试访问 Base 中的 protected 成员
    std::cout << "Pal accessing Base's protected member: " << p.f(b) << std::endl;

    // 测试访问 Sneaky 中的私有成员 (错误)
    // std::cout << "Pal accessing Sneaky's private member: " << p.f2(s) << std::endl; // 这一行会导致编译错误，注释掉以防止编译失败

    // 测试访问 Sneaky 继承自 Base 的 protected 成员
    std::cout << "Pal accessing Sneaky's protected member inherited from Base: " << p.f3(s) << std::endl;

    return 0;
}
