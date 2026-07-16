#pragma once
#include "Logger.h"
namespace Cmd {
void parse(int argc, char *argv[]) {
  int i = 0;
  while (i < argc) {
    std::string_view msg{argv[i]};
    Logger::log(LogLevel::INFO, msg);
    i++;
  }
}
}; // namespace Cmd
