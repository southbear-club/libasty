/**
 * @file log.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-03-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "log.hpp"

namespace asty {

namespace log {

class LogFilterImpl {
public:
    LogFilterImpl() {

    }

    LogFilterImpl(const std::vector<LogConfig> &conf, const LogConfigEx *conf_ex=nullptr) {
        setup_log(conf, conf_ex);
    }

    ~LogFilterImpl() {
    }

    void setup_log(const std::vector<LogConfig> &conf, const LogConfigEx *conf_ex=nullptr) {
        for (auto &item : conf) {
            if (item.module_name.empty()) {
                continue;
            }
            module_map_level_[item.module_name] = item.level;
        }
    }

    bool filter(const std::string &module_name, LogLevel level) const {
        auto item = module_map_level_.find(module_name);
        if (item == module_map_level_.end()) {
            return true;
        }

        return level < item->second;
    }

    bool set_module_level(const std::string &module_name, LogLevel level) {
        if (module_name.empty()) {
            return false;
        }

        module_map_level_[module_name] = level;

        return true;
    }

    void remove_module(const std::string &module_name) {
        if (module_map_level_.end() == module_map_level_.find(module_name)) {
            return ;
        }

        module_map_level_.erase(module_name);
    }

private:
    std::map<std::string, LogLevel> module_map_level_;
};

LogFilter::LogFilter() {
    impl_ = new LogFilterImpl;
}

LogFilter::LogFilter(const std::vector<LogConfig> &conf, const LogConfigEx *conf_ex) : impl_(new LogFilterImpl(conf, conf_ex)) {

}

LogFilter::~LogFilter() {
    delete impl_;
}

void LogFilter::setup_log(const std::vector<LogConfig> &conf, const LogConfigEx *conf_ex) {
    impl_->setup_log(conf, conf_ex);
}

bool LogFilter::filter(const std::string &module_name, LogLevel level) const {
    return impl_->filter(module_name, level);
}

bool LogFilter::set_module_level(const std::string &module_name, LogLevel level) {
    return impl_->set_module_level(module_name, level);
}

void LogFilter::remove_module(const std::string &module_name) {
    impl_->remove_module(module_name);
}

bool filter_log_level(LogFilter *log, const char* module_name, LogLevel level)
{
    if (!log) {
        return true;
    }

    return log->filter(module_name, level);
}

}

}
