/**
 * @file ut_log.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-03-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#define ASTY_LOG_MODULE_NAME "log"
#include "gtest/gtest.h"

#include "ut_log.hpp"

static asty::log::LogFilter log_filter;

asty::log::LogFilter *get_log_filter(void) {
    return &log_filter;
}

TEST(Log, Log) {
    UT_LOG(INFO) << "info...\n";
    UT_LOG(WARNING) << "warning...\n";
    UT_LOG(ERROR) << "error...\n";
    UT_LOG(FATAL) << "fatal...\n";
}