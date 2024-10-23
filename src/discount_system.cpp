#include <iostream>
#include <string>

// 基类Quote的定义
class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) 
        : bookNo(book), price(sales_price) {}

    std::string isbn() const { return bookNo; }

    // 虚函数，用于计算销售价格，支持不同的定价策略
    virtual double net_price(std::size_t n) const {
        return n * price;
    }

    virtual ~Quote() = default;  // 基类析构函数需要是虚函数

private:
    std::string bookNo;  // 书的ISBN编号
protected:
    double price = 0.0;  // 价格
};

// 抽象类Disc_quote的定义，继承自Quote
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc)
        : Quote(book, price), quantity(qty), discount(disc) {}

    // 由于Disc_quote不定义折扣策略，所以不实现net_price，留给子类实现
    virtual double net_price(std::size_t) const = 0;

protected:
    std::size_t quantity = 0;  // 享受折扣的最低购买量
    double discount = 0.0;     // 折扣额
};

// 具体的折扣类Bulk_quote，继承自Disc_quote
class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double price, std::size_t qty, double disc)
        : Disc_quote(book, price, qty, disc) {}

    // 实现折扣策略
    double net_price(std::size_t n) const override {
        if (n >= quantity) {
            return n * (1 - discount) * price;
        } else {
            return n * price;
        }
    }
};

// 主函数，测试折扣类的行为
int main() {
    Bulk_quote bulk("12345", 50.0, 10, 0.2); // 买10本及以上打八折

    std::cout << "Buying 5 books: " << bulk.net_price(5) << std::endl;
    std::cout << "Buying 10 books: " << bulk.net_price(10) << std::endl;

    return 0;
}
