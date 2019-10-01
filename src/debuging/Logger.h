#ifndef Logger_h
#define Logger_h

class Logger {
public:
    static Logger& Get();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    ~Logger() = default;

private:
    Logger();
};


#endif
