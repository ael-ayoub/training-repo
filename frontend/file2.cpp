#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>

class EventBus {
public:
    using Handler = std::function<void(const std::string &)>;

    void subscribe(const std::string &event, Handler handler) {
        handlers_[event].push_back(std::move(handler));
    }

    void emit(const std::string &event, const std::string &payload) {
        auto it = handlers_.find(event);
        if (it == handlers_.end()) return;
        for (auto &h : it->second) {
            h(payload);
        }
    }

private:
    std::unordered_map<std::string, std::vector<Handler>> handlers_;
};

class Button {
public:
    Button(std::string id, EventBus &bus) : id_(std::move(id)), bus_(bus) {}

    void click() {
        std::cout << "Button " << id_ << " clicked\n";
        bus_.emit("click", id_);
    }

private:
    std::string id_;
    EventBus &bus_;
};

int main() {
    EventBus bus;

    bus.subscribe("click", [](const std::string &id) {
        std::cout << "Handler A received click from " << id << "\n";
    });

    bus.subscribe("click", [](const std::string &id) {
        std::cout << "Handler B logging click: " << id << "\n";
    });

    Button submitBtn("submit-btn", bus);
    Button cancelBtn("cancel-btn", bus);

    submitBtn.click();
    cancelBtn.click();

    return 0;
}
