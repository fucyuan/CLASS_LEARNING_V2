#include <iostream>
#include <string>

// 基类
class Base {
public:
    std::string name;
    
    // 默认构造函数
    Base() : name("Default Base") {
        std::cout << "Base default constructor\n";
    }
    
    // 拷贝构造函数
    Base(const Base& other) : name(other.name) {
        std::cout << "Base copy constructor\n";
    }
    
    // 移动构造函数
    Base(Base&& other) noexcept : name(std::move(other.name)) {
        std::cout << "Base move constructor\n";
    }
};

// 派生类
class Derived : public Base {
public:
    int value;
    
    // 默认构造函数
    Derived() : Base(), value(0) {
        std::cout << "Derived default constructor\n";
    }
    
    // 拷贝构造函数
    Derived(const Derived& other) : Base(other), value(other.value) {
        std::cout << "Derived copy constructor\n";
    }
    
    // 移动构造函数
    Derived(Derived&& other) noexcept : Base(std::move(other)), value(other.value) {
        std::cout << "Derived move constructor\n";
    }
};

int main() {
    Derived d1;                      // 调用默认构造函数
    Derived d2(d1);                  // 调用拷贝构造函数
    Derived d3(std::move(d1));       // 调用移动构造函数
    
    return 0;
}
