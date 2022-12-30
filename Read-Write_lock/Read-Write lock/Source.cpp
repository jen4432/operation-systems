#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class RWLock {
public:
    template<class Func>
    void read(Func func) {
        read_.lock();
        blocked_readers_++;
        mut_flag.lock();
        flag = false;
        mut_flag.unlock();
        read_.unlock();
        func();
        read_.lock();
        blocked_readers_--;
        read_.unlock();
        if (blocked_readers_ == 0) {
            cv.notify_one();
            mut_flag.lock();
            flag = true;
            mut_flag.unlock();
        }
        
    }

    template<class Func>
    void write(Func func) {
        unique_lock<mutex> lock(write_);
        while (!flag) {
            cv.wait(lock);
        }
        func();
    }

private:
    std::mutex mut_flag;
    std::mutex read_;
    std::mutex write_;
    int blocked_readers_ = 0;
    bool flag = false;
    std::condition_variable cv;

};

int main() {
    RWLock rw;
    std :: cout << "yes";
}