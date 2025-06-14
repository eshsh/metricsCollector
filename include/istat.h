#pragma once
#include <string>

namespace statistics {
struct IStatisticsData {
    virtual ~IStatisticsData() = default;
    virtual std::string ToString() const = 0;
    virtual void Reset() = 0;
};
} // namespace statistics
