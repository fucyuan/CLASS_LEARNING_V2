#include <iostream>
class Base {
public:
    virtual ~Base() { 
        std::cout << "Base Destructor" << std::endl; 
    }
};

class Derived : public Base {
public:
    ~Derived() override {
        std::cout << "Derived Destructor" << std::endl; 
    }
};

int main() {
    Base* ptr = new Derived();
    delete ptr;  // 调用 Derived 和 Base 的析构函数
}
