#include <iostream>
#include <vector>
#include <memory> // For shared_ptr

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price)
        : bookNo(book), price(sales_price) {}

    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const {
        return n * price;
    }

    virtual ~Quote() = default;

protected:
    double price = 0.0;

private:
    std::string bookNo;
};

class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double sales_price, std::size_t qty, double disc)
        : Quote(book, sales_price), min_qty(qty), discount(disc) {}

    double net_price(std::size_t n) const override {
        if (n >= min_qty)
            return n * (1 - discount) * price;
        else
            return n * price;
    }

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

// Function to calculate total net price for a vector of Quotes
double print_total(const std::vector<std::shared_ptr<Quote>> &basket, std::size_t quantity) {
    double total = 0.0;
    for (const auto &item : basket) {
        total += item->net_price(quantity);
    }
    return total;
}

int main() {
    // Create a vector to store Quote and Bulk_quote objects
    std::vector<std::shared_ptr<Quote>> basket;

    // Add a Quote and Bulk_quote to the vector
    basket.push_back(std::make_shared<Quote>("12345", 50.0));
    basket.push_back(std::make_shared<Bulk_quote>("12345", 50.0, 10, 0.2));

    // Calculate the total net price for a certain quantity
    std::size_t quantity = 15;
    double total = print_total(basket, quantity);

    std::cout << "Total net price for quantity " << quantity << " is: " << total << std::endl;

    return 0;
}
