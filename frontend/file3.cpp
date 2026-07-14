#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Product {
    std::string name;
    double price;
    int stock;
};

class Cart {
public:
    void addProduct(const Product &p, int quantity) {
        items_.push_back({p, quantity});
    }

    double total() const {
        double sum = 0.0;
        for (const auto &item : items_) {
            sum += item.product.price * item.quantity;
        }
        return sum;
    }

    void applyDiscount(double percent) {
        discount_ = percent;
    }

    double finalTotal() const {
        return total() * (1.0 - discount_ / 100.0);
    }

    void printReceipt() const {
        std::cout << "----- Receipt -----\n";
        for (const auto &item : items_) {
            std::cout << item.product.name << " x" << item.quantity
                      << " = $" << (item.product.price * item.quantity) << "\n";
        }
        std::cout << "Subtotal: $" << total() << "\n";
        std::cout << "Discount: " << discount_ << "%\n";
        std::cout << "Total: $" << finalTotal() << "\n";
    }

private:
    struct CartItem {
        Product product;
        int quantity;
    };

    std::vector<CartItem> items_;
    double discount_ = 0.0;
};

int main() {
    Cart cart;
    cart.addProduct({"Keyboard", 49.99, 10}, 2);
    cart.addProduct({"Mouse", 19.99, 25}, 1);
    cart.addProduct({"Monitor", 199.99, 5}, 1);

    cart.applyDiscount(10.0);
    cart.printReceipt();

    return 0;
}
salma add this 
salma add this again