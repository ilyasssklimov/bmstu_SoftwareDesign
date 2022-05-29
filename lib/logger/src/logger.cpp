#include "logger.h"


void log_info(const std::string& message)
{
    std::cout << "INFO: " << message << std::endl;
}


void log_error(const std::string& message)
{
    std::cout << "ERROR: " << message << std::endl;
}


void log_debug(const std::string& message)
{
    std::cout << "DEBUG: " << message << std::endl;
}
