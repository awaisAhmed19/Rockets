#pragma once
#include <algorithm>
#include <cctype>
#include <string>
#include <unordered_set>
#include <vector>
namespace Engine {
namespace String {

inline std::string trim(const std::string &str,
                        const std::unordered_set<char> &chars = {' ', '\t',
                                                                 '\n', '\r'}) {
  size_t begin = 0;
  size_t end = str.size();

  while (begin < end && chars.count(str[begin]))
    ++begin;

  while (end > begin && chars.count(str[end - 1]))
    --end;

  return str.substr(begin, end - begin);
}

inline std::vector<std::string>
split_string_with_delimiter(const std::string &str,
                            const std::string &delimiter) {
  std::vector<std::string> result;

  size_t start = 0;
  size_t pos;

  while ((pos = str.find(delimiter, start)) != std::string::npos) {
    result.push_back(str.substr(start, pos - start));

    start = pos + delimiter.size();
  }

  result.push_back(str.substr(start));

  return result;
}

inline std::string extract_string_between_enclosure(const std::string &str,
                                                    const std::string &left,
                                                    const std::string &right) {
  size_t begin = str.find(left);

  if (begin == std::string::npos)
    return "";

  begin += left.size();

  size_t end = str.rfind(right);

  if (end == std::string::npos || end < begin)
    return "";

  return str.substr(begin, end - begin);
}

inline bool starts_with(const std::string &str, const std::string &prefix) {
  return str.compare(0, prefix.size(), prefix) == 0;
}

inline bool ends_with(const std::string &str, const std::string &suffix) {
  if (suffix.size() > str.size())
    return false;

  return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

inline bool contains(const std::string &str, const std::string &substr) {
  return str.find(substr) != std::string::npos;
}

inline std::string to_upper(std::string str) {
  for (char &c : str)
    c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  return str;
}
inline std::string to_lower(std::string str) {
  for (char &c : str) {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  }
  return str;
}
inline std::string ltrim(const std::string &str,
                         const std::unordered_set<char> &chars = {' ', '\t',
                                                                  '\n', '\r'}) {
  size_t begin = 0;

  while (begin < str.size() && chars.count(str[begin]))
    ++begin;

  return str.substr(begin);
}
inline std::string rtrim(const std::string &str,
                         const std::unordered_set<char> &chars = {' ', '\t',
                                                                  '\n', '\r'}) {
  if (str.empty())
    return str;

  size_t end = str.size();

  while (end > 0 && chars.count(str[end - 1]))
    --end;

  return str.substr(0, end);
}
inline std::string remove_chars(const std::string &str,
                                const std::unordered_set<char> &chars) {
  std::string result;
  result.reserve(str.size());

  for (char c : str) {
    if (!chars.count(c))
      result.push_back(c);
  }

  return result;
}
inline std::string remove_whitespace(const std::string &str) {
  return remove_chars(str, {' ', '\t', '\n', '\r'});
}
inline std::string extract_between(const std::string &str,
                                   const std::string &left,
                                   const std::string &right) {
  size_t leftPos = str.find(left);

  if (leftPos == std::string::npos)
    return "";

  leftPos += left.size();

  size_t rightPos = str.find(right, leftPos);

  if (rightPos == std::string::npos)
    return "";

  return str.substr(leftPos, rightPos - leftPos);
}

inline bool is_number(const std::string &str) {
  if (str.empty())
    return false;

  bool decimal = false;
  bool digit = false;

  size_t i = 0;

  if (str[0] == '+' || str[0] == '-')
    i = 1;

  for (; i < str.size(); ++i) {
    char c = str[i];

    if (std::isdigit(static_cast<unsigned char>(c))) {
      digit = true;
      continue;
    }

    if (c == '.') {
      if (decimal)
        return false;

      decimal = true;
      continue;
    }

    return false;
  }

  return digit;
}
} // namespace String
}; // namespace Engine
