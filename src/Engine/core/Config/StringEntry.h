#pragma once
#include "Engine/core/Utitlity/StringUtils.h"
#include "PrimitiveEntry.h"

using namespace Engine::String;
class StringEntry : public TypedEntry<std::string> {
protected:
  // NOTE: value string format: "value_string"
  std::string str_enclosure[2] = {"\"", "\""};

public:
  StringEntry(const std::string &val = "") {
    this->m_type_name = "string";
    this->data = val;
  }

  void write_val_string(std::string *dst_string) override {
    // Add " " to string
    *dst_string = str_enclosure[0] + std::string(this->data) + str_enclosure[1];
  }

  void read_val_string(const std::string &src_string) override {
    // Extract string between " "
    std::string tmp_str = Engine::String::extract_between(
        src_string, str_enclosure[0], str_enclosure[1]);
    this->data = std::string(tmp_str);
  }
};
