#include "Win32Logger.h"

Logger& Logger::Get() {
    static Logger instance;

    return instance;
}

void Logger::InfoLog(int color, const char* format, ...) {

}

void Logger::InfoLog(int color, EPriority priority, const char* format, ...) {

}

Logger::Logger() {
    m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    m_ChannelMask = static_cast<EChannel>(EChannel::Info | EChannel::Warning | EChannel::Error);
}

void Logger::Log(int color, const char* format, ...) {
    SetConsoleTextAttribute(m_ConsoleHandle, color);

    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, format, argptr);
    va_end(argptr);

    // Return to default state white text on black background
    SetConsoleTextAttribute(m_ConsoleHandle, 15);
}
