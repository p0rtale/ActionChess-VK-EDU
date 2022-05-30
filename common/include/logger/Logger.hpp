#pragma once

#include <chrono>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>

enum class LogType {
    ERROR,
    INFO
};

class Logger final { 
public:
    Logger(const char* filename) {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_os.open(filename, std::ofstream::out);
    }

    ~Logger() {
        std::lock_guard<std::mutex> guard(m_mutex);
        if (m_os.is_open()) {
            m_os.close();
        }
    }

    template<class ...Args>
    void write(const LogType type, Args&&... args) {
        std::lock_guard<std::mutex> guard(m_mutex);

        std::stringstream ss;
        auto now = std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now());
        ss << std::put_time(std::localtime(&now), "%Y-%m-%d %X");

        m_os << ss.str() << " ";
        switch(type) {
            case LogType::ERROR:
                m_os << "ERROR: ";
                break;
            case LogType::INFO:
                m_os << "INFO: ";
                break;
            default: 
                break;
        }

        ((m_os << " " << std::forward<Args>(args)), ...);
        m_os << std::endl;
    }

private:
    std::ofstream m_os;  // Guarded by m_mutex

    std::mutex m_mutex;
};
