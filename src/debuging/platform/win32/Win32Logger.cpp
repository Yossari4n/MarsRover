#include "Win32Logger.h"

Logger& Logger::Instance() {
    static Logger instance;

    return instance;
}

Logger::Logger() {
    m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    m_ChannelMask = EChannel::Info | EChannel::Warning | EChannel::Error;
}

void Logger::Push(EChannel channel) {
    m_ChannelMask = m_ChannelMask | channel;
}

void Logger::Pop(EChannel channel) {
    m_ChannelMask = m_ChannelMask | (~channel);
}

void Logger::InfoLog(ESender sender, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Info)) {
        va_list argptr;
        va_start(argptr, format);
        Log(static_cast<WORD>(sender), format, argptr);
        va_end(argptr);
    }
}

void Logger::WarningLog(ESender sender, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Warning)) {
        va_list argptr;
        va_start(argptr, format);
        Log(static_cast<WORD>(sender), format, argptr);
        va_end(argptr);
    }
}

void Logger::ErrorLog(ESender sender, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Error)) {
        va_list argptr;
        va_start(argptr, format);
        Log(static_cast<WORD>(sender), format, argptr);
        va_end(argptr);
    }
}

void Logger::Log(WORD color, const char* format, va_list list) {
    SetConsoleTextAttribute(m_ConsoleHandle, color);

    vfprintf(stdout, format, list);
    printf("\n");

    // Return to default state white text on black background
    SetConsoleTextAttribute(m_ConsoleHandle, 15);
}
