#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class Counter {
    public:
    Counter() : count(0) {};
    
    void increase_count_by_1() {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        ++count;
    }
    
    void show() {
        std::cout << "count = " << count << std::endl;
    }
    
    private:
    unsigned int count;
    std::mutex mtx; // Mutex to protect count
};

void counter_fn(Counter& counter, size_t loop) {
    for (size_t i=0; i < loop; ++i) {
        counter.increase_count_by_1();
    }
}

int main() {
    Counter cnt;
    const int numThreads = 10;
    std::vector<std::thread> threads;
    
    //10 threads - execute counter_fn(cnt, 1000000)
      // Create 10 threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(counter_fn, std::ref(cnt), 1000000);
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }
    
    cnt.show();
    return 0;
}