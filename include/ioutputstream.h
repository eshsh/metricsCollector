#pragma once
#include <string>

struct IOutputStream {
    virtual ~IOutputStream() = default;
    virtual void Log(std::string message) = 0;
};
