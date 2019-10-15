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
        SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(sender));

        va_list argptr;
        va_start(argptr, format);
        vfprintf(stdout, format, argptr);
        printf("\n");
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, 15);
    }
}

void Logger::WarningLog(ESender sender, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Warning)) {
        SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(sender));

        va_list argptr;
        va_start(argptr, format);
        printf("Warning: ");
        vfprintf(stdout, format, argptr);
        printf("\n");
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, 15);
    }
}

void Logger::ErrorLog(ESender sender, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Error)) {
        SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(sender));

        va_list argptr;
        va_start(argptr, format);
        printf("Error: ");
        vfprintf(stdout, format, argptr);
        printf("\n");
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, 15);
    }
}
