#include <iostream>

// 基类 Quote
class Quote {
public:
    virtual double net_price(std::size_t n, double discount = 0.1) const {
        std::cout << "Quote::net_price called" << std::endl;
        return n * (1 - discount) * price;
    }

    virtual ~Quote() = default;

protected:
    double price = 50.0;  // 假设书的原价是 50
};

// 派生类 Bulk_quote
class Bulk_quote : public Quote {
public:
    // 重写基类中的 net_price 函数，但不设置默认参数
    double net_price(std::size_t n, double discount = 0.2) const override {
        std::cout << "Bulk_quote::net_price called" << std::endl;
        return n * (1 - discount) * price;
    }
};

int main() {
    Quote q;
    Bulk_quote b;

    Quote *quotePtr = &q;
    Quote *bulkPtr = &b;

    // 基类对象的调用
    std::cout << quotePtr->net_price(10) << std::endl;  // 使用基类默认实参 0.1

    // 派生类对象的调用
    std::cout << bulkPtr->net_price(10) << std::endl;   // 使用基类默认实参 0.1
}
