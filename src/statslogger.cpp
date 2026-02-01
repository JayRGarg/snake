#include "statslogger.h"
#include <mutex>
#include <thread>
#include <utility>

StatsLogger::StatsLogger(std::filesystem::path log_path, Uint32 start_time_ms) : _log_path(std::move(log_path)), _start_time_ms(start_time_ms) {
    _thread = std::thread(&StatsLogger::listener, this);
}

StatsLogger::~StatsLogger() {
    std::unique_lock<std::mutex> lock(_mtx);
    _stop_logging = true;
    _cv.notify_one();
    lock.unlock();
    if (_thread.joinable()) {
        _thread.join();
    }
};


void StatsLogger::queueEvent(Event&& event) {
    std::unique_lock<std::mutex> lock(_mtx);
    _event_queue.emplace_back(std::move(event));
    lock.unlock();
    _cv.notify_one();
}

void StatsLogger::logEvent(const Event& event) {
    std::ofstream out(_log_path, std::ios::app);
    if (!out) {
        std::cerr << "Could not write to file: " << _log_path << std::endl;
    }
    Uint32 relative_time = event.timestamp_ms - _start_time_ms;
    out << "time_ms=" << relative_time << ":message=" << event.message << std::endl;
}

void StatsLogger::listener() {
    while (true) {
        std::unique_lock<std::mutex> lock(_mtx);
        _cv.wait(lock, [this] () { return _stop_logging || !_event_queue.empty(); });

        if (_stop_logging && _event_queue.empty()) {
            break;
        }

        Event event = _event_queue.front();
        _event_queue.pop_front();
        lock.unlock();
        logEvent(event);
    }
}
