#pragma once

#include "PrimitiveEntry.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
class GenericEntry;

using GenHashMap = std::unordered_map<std::string, GenericEntry *>;

namespace Engine::Config {

struct EntryToken {
  std::string type;
  std::string name;
  std::string value;
};

std::string PackEntry(const std::string &type, const std::string &name,
                      const std::string &value,
                      const std::string &typeDelimiter = " ",
                      const std::string &valueDelimiter = "=");

std::vector<std::string> ExtractEntries(
    const std::string &src_string, const std::string &entry_stop_str = ";",
    std::unordered_map<std::string, std::string> ignore_left_to_right_map =
        {{"//", "\n"}, {"/*", "*/"}},
    std::unordered_map<std::string, std::string> include_left_to_right_map = {
        {"\"", "\""}});

EntryToken SplitEntry(const std::string &entry,
                      const std::string &typeDelimiter = " ",
                      const std::string &valueDelimiter = "=");

bool ParseText(const std::string &text, GenHashMap &entries);

std::string SerializeText(const GenHashMap &entries);
}; // namespace Engine::Config

// pack type name value string into one string
