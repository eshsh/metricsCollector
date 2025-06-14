#pragma once

#include <chrono>
#include <memory>

#include "ioutputstream.h"

namespace statistics {
class IStatisticsData;
class StatScheduler {
public:
    static StatScheduler& Instance();
    ~StatScheduler() = default;
    void RegisterStat(std::shared_ptr<IStatisticsData> stat);
    void SetOutput(std::unique_ptr<IOutputStream> output);
    void SetPeriod(std::chrono::seconds period);
    void Start();

private:
    StatScheduler();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;

};
} // namespace statistics
