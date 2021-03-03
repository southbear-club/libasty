/**
 * @file log.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-03-01
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <map>
#include <string>
#include <vector>

// 自定义输出接口
// 使用glog时直接配置为LOG(severity)
#ifndef LIBASTY_LOG_STREAM
#include <stdio.h>
#include <time.h>
#include <iostream>

namespace asty {

namespace log {

static inline std::string libasty_log_timespec(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    struct tm *tm = nullptr;
    tm = localtime(&ts.tv_sec);
    char buf[32] = "";
    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d.%03ld", tm->tm_year + 1900, tm->tm_mon + 1,
            tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, ts.tv_nsec / 1000 / 1000);

    return buf;
}

}  // namespace log

}  // namespace asty

#define LIBASTY_LOG_STREAM(severity)                                                           \
    std::cout << "" << asty::log::libasty_log_timespec() << " " << __FILE__ << ":" << __LINE__ \
              << ":" << __func__ << "]["                                                       \
              << asty::log::LogLevelName::level_names[asty::log::LogLevel::LOG_##severity] << "]"
#endif  // !LIBASTY_LOG_STREAM

#ifndef ASTY_LOG_MODULE_NAME
#define ASTY_LOG_MODULE_NAME "NON"
#endif

// 这里的日志接口需要指定日志实例，主要是能提供多个实例，建议实际使用时自己在对宏定义封装一次
#define ASTY_LOG(severity, log_object)                                      \
    if (asty::log::filter_log_level(log_object, ASTY_LOG_MODULE_NAME,       \
                                    asty::log::LogLevel::LOG_##severity)) { \
    } else                                                                  \
        LIBASTY_LOG_STREAM(severity) << "[" ASTY_LOG_MODULE_NAME "] "

namespace asty {

namespace log {

typedef enum {
    LOG_INFO = 0,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL,
} LogLevel;

/**
 * @brief 日志等级名称
 * @details 只能使用这些等级
 *
 */
struct LogLevelName {
    constexpr static const char *level_names[] = {"INFO", "WARNING", "ERROR", "FATAL"};
};

class LogFilter;
class LogFilterImpl;

struct LogConfig {
    std::string module_name;
    LogLevel level;
};

struct LogConfigEx {};

class LogFilter {
public:
    LogFilter();
    LogFilter(const std::vector<LogConfig> &conf, const LogConfigEx *conf_ex = nullptr);
    ~LogFilter();
    void setup_log(const std::vector<LogConfig> &conf, const LogConfigEx *conf_ex = nullptr);
    bool filter(const std::string &module_name, LogLevel level) const;
    bool set_module_level(const std::string &module_name, LogLevel level);
    void remove_module(const std::string &module_name);

private:
    LogFilterImpl *impl_;
};

// 过滤日志等级
bool filter_log_level(LogFilter *log, const char *module_name, LogLevel level);

}  // namespace log

}  // namespace asty
