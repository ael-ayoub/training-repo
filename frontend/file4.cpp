#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

template <typename T>
class ThreadSafeQueue {
public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(value));
        cv_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !queue_.empty(); });
        T value = std::move(queue_.front());
        queue_.pop();
        return value;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<T> queue_;
};

void producer(ThreadSafeQueue<int> &q, int count) {
    for (int i = 0; i < count; ++i) {
        q.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void consumer(ThreadSafeQueue<int> &q, int count) {
    for (int i = 0; i < count; ++i) {
        int value = q.pop();
        std::cout << "consumed: " << value << "\n";
    }
}

int main() {
    ThreadSafeQueue<int> queue;
    const int total = 20;

    std::thread producerThread(producer, std::ref(queue), total);
    std::thread consumerThread(consumer, std::ref(queue), total);

    producerThread.join();
    consumerThread.join();

    std::cout << "Done processing " << total << " items\n";
    return 0;
}
