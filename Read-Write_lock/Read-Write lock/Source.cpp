#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class RWLock {
public:
    template<class Func>
    void read(Func func) {
        unique_lock<mutex> lock(read_);
        read_.lock();
        while (writer_waiting > 0 || writer_active == true) {
            cv.wait(lock);
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
        unique_lock<mutex> lock(read_);
        read_.lock();
        writer_waiting++;
        while (writer_waiting > 0 || writer_active == true) {
            cv.wait(lock);
        }
        writer_waiting--;
        writer_active = true;
        read_.unlock();
        func();
        read_.lock();
        writer_active = false;
        cv.notify_one();
        read_.unlock();
    }

private:
    int readers_active = 0;
    int writer_waiting = 0;
    bool writer_active = false;
    std::mutex read_;
    std::condition_variable cv;

};

int main() {
    RWLock rw;
    std :: cout << "yes";
    cout << "no";
}