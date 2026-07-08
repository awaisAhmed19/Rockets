#include "ConfigParser.h"

#include "Engine/Core/Utitlity/StringUtils.h"

#include <iostream>
#include <sstream>

namespace Engine::Config {
struct ParserSettings {
  std::string TypeDelimiter = " ";
  std::string ValueDelimiter = "=";
  std::string EntryDelimiter = ";";

  std::unordered_map<std::string, std::string> IgnorePairs = {{"//", "\n"},
                                                              {"/*", "*/"}};
  std::unordered_map<std::string, std::string> IncludePairs = {{"\"", "\""}};
  std::unordered_set<char> TrimCharacters = {' ', '\t', '\n', '\r'};
};
std::string PackEntry(const std::string &type, const std::string &name,
                      const std::string &value,
                      const std::string &typeDelimiter,
                      const std::string &valueDelimiter) {
  return type + typeDelimiter + name + valueDelimiter + value;
}

std::vector<std::string> ExtractEntries(
    const std::string &src_string, const std::string &entry_stop_str,
    std::unordered_map<std::string, std::string> ignore_left_to_right_map,
    std::unordered_map<std::string, std::string> include_left_to_right_map) {
  std::size_t slow_idx = 0;
  std::size_t fast_idx = 0;
  std::size_t srcstr_len = src_string.size();
  std::size_t entry_stop_str_len = entry_stop_str.size();

  // count string lengths in the left_to_right map keys
  std::unordered_set<std::size_t> ignore_left_lens;
  for (const auto &itr : ignore_left_to_right_map) {
    ignore_left_lens.insert(itr.first.size());
  }

  // count string lengths in the left_to_right map keys
  std::unordered_set<std::size_t> include_left_lens;
  for (const auto &itr : include_left_to_right_map) {
    include_left_lens.insert(itr.first.size());
  }

  // itrate through src_string to find all entry strings
  std::vector<std::string> entry_strs;
  while (fast_idx < srcstr_len) {
    // check string between "left" and "right" to include
    for (auto cur_left_len : include_left_lens) {
      if (fast_idx + cur_left_len > srcstr_len)
        continue;
      std::string cur_left_str = src_string.substr(fast_idx, cur_left_len);
      if (include_left_to_right_map.find(cur_left_str) !=
          include_left_to_right_map.end()) {
        std::string cur_right_str = include_left_to_right_map[cur_left_str];
        std::size_t cur_right_len = cur_right_str.size();
        for (fast_idx += cur_left_len; fast_idx + cur_right_len < srcstr_len;
             ++fast_idx) {
          if (src_string.substr(fast_idx, cur_right_len) == cur_right_str)
            break;
        }
        fast_idx += cur_right_len;
      }
    }
    // check string between "left" and "right" to exclude
    for (auto cur_left_len : ignore_left_lens) {
      if (fast_idx + cur_left_len > srcstr_len)
        continue;
      std::string cur_left_str = src_string.substr(fast_idx, cur_left_len);
      if (ignore_left_to_right_map.find(cur_left_str) !=
          ignore_left_to_right_map.end()) {
        std::string cur_right_str = ignore_left_to_right_map[cur_left_str];
        std::size_t cur_right_len = cur_right_str.size();
        for (fast_idx += cur_left_len; fast_idx + cur_right_len < srcstr_len;
             ++fast_idx) {
          if (src_string.substr(fast_idx, cur_right_len) == cur_right_str)
            break;
        }
        fast_idx += cur_right_len;
        slow_idx = fast_idx;
      }
    }
    if (fast_idx + entry_stop_str_len > srcstr_len)
      break; // reach the end of src_string
    // found complete entry string
    if (src_string.substr(fast_idx, entry_stop_str_len) == entry_stop_str) {
      entry_strs.push_back(src_string.substr(slow_idx, fast_idx - slow_idx));
      slow_idx = fast_idx + 1;
    }
    ++fast_idx;
  }

  return entry_strs;
}

EntryToken SplitEntry(const std::string &entry,
                      const std::string &typeDelimiter,
                      const std::string &valueDelimiter) {
  EntryToken token;
  auto typeEnd = entry.find(typeDelimiter);
  if (typeEnd == std::string::npos)
    return token;

  token.type = entry.substr(0, typeEnd);

  auto nameBegin = typeEnd + typeDelimiter.size();
  auto valuePos = entry.find(valueDelimiter, nameBegin);
  if (valuePos == std::string::npos)
    return token;

  token.name = entry.substr(nameBegin, valuePos - nameBegin);
  token.value = entry.substr(valuePos + valueDelimiter.size());
  return token;
}

bool ParseText(const std::string &text, GenHashMap &map) {
  const ParserSettings settings;
  auto entries = ExtractEntries(text, settings.EntryDelimiter,
                                settings.IgnorePairs, settings.IncludePairs);

  for (auto &entry : entries) {
    entry = Engine::String::trim(entry, settings.TrimCharacters);

    auto token =
        SplitEntry(entry, settings.TypeDelimiter, settings.ValueDelimiter);
    token.type = Engine::String::trim(token.type, settings.TrimCharacters);
    token.name = Engine::String::trim(token.name, settings.TrimCharacters);
    token.value = Engine::String::trim(token.value, settings.TrimCharacters);

    auto itr = map.find(token.name);

    if (itr == map.end()) {
      std::cout << "Unknown config entry: " << token.name << '\n';

      continue;
    }

    std::string type;
    type = itr->second->type_name();

    if (type != token.type) {
      std::cout << "Type mismatch: " << token.name << '\n';
      continue;
    }

    itr->second->read_val_string(token.value);
  }
  return true;
}
std::string SerializeText(const GenHashMap &map) {
  std::stringstream out;
  const ParserSettings settings;
  for (const auto &pair : map) {
    std::string type;
    std::string value;

    type = pair.second->type_name();
    pair.second->write_val_string(&value);

    out << PackEntry(type, pair.first, value, settings.TypeDelimiter,
                     settings.ValueDelimiter)
        << settings.EntryDelimiter << '\n';
  }

  return out.str();
}

} // namespace Engine::Config
