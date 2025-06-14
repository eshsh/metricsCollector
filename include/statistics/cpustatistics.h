#pragma once
#include <atomic>
#include "../istat.h"

namespace statistics {
namespace cpu {
struct Statistics final : public IStatisticsData {
    ~Statistics() = default;
    std::string ToString() const override {
        return "\"CPU\" " + std::to_string(count_.load());
    }
    void Reset() override {
        count_.store(0);
    }
    void SetLoad(double load) {
        count_ = load;
    }

private:
    std::atomic<double> count_{0};
};

} //namespace cpu
} //namespace statistics
