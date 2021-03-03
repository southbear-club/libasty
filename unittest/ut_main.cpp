/**
 * @file ut_main.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-03-02
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "gtest/gtest.h"

#include "ut_log.hpp"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

class AstyEnvironment : public testing::Environment {
public:
    virtual void SetUp() {
        std::cout << "AstyEnvironment SetUp" << std::endl;
        std::vector<asty::log::LogConfig> logs = {
            {"main", asty::log::LOG_INFO},
            {"log", asty::log::LOG_INFO},
            {"memory", asty::log::LOG_INFO},
        };

        get_log_filter()->setup_log(logs);
    }
    virtual void TearDown() { std::cout << "AstyEnvironment TearDown" << std::endl; }

};

int main(int argc, char** argv) {
    testing::AddGlobalTestEnvironment(new AstyEnvironment);
    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}