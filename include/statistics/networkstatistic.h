#pragma once
#include "../istat.h"

namespace statistics {
namespace network {
struct Statistics final : public IStatisticsData {
    Statistics();
    ~Statistics() = default;
    std::string ToString() const override {
        return "\"Network bytes received\" " + std::to_string(bytes_);
    }
    void Reset() override {
        bytes_ = 0;
    }
    void AddBytes(uint64_t bytes) {
        bytes_ += bytes;
    }

private:
    uint64_t bytes_ = 0;
};

} //namespace network
} //namespace statistics
