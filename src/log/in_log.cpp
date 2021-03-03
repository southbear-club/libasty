/**
 * @file in_log.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-03-03
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "in_log.hpp"
#include "../libasty.hpp"

namespace asty {

namespace log {

// 内部日志
static LogFilter log_filter;

LogFilter *get_log_filter(void) { return &log_filter; }

}  // namespace log

}  // namespace asty

namespace asty {

namespace lib {

// 一键设置日志等级
void set_log_level(asty::log::LogLevel level) {
#define XX(m, name) name,
    const char *logs[] = {LIBASTY_MODULE_TABLE(XX)};
#undef XX

    for (auto item : logs) {
        asty::log::log_filter.set_module_level(item, level);
    }
}

// 设置单个模块日志等级
void set_log_level(const std::string &module_name, asty::log::LogLevel level) {
    asty::log::log_filter.set_module_level(module_name, level);
}

}  // namespace lib

}  // namespace asty
