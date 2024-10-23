#include <iostream>
#include <string>

// 基类 Quote
class Quote {
public:
    // 默认构造函数
    Quote() = default;
    
    // 带参数的构造函数
    Quote(const std::string &book, double sales_price) 
        : bookNo(book), price(sales_price) { }

    // 返回书籍的 ISBN 号
    std::string isbn() const { return bookNo; }

    // 虚函数，计算总价格，允许派生类重写
    virtual double net_price(std::size_t n) const {
        return n * price;
    }

    // 虚析构函数，确保派生类正确析构
    virtual ~Quote() = default;

protected:
    double price = 0.0;  // 书籍价格

private:
    std::string bookNo;  // 书籍 ISBN
};

// 派生类 Bulk_quote
class Bulk_quote : public Quote {
public:
    // 带参数的构造函数
    Bulk_quote(const std::string& book, double p, std::size_t qty, double disc)
        : Quote(book, p), min_qty(qty), discount(disc) {}

    // 重写 net_price 函数，计算批量折扣
    double net_price(std::size_t cnt) const override {
        if (cnt >= min_qty) {
            return cnt * (1 - discount) * price;  // 达到最低数量享受折扣
        } else {
            return cnt * price;  // 否则按原价销售
        }
    }

private:
    std::size_t min_qty = 0;  // 享受折扣的最小购买数量
    double discount = 0.0;    // 折扣率
};

// 打印并计算总价的函数
double print_total(std::ostream &os, const Quote &item, std::size_t n) {
    // 调用 net_price 来计算总价
    double total = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n 
       << " total due: " << total << std::endl;
    return total;
}

// 主程序
int main() {
    // 创建 Quote 对象
    Quote basic("123-456-789", 50.0);
    
    // 创建 Bulk_quote 对象
    Bulk_quote bulk("123-456-789", 50.0, 10, 0.2);  // 10本以上享受 20% 折扣
    
    // 打印并计算5本书的总价
    print_total(std::cout, basic, 5);
    
    // 打印并计算15本书的总价
    print_total(std::cout, bulk, 15);

    return 0;
}
