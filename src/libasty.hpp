/**
 * @file libasty.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-03-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <string>
#include "log/log.hpp"

namespace asty {

namespace lib {

#define LIBASTY_MODULE_TABLE(XX) \
    XX(MEMORY, "memory-slab")        \
    XX(FRAMEWORK, "framework-microKernel")        \
    XX(FRAMEWORK, "framework-layer")        \
    XX(FRAMEWORK, "framework-module")        \
    XX(NET, "net-basic")

std::string version_string(void);

// 一键设置日志等级
void set_log_level(asty::log::LogLevel level);

// 设置单个模块日志等级
void set_log_level(const std::string &module_name, asty::log::LogLevel level);

} // namespace lib

} // namespace asty
