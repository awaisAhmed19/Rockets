#include "CmdParser.h"
#include "Engine/Core/Logger.h"
#include "Engine/Core/Utitlity/StringUtils.h"
#include <optional>
#include <stdexcept>
using namespace Engine;

namespace Cmd {

enum class ArgumentType { Flag, Integer, String };

struct Command {
  std::string name;
  ArgumentType type;
};

class CLIError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

std::vector<Command> commands = {
    {"--help", ArgumentType::Flag},      {"--fullscreen", ArgumentType::Flag},
    {"--vsync", ArgumentType::Flag},     {"--width", ArgumentType::Integer},
    {"--height", ArgumentType::Integer}, {"--scene", ArgumentType::String},
};

void help() {
  const std::string help = R"(

Rocket Simulator
================

Usage:
    rocket [options]

Options:
    --fullscreen           Start in fullscreen mode.
    --vsync                Enable vertical synchronization.
    --width <pixels>       Set the window width.
    --height <pixels>      Set the window height.
    --scene <file>         Load a scene file at startup.
    --help                 Display this help message.

Examples:
    rocket --fullscreen
    rocket --vsync
    rocket --width 1920 --height 1080
    rocket --scene sandbox.scene
    rocket --fullscreen --vsync --scene sandbox.scene

Notes:
    • Unknown arguments will produce an error.
    • Width and height must be positive integers.
    • If no options are provided, default engine settings are used.

)";
  Logger::log(LogLevel::INFO, help);
}

ParsedCLI parse(int argc, char *argv[]) {
  ParsedCLI cli;

  if (argc <= 1)
    return cli;

  auto args = String::make_string_vector(argc, argv);

  for (size_t i = 1; i < args.size(); ++i) {
    const auto &arg = args[i];

    if (!String::starts_with(arg, "--"))
      throw CLIError("Unexpected argument: " + arg);

    if (arg == "--help") {
      help();
    } else if (arg == "--fullscreen") {
      cli.fullscreen = true;
    } else if (arg == "--vsync") {
      cli.vsync = true;
    } else if (arg == "--width") {
      if (++i >= args.size())
        throw CLIError("--width requires a value");

      if (!String::is_number(args[i]))
        throw CLIError("--width expects an integer");

      cli.width = std::stoi(args[i]);
    } else if (arg == "--height") {
      if (++i >= args.size())
        throw CLIError("--height requires a value");

      if (!String::is_number(args[i]))
        throw CLIError("--height expects an integer");

      cli.height = std::stoi(args[i]);
    } else if (arg == "--scene") {
      if (++i >= args.size())
        throw CLIError("--scene requires a filename");

      cli.scene = args[i];
    } else {
      throw CLIError("Unknown argument: " + arg);
    }
  }

  return cli;
}
}; // namespace Cmd
