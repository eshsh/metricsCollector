#pragma once
#include <string>
#include <iostream>
#include "../../include/ioutputstream.h"
#include <spdlog/spdlog.h>

class SpdLogger : public IOutputStream {
public:
    SpdLogger() = default;
    ~SpdLogger() override = default;
    void Log(std::string message) override {
        spdlog::info("{}", message);
    }
};
