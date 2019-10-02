#include "Win32Logger.h"

Logger& Logger::Instance() {
    static Logger instance;

    return instance;
}

void Logger::InfoLog(int color, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Info)) {
        SetConsoleTextAttribute(m_ConsoleHandle, color);

        va_list argptr;
        va_start(argptr, format);
        vfprintf(stderr, format, argptr);
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, 15);
    }
}

void Logger::InfoLog(int color, EPriority priority, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Info) && m_PriorityLevel <= priority) {
        SetConsoleTextAttribute(m_ConsoleHandle, color);

        va_list argptr;
        va_start(argptr, format);
        vfprintf(stderr, format, argptr);
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, 15);
    }
}

void Logger::WarningLog(int color, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Warning)) {
        SetConsoleTextAttribute(m_ConsoleHandle, color);

        va_list argptr;
        va_start(argptr, format);
        vfprintf(stderr, format, argptr);
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, 15);
    }
}

void Logger::WarningLog(int color, EPriority priority, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Warning) && m_PriorityLevel <= priority) {
        SetConsoleTextAttribute(m_ConsoleHandle, color);

        va_list argptr;
        va_start(argptr, format);
        vfprintf(stderr, format, argptr);
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, 15);
    }
}

void Logger::ErrorLog(int color, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Error)) {
        SetConsoleTextAttribute(m_ConsoleHandle, color);

        va_list argptr;
        va_start(argptr, format);
        vfprintf(stderr, format, argptr);
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, 15);
    }
}

void Logger::ErrorLog(int color, EPriority priority, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Error) && m_PriorityLevel <= priority) {
        SetConsoleTextAttribute(m_ConsoleHandle, color);

        va_list argptr;
        va_start(argptr, format);
        vfprintf(stderr, format, argptr);
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, 15);
    }
}

Logger::Logger() {
    m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    m_ChannelMask = EChannel::Info | EChannel::Warning | EChannel::Error;
    m_PriorityLevel = EPriority::Low;
}