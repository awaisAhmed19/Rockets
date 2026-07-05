#include "ConfigFile.h"
#include <fstream>
namespace Engine::Config {
bool LoadFile(const std::string &filename, GenHashMap &entries) {
  std::ifstream file(filename);

  if (!file)
    return false;

  std::string text(std::istreambuf_iterator<char>(file), {});

  return ParseText(text, entries);
}
bool SaveFile(const std::string &filename, const GenHashMap &entries,
              const std::string &header) {
  std::ofstream file(filename);

  if (!file)
    return false;

  if (!header.empty())
    file << "/*" << header << "*/\n";

  file << SerializeText(entries);

  return true;
}
}; // namespace Engine::Config
