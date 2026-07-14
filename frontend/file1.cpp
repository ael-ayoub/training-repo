#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Widget {
public:
    Widget(std::string label, int width, int height)
        : label_(std::move(label)), width_(width), height_(height) {}

    void render() const {
        std::cout << "[" << label_ << "] " << width_ << "x" << height_ << "\n";
    }

    int area() const { return width_ * height_; }

private:
    std::string label_;
    int width_;
    int height_;
};

class Layout {
public:
    void addWidget(std::unique_ptr<Widget> widget) {
        widgets_.push_back(std::move(widget));
    }

    void renderAll() const {
        for (const auto &w : widgets_) {
            w->render();
        }
    }

    int totalArea() const {
        int sum = 0;
        for (const auto &w : widgets_) {
            sum += w->area();
        }
        return sum;
    }

private:
    std::vector<std::unique_ptr<Widget>> widgets_;
};

int main() {
    Layout layout;
    layout.addWidget(std::make_unique<Widget>("Header", 800, 60));
    layout.addWidget(std::make_unique<Widget>("Sidebar", 200, 600));
    layout.addWidget(std::make_unique<Widget>("Content", 600, 600));

    layout.renderAll();
    std::cout << "Total area: " << layout.totalArea() << "\n";

    return 0;
}
