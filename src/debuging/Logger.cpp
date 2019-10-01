#include "Logger.h"

Logger& Logger::Get() {
    static Logger instance;

    return instance;
}

Logger::Logger() {

}
