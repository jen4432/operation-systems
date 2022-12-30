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
        while (wraiter_waiting > 0 || writer_active) {
            cv.wait();
        }
        readers_active++;
        read_.unlock();
        func();
        read_.lock();
        readers_active--;
        if (readers_active == 0) {
            cv.notify_one();
        }
        read_.unlock();
    }

    template<class Func>
    void write(Func func) {
        unique_lock<mutex> lock(write_);
        read_.lock();
        wraiter_waiting--;
        while (wraiter_waiting > 0 || writer_active == true) {
            cv.wait(lock);
        }
        wraiter_waiting--;
        writer_active = true;
        read_.unlock();
        
        read_.lock();
        writer_active = false;
        cv.notify_one();
        read_.unlock();
    }

private:
    int readers_active = 0;
    int wraiter_waiting = 0;
    bool writer_active = false;
    std::mutex read_;
    std::mutex write_;
    int blocked_readers_ = 0;
    std::condition_variable cv;

};

int main() {
    RWLock rw;
    std :: cout << "yes";
}