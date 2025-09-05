#include "Application.h"
#include "Logger.h"

int main() {

  // Initialize Logger
  Logger::setConfig(Logger::Config{false, true, false, true});
  INFO("Logger ready!");
  
  // Application entry point
  Raze::Application app;
  app.run();

  return 0;
}

