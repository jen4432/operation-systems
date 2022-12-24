#pragma once
#include <mutex>
#include <condition_variable>

class RWLock {
public:
    template<class Func>
    void read(Func func) {
        read_.lock();
        blocked_readers_++;
        read_.unlock();
        func();
        if (blocked_readers_ == 0) {
            cv.notify_one();
        }
        
    }

    template<class Func>
    void write(Func func) {
        unique_lock<mutex> lock(write_);
        while (!flag) {
            cv.wait(read_);
        }
        func();
    }

private:
    std::mutex read_;
    std::mutex write_;
    int blocked_readers_ = 0;
    bool flag = false;
    std::condition_variable cv;

 
};