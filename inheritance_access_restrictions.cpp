#include <iostream>

class Base {
public:
    void pub_mem() const {
        std::cout << "Base public member function\n";
    }
protected:
    int prot_mem;  // 受保护成员
private:
    char priv_mem; // 私有成员
};

// 公有继承
class Pub_Derv : public Base {
   
    // 继承了Base的pub_mem，且在Pub_Derv中保持public
};

// 私有继承
class Priv_Derv : private Base {
public:
     void access_base() {
     pub_mem();
     }
    // 继承了Base的pub_mem，但在Priv_Derv中变为private
};

int main() {
    Pub_Derv d1;
    Priv_Derv d2;

    d1.pub_mem();  // 正确，pub_mem在Pub_Derv中是public的
    // d2.pub_mem();  // 错误，pub_mem在Priv_Derv中是private的，不能访问
    d2.access_base();

    return 0;
}
