#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
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

int main() {
    std::vector<char>::size_type BLOCK_SIZE = 1024;
    std::ifstream is("file.txt", std::ios::binary);

    Queue<std::vector<char>> q;

    auto readChunk = [&BLOCK_SIZE](Queue<std::vector<char>>& q_, std::ifstream& is_) {
        while(!is_.eof()) {
            std::cout << "reading.." << std::endl;
            std::vector<char> c(BLOCK_SIZE);
            is_.read(c.data(), BLOCK_SIZE);
            for(auto const& l : c) {
                std::cout << l << std::endl;
            }
            q_.push(std::move(c));
        }
    };
    
    auto printChunk = [](Queue<std::vector<char>>& q_) {
        while(true) {
            auto item = q_.pop();
            //std::cout << item[0] << std::endl;
        }
    };

    std::thread producer(readChunk, std::ref(q), std::ref(is));
    std::thread consumer(printChunk, std::ref(q));

    producer.join();
    consumer.join();

    return 0;
}
