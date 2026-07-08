#pragma once

#include "ConfigParser.h"
#include <string>

class GenericEntry;

using GenHashMap = std::unordered_map<std::string, GenericEntry *>;

namespace Engine::Config {

inline void clear_genhashmap(GenHashMap &map) {
  for (auto &[name, entry] : map)
    delete entry;

  map.clear();
}
bool LoadFile(const std::string &filename, GenHashMap &entries);

bool SaveFile(const std::string &filename, const GenHashMap &entries,
              const std::string &header = "");
} // namespace Engine::Config
