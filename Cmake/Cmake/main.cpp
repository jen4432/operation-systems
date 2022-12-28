#pragma once

#include <string>
#include <iostream>

class Solver {
public:
    Solver(const std::string& filename, size_t thread_count);
    void Run();

private:
    std::string filename_;
    size_t thread_count_;
};

int main() {
    std :: cout << "type F to start";

    std :: string line = "";

    while (line != "F") {
        std :: cin >> line;
    }

    Solver solver("numbers.txt", 3);
    solver.Run();

    while (true) {

    }

}