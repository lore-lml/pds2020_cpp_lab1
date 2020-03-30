#pragma once
#include <string>
#include <ctime>
class DurationLogger {
    std::string name;
    clock_t start;
public:
    DurationLogger(std::string  name);
    ~DurationLogger();
};
