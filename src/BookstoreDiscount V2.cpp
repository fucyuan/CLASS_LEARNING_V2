#include <iostream>
#include <string>

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
            return n * (1 - discount) * price;  // 如果数量达到最小折扣数
        else
            return n * price;  // 否则按原价销售
    }

private:
    std::size_t min_qty = 0;  // 最小折扣数量
    double discount = 0.0;    // 折扣率
};

// 一个测试函数，用来显示多态机制
void print_total(const Quote &item, std::size_t n) {
    double total = item.net_price(n);  // 调用 net_price，使用动态类型
    std::cout << "ISBN: " << item.isbn() << " # sold: " << n 
              << " total due: " << total << std::endl;
}

int main() {
    // 使用派生类对象
    Bulk_quote bulk("12345", 50.0, 10, 0.25);  // 10本以上打75折
    Quote *quotePtr = &bulk;  // 1. 使用基类指针指向派生类对象
    Quote &quoteRef = bulk;   // 2. 使用基类引用指向派生类对象

    // 使用指针或引用时，动态类型是 Bulk_quote，调用的是 Bulk_quote 的 net_price
    std::cout << "通过指针调用：" << quotePtr->net_price(15) << std::endl;  // 打折后价格
    std::cout << "通过引用调用：" << quoteRef.net_price(15) << std::endl;   // 打折后价格

    // 调用 print_total 函数，展示动态绑定
    print_total(bulk, 15);

    // 3. 基类不能自动转换为派生类（错误示例）
    Quote base("54321", 60.0);  // 一个基类对象
    // Bulk_quote &bulkRef = base;  // 错误：基类不能转换为派生类
    // Bulk_quote *bulkPtr = &base;  // 错误：基类指针不能自动转换为派生类指针
    return 0;
}
