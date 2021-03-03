/**
 * @file ut_log.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-03-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "log/log.hpp"

asty::log::LogFilter *get_log_filter(void);

#define UT_LOG(severity) ASTY_LOG(severity, get_log_filter())