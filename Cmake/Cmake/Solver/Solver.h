#pragma once

#include <string>

class Solver {
public:
    Solver(const std::string& filename, size_t thread_count);
    void Run();

private:
    std::string filename_;
    size_t thread_count_;
};