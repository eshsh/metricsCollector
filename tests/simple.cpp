#include <gtest/gtest.h>

#include "../include/filelogger.h"

TEST(StatisticsTest, createFile) {
    const char* file_name = "test_out.txt";
    auto file_logger = std::make_unique<FileLogger>();
    bool is_openned = file_logger->Open(file_name);
    EXPECT_EQ(is_openned, true);
    std::remove(file_name);
}
