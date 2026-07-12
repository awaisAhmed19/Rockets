#include "App/Application.h"
#include "Engine/Core/Logger.h"
int main() {
  Logger::init("runtime.log");
  App app;
  app.start();

  return 0;
}
