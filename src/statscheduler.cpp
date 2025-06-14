#include "../include/statscheduler.h"
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <ctime>
#include <sstream>
#include <iomanip>

#include "../include/istat.h"
#include "../include/consolelogger.h"

namespace statistics {

class StatScheduler::Impl {
public:
    void RegisterStat(std::shared_ptr<IStatisticsData> stat) {
        std::lock_guard<std::mutex> lock(mutex_);
        statistics_.emplace_back(stat);
    }

    ~Impl() {
        Stop();
    }

    void SetOutput(std::unique_ptr<IOutputStream> output) {
        std::lock_guard<std::mutex> lock(mutex_);
        output_ = std::move(output);
    }

    void SetPeriod(std::chrono::seconds period) {
        std::lock_guard<std::mutex> lock(mutex_);
        period_ = period;
    }

    void Start() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!output_) {
            output_ = std::make_unique<ConsoleLogger>();
        }

        if (!worker_.joinable()) {
            worker_ = std::thread([this]() { Run(); });
        }
    }
private:
    void Stop() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stop_ = true;
        }
        cv_.notify_all();

        if (worker_.joinable()) {
            worker_.join();
        }
    }

    void Run() {
        try {
            std::unique_lock<std::mutex> lock(mutex_);
            while (!stop_) {
                auto stats_copy = statistics_;
                auto output_copy = output_.get();
                auto period_copy = period_;

                lock.unlock();

                auto now = std::chrono::system_clock::now();
                auto in_time_t = std::chrono::system_clock::to_time_t(now);

                std::stringstream ss;
                ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

                for (const auto& wstat : stats_copy) {
                    if (auto stat = wstat.lock()) {
                        ss << ' ' << stat->ToString();
                        stat->Reset();
                    }
                }
                ss << "\n";
                output_copy->Log(ss.str());

                lock.lock();
                cv_.wait_for(lock, period_copy, [this]() { return stop_; });
            }
        } catch (const std::exception& ex) {
            std::cout << "[StatScheduler] " << ex.what() << std::endl;
        }
    }
private:
    std::vector<std::weak_ptr<IStatisticsData>> statistics_;
    std::mutex mutex_;
    std::thread worker_;
    bool stop_ = false;
    std::unique_ptr<IOutputStream> output_;
    std::chrono::seconds period_ {1};
    std::condition_variable cv_;
};


StatScheduler &statistics::StatScheduler::Instance() {
    static StatScheduler scheduler;
    return scheduler;
}

StatScheduler::StatScheduler()
    : impl_(std::make_unique<Impl>()) {}

void StatScheduler::RegisterStat(std::shared_ptr<IStatisticsData> stat) {
    impl_->RegisterStat(std::move(stat));
}

void StatScheduler::SetOutput(std::unique_ptr<IOutputStream> output) {
    impl_->SetOutput(std::move(output));
}

void StatScheduler::SetPeriod(std::chrono::seconds period) {
    impl_->SetPeriod(period);
}

void StatScheduler::Start() {
    impl_->Start();
}
} //namespace statistics
