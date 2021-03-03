/**
 * @file in_log.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-03-03
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "log.hpp"

namespace asty {

namespace log {

LogFilter *get_log_filter(void);

#define ASTY_IN_LOG(severity) ASTY_LOG(severity, get_log_filter())

}  // namespace log

}  // namespace asty
