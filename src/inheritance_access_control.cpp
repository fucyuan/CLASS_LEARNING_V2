#include <iostream>

class B {
public:
    void public_func() const { 
        std::cout << "B's public function\n"; 
    }
protected:
    void protected_func() const { 
        std::cout << "B's protected function\n"; 
    }
private:
    void private_func() const { 
        std::cout << "B's private function\n"; 
    }
};

class D_public : public B {
public:
    void access_base() {
        public_func();       // 可以访问 B 的 public 成员
        protected_func();    // 可以访问 B 的 protected 成员
        // private_func();   // 无法访问 B 的 private 成员，编译错误
    }
};

class D_protected : protected B {
public:
    void access_base() {
        public_func();       // 可以访问 B 的 public 成员，因为继承方式是 protected
        protected_func();    // 可以访问 B 的 protected 成员
        // private_func();   // 无法访问 B 的 private 成员，编译错误
    }
};

class D_private : private B {
public:
    void access_base() {
        public_func();       // 可以访问 B 的 public 成员，因为继承方式是 private
        protected_func();    // 可以访问 B 的 protected 成员
        // private_func();   // 无法访问 B 的 private 成员，编译错误
    }
};

// 测试类型转换
void test_cast(B *b) {
    b->public_func();  // 通过基类指针调用 public 函数
    // b->protected_func(); // 无法调用 protected 函数，编译错误
    // b->private_func();   // 无法调用 private 函数，编译错误
}

int main() {
    D_public d_public;
    D_protected d_protected;
    D_private d_private;

    std::cout << "D_public accessing base:\n";
    d_public.access_base();
    std::cout << "D_protected accessing base:\n";
    d_protected.access_base();
    std::cout << "D_private accessing base:\n";
    d_private.access_base();

    // 测试类型转换
    B *b1 = &d_public;   // 公有继承，派生类可以向基类转换
    test_cast(b1);

    // B *b2 = &d_protected;  // 保护继承，派生类不能向基类转换，编译错误
    // B *b3 = &d_private;    // 私有继承，派生类不能向基类转换，编译错误

    return 0;
}
