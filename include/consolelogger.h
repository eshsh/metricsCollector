#pragma once
#include <string>
#include <iostream>
#include "ioutputstream.h"

class ConsoleLogger : public IOutputStream {
public:
    ConsoleLogger() = default;
    ~ConsoleLogger() override = default;
    void Log(std::string message) override {
        std::cout << message;
    }
};
