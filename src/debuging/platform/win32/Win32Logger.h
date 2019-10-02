#ifdef _WIN32
#ifndef Win32Logger_h
#define Win32Logger_h

#include "../../../core/Enum.h"

#include <iostream>
#include <Windows.h>

class Logger {
public:
    enum class EPriority {
        High = 2,
        Medium = 1,
        Low = 0
    };

    enum class EChannel : unsigned char {
        Info = 0x4,
        Warning = 0x2,
        Error = 0x1
    };

    static Logger& Instance();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    ~Logger() = default;

    void Push(EChannel channel);
    void Pop(EChannel channel);

    void PriorityLevel(EPriority level) { m_PriorityLevel = level; }

    void InfoLog(int color, const char* format, ...);
    void InfoLog(int color, EPriority priority, const char* format, ...);

    void WarningLog(int color, const char* format, ...);
    void WarningLog(int color, EPriority priority, const char* format, ...);

    void ErrorLog(int color, const char* format, ...);
    void ErrorLog(int color, EPriority priority, const char* format, ...);

private:
    Logger();

    HANDLE m_ConsoleHandle;
    EChannel m_ChannelMask;
    EPriority m_PriorityLevel;
};
ENABLE_BITMASK_OPERATORS(Logger::EChannel);

#endif
#endif