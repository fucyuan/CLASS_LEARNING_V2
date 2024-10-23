#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 基类 Quote
class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
    
    // 虚函数：用于返回对象的 ISBN 编号
    std::string isbn() const { return bookNo; }

    // 虚函数：用于计算销售 n 本书的总价格
    virtual double net_price(std::size_t n) const { return n * price; }

    // 虚函数：克隆当前对象
    virtual Quote* clone() const & { return new Quote(*this); }  // 拷贝当前对象
    virtual Quote* clone() && { return new Quote(std::move(*this)); }  // 移动当前对象

    virtual ~Quote() = default;  // 虚析构函数

protected:
    std::string bookNo;  // 书的 ISBN 编号
    double price = 0.0;  // 代表正常状态下不打折的价格
};

// 派生类 Bulk_quote
class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double p, std::size_t qty, double disc) 
        : Quote(book, p), min_qty(qty), discount(disc) {}

    // 重写 net_price 方法，计算批量购买的价格
    double net_price(std::size_t cnt) const override {
        if (cnt >= min_qty) {
            return cnt * (1 - discount) * price;
        } else {
            return cnt * price;
        }
    }

    // 重写 clone 方法，返回当前对象的拷贝
    Bulk_quote* clone() const & { return new Bulk_quote(*this); }
    Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); }

private:
    std::size_t min_qty = 0;  // 适用折扣的最小购买数量
    double discount = 0.0;    // 折扣
};

// 计算书籍总价的函数
double print_total(const Quote& item, std::size_t n) {
    double ret = item.net_price(n);
    std::cout << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}

int main() {
    // 创建两个对象
    Quote q("Book1", 50.0);
    Bulk_quote bq("Book2", 50.0, 10, 0.2);

    // 用于存储克隆的对象
    std::vector<std::unique_ptr<Quote>> basket;

    // 将对象克隆后加入 basket 中
    basket.push_back(std::unique_ptr<Quote>(q.clone()));  // 拷贝 Quote 对象
    basket.push_back(std::unique_ptr<Quote>(bq.clone())); // 拷贝 Bulk_quote 对象

    // 遍历 basket，输出每个对象的 net_price
    for (const auto& item : basket) {
        print_total(*item, 20);
    }

    return 0;
}
