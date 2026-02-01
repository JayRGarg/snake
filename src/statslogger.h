#ifndef STATSLOGGER_H
#define STATSLOGGER_H

#include <condition_variable>
#include <deque>
#include <filesystem>
#include <mutex>
#include <string>
#include <thread>
#include <fstream>
#include <iostream>
#include "SDL.h"

struct Event {
    Uint32 timestamp_ms;
    std::string message;
};

class StatsLogger {
    public:
        StatsLogger(const std::filesystem::path& log_path, Uint32 start_time_ms);
        ~StatsLogger();
        StatsLogger(const StatsLogger&) = delete;
        StatsLogger& operator=(const StatsLogger&) = delete;
        StatsLogger(StatsLogger&&) = delete;
        StatsLogger& operator=(StatsLogger&&) = delete;
        void queueEvent(Event&& event);
        void logEvent(const Event& event);
        void listener();

    private:
        std::thread _thread;
        std::mutex _mtx;
        std::condition_variable _cv;
        bool _stop_logging = false;
        Uint32 _start_time_ms;
        const std::filesystem::path _log_path;
        std::deque<Event> _event_queue;
};

#endif
