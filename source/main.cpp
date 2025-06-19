#include "Logger.h"

int main() {
  Logger::setConfig(Logger::Config{true, true, true, true});
  INFO("Logger ready!");
  DEBUG("Test");
  ERROR("Test");
  WARN("Test");
  
}

