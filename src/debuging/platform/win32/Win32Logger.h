#ifdef _WIN32
#ifndef Win32Logger_h
#define Win32Logger_h

#include "../../../core/Enum.h"

#include <iostream>
#define NOMINMAX
#include <Windows.h>

class Logger {
public:
    enum class EChannel : unsigned char {
        Info = 0x4,
        Warning = 0x2,
        Error = 0x1
    };

    // Windows specific codes for colors
    // Don't add beyond white
    enum class ESender : WORD {
        CBS = 1,        // Blue
        Rendering = 2,  // Green
        Resources = 3,  // Cyan

        None = 15       // White
    };

    static Logger& Instance();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    ~Logger() = default;

    void Push(EChannel channel);
    void Pop(EChannel channel);

    void InfoLog(ESender sender, const char* format, ...);
    void WarningLog(ESender sender, const char* format, ...);
    void ErrorLog(ESender sender, const char* format, ...);

private:
    Logger();

    void Log(WORD color, const char* format, va_list list);

    HANDLE m_ConsoleHandle;
    EChannel m_ChannelMask;
};
ENABLE_BITMASK_OPERATORS(Logger::EChannel);
ENABLE_BITMASK_OPERATORS(Logger::ESender);

#endif
#endif
