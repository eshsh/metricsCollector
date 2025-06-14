#pragma once
#include <memory>

struct IStatisticsData;
struct IOutputStream;

namespace statistics {
void RegisterStat(std::shared_ptr<IStatisticsData> stat);
void SetStatOutput(std::unique_ptr<IOutputStream> output);
void Start();
} // namespace statistics
