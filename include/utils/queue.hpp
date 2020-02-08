#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Queue {
    std::mutex mutex_;
    std::queue<T> queue_;
    std::condition_variable cond;

    public:
        T pop () {
            std::unique_lock<std::mutex> mlock(mutex_);
            cond.wait(mlock, [this](){return !queue_.empty();});
            auto item = queue_.front();
            queue_.pop();
            return item;
        }
    
        void pop(T& item) {
            std::unique_lock<std::mutex> mlock(mutex_);
            cond.wait(mlock, [this](){return !queue_.empty();});
            item = queue_.front();
            queue_.pop();
        }

        void push(const T& item) {
            std::unique_lock<std::mutex> mlock(mutex_);
            queue_.push(item);
            mlock.unlock();
            cond.notify_one();
        }

        void push(T&& item) {
            std::unique_lock<std::mutex> mlock(mutex_);
            queue_.push(std::move(item));
            mlock.unlock();
            cond.notify_one();
        }

        bool empty() {
            std::unique_lock<std::mutex> mlock(mutex_);
            return queue_.empty();
        }
};