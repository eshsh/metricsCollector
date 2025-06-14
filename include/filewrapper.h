#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

enum class OpenMode { Read, Write };
enum class SeekDir { Begin, End };

class FileWrapper {
public:
    FileWrapper();
    ~FileWrapper();
    bool Open(const char* filepath, OpenMode mode);
    void Close();
    size_t Read(void* buffer, size_t size);
    size_t Write(const void* buffer, size_t size);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
