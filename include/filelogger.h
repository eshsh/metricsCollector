#pragma once
#include <string>
#include "ioutputstream.h"
#include "filewrapper.h"
#include <iostream>

class FileLogger : public IOutputStream {
public:
    FileLogger() = default;
    ~FileLogger() override = default;

    bool Open(const std::string& file_name) {
        return file_.Open(file_name.c_str(), OpenMode::Write);
    }
    void Log(std::string message) override {
        file_.Write(message.c_str(), message.size());
    }

private:
    FileWrapper file_;
};
