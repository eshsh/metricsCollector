#pragma once
#include "../istat.h"
#include "../statscheduler.h"

namespace statistics {
namespace http {
struct Statistics final : public IStatisticsData {
    ~Statistics() = default;
    std::string ToString() const override {
        return "\"HTTP requests rpc\" " + std::to_string(count_);
    }
    void Reset() override {
        count_ = 0;
    }
    void Increment() {
        count_++;
    }

private:
    uint64_t count_ = 0;
};

} //namespace cpu
} //namespace statistics
