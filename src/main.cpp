#include "App/Application.h"
#include "Engine/Core/CmdParser.h"
#include "Engine/Core/Logger.h"
int main(int argc, char *argv[]) {
  Cmd::parse(argc, argv);
  Logger::init("runtime.log");
  // App app;
  // app.start();
  return 0;
}
