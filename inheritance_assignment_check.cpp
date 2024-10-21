#include <iostream>

class Base {
public:
    Base& operator=(const Base& rhs) {
        std::cout << "Base assignment operator\n";
        return *this;
    }
};

// 公有继承
class Pub_Derv : public Base {
public:
    void memfcn(Base &b) {
        b = *this;  // 合法，派生类对象可以赋值给基类对象
    }
};

// 受保护继承
class Prot_Derv : protected Base {
public:
    void memfcn(Base &b) {
        b = *this;  // 合法，因为这是在派生类内部，受保护的继承仍允许在成员函数内访问基类
    }
};

// 私有继承
class Priv_Derv : private Base {
public:
    void memfcn(Base &b) {
        b = *this;  // 合法，因为这是在派生类内部，私有的继承允许在成员函数内访问基类
    }
};

int main() {
    Base base;
    Pub_Derv pubD;
    Prot_Derv protD;
    Priv_Derv privD;

    pubD.memfcn(base);   // 合法
    protD.memfcn(base);  // 合法，因为转换在派生类内部进行
    privD.memfcn(base);  // 合法，因为转换在派生类内部进行

    return 0;
}
