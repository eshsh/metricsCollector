#include "../include/statistics.h"
#include "../include/statscheduler.h"

namespace statistics {
void RegisterStat(std::shared_ptr<IStatisticsData> stat) {
    StatScheduler::Instance().RegisterStat(std::move(stat));
}

void SetStatOutput(std::unique_ptr<IOutputStream> output) {
    StatScheduler::Instance().SetOutput(std::move(output));
}

void Start() {
    StatScheduler::Instance().Start();
}
} // namespace statistics
