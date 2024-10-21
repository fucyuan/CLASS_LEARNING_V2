#include <iostream>

class Base {
public:
    void public_func() const {
        std::cout << "Base public function: accessible by anyone\n";
    }

protected:
    void protected_func() const {
        std::cout << "Base protected function: accessible by derived classes\n";
    }

private:
    void private_func() const {
        std::cout << "Base private function: accessible only by Base\n";
    }
};

class Derived : public Base {
public:
    // 派生类可以访问Base类的protected成员
    void access_base() {
        public_func();       // 可以访问Base类的public成员
        protected_func();    // 可以访问Base类的protected成员
        // private_func();   // 错误，无法访问Base类的private成员
    }
};

int main() {
    Base base_obj;
    Derived derived_obj;

    std::cout << "Accessing from Base object:\n";
    base_obj.public_func();    // 访问public成员
    // base_obj.protected_func(); // 错误，无法访问protected成员
    // base_obj.private_func();   // 错误，无法访问private成员

    std::cout << "\nAccessing from Derived object:\n";
    derived_obj.public_func();  // 访问public成员
    derived_obj.access_base();  // 通过派生类的函数访问protected成员

    return 0;
}
