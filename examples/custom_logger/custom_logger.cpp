#include <iostream>
#include <memory>
#include <thread>

#include "../include/statistics/httpstatistic.h"
#include "../include/statistics/cpustatistics.h"
#include "../include/statistics.h"
#include "customlogger.h"

int main() {
    std::shared_ptr<statistics::http::Statistics> http = std::make_shared<statistics::http::Statistics>();
    statistics::RegisterStat(http);
    statistics::SetStatOutput(std::make_unique<SpdLogger>());
    statistics::Start();

    std::thread httpThread([http]() {
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
            http->Increment();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    httpThread.join();

    return 0;
}
