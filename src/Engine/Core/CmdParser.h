#pragma once

#include <optional>
#include <string>

namespace Cmd {

struct ParsedCLI {
  bool help = false;
  bool fullscreen = false;
  bool vsync = false;

  std::optional<int> width;
  std::optional<int> height;
  std::optional<std::string> scene;
};

ParsedCLI parse(int argc, char *argv[]);

void help();

} // namespace Cmd
