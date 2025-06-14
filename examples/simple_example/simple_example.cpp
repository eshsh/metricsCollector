#include <iostream>
#include <memory>
#include <thread>

#include "../include/statistics/httpstatistic.h"
#include "../include/statistics/cpustatistics.h"
#include "../include/statistics.h"
#include "../include/filelogger.h"

int main() {
    std::shared_ptr<statistics::http::Statistics> http = std::make_shared<statistics::http::Statistics>();
    std::shared_ptr<statistics::cpu::Statistics> cpu = std::make_shared<statistics::cpu::Statistics>();
    statistics::RegisterStat(http);
    statistics::RegisterStat(cpu);

    auto file_logger = std::make_unique<FileLogger>();
    if (file_logger->Open("test_out.txt")) {
        statistics::SetStatOutput(std::move(file_logger));
    } else {
        std::cout << "Error open file, using default logger \n";
    }

    statistics::Start();

    std::thread httpThread([http]() {
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
            http->Increment();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    std::thread cpuThread([cpu]() {
        auto start = std::chrono::steady_clock::now();
        double fake_cpu_usage = 0.0;
        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
            fake_cpu_usage++;
            cpu->SetLoad(fake_cpu_usage);
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    });

    httpThread.join();
    cpuThread.join();

    return 0;
}
