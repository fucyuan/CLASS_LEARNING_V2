#include <iostream>
#include <string>
#include <typeinfo>  // 用于 typeid 检查

// 基类 Quote
class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price)
        : bookNo(book), price(sales_price) {}

    std::string isbn() const { return bookNo; }

    // 虚函数，用于计算总价
    virtual double net_price(std::size_t n) const {
        return n * price;
    }

    virtual ~Quote() = default;  // 虚析构函数

protected:
    double price = 0.0;  // 书籍价格

private:
    std::string bookNo;  // ISBN 号
};

// 派生类 Bulk_quote
class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double p, std::size_t qty, double disc)
        : Quote(book, p), min_qty(qty), discount(disc) {}

    // 重写 net_price 函数
    double net_price(std::size_t n) const override {
        if (n >= min_qty)
            return n * (1 - discount) * price;
        else
            return n * price;
    }

private:
    std::size_t min_qty = 0;  // 最小折扣数量
    double discount = 0.0;    // 折扣率
};

int main() {
    Bulk_quote bulk("12345", 50.0, 10, 0.25);  // 派生类对象
    Quote *itemP = &bulk;  // 正确：基类指针指向派生类对象

    // 1. 使用 dynamic_cast 进行安全的类型转换
    if (Bulk_quote *bulkP = dynamic_cast<Bulk_quote*>(itemP)) {
        std::cout << "使用 dynamic_cast 转换成功，调用 Bulk_quote 的方法: " 
                  << bulkP->net_price(20) << std::endl;
    } else {
        std::cout << "dynamic_cast 失败，itemP 不是指向 Bulk_quote 对象" << std::endl;
    }

    // 2. 使用 static_cast 强制转换（没有运行时检查）
    Bulk_quote *bulkP2 = static_cast<Bulk_quote*>(itemP);
    std::cout << "使用 static_cast 强制转换，调用 Bulk_quote 的方法: "
              << bulkP2->net_price(20) << std::endl;

    return 0;
}
