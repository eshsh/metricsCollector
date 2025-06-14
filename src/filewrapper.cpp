#include "../include/filewrapper.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cerrno>
#include <cstring>

constexpr const char* kFileWrapperTag = "[FileWrapper]  ";

class FileWrapper::Impl {
public:
    Impl() {}
    ~Impl() {
        Close();
    }

    bool Open(const char* filepath, OpenMode mode) {
        Close();

        const char* modeStr = nullptr;
        switch (mode) {
        case OpenMode::Read:
            modeStr = "rb";
            break;
        case OpenMode::Write:
            modeStr = "wb";
            break;
        }

        file_ = std::fopen(filepath, modeStr);
        if (file_) {
            std::cout << kFileWrapperTag << "file " << filepath << " successfully opened" << std::endl;
            return true;
        }
        std::cerr << kFileWrapperTag << "error opening file " << filepath
                  << ": " << std::strerror(errno) << std::endl;

        return false;
    }

    void Close() {
        if (file_) {
            std::fflush(file_);
            std::fclose(file_);
            file_ = nullptr;
        }
    }

    size_t Write(const void* buffer, size_t size) {
        if (!file_) {
            return 0;
        }
        return std::fwrite(buffer, 1, size, file_);
    }

    size_t Read(void* buffer, size_t size) {
        if (!file_) {
            return 0;
        }
        return std::fread(buffer, 1, size, file_);
    }

private:
    std::string filepath_;
    OpenMode mode_ = OpenMode::Read;
    FILE* file_ = nullptr;
};

FileWrapper::FileWrapper()
    : impl_(std::make_unique<Impl>()) {}

FileWrapper::~FileWrapper() {
    Close();
}

bool FileWrapper::Open(const char* filepath, OpenMode mode) {
    return impl_->Open(filepath, mode);
}

void FileWrapper::Close() {
    impl_->Close();
}

size_t FileWrapper::Read(void* buffer, size_t size) {
    return impl_->Read(buffer, size);
}

size_t FileWrapper::Write(const void* buffer, size_t size) {
    return impl_->Write(buffer, size);
}
