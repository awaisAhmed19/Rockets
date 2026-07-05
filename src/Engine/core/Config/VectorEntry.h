#include "Engine/core/Utitlity/StringUtils.h"
#include "PrimitiveEntry.h"
using namespace Engine::String;

template <typename T>
class VectorPrimitiveTypeEntry : public TypedEntry<std::vector<T>> {
protected:
  std::string str_dl = ",";
  std::string str_enclosure[2] = {"{", "}"};

public:
  VectorPrimitiveTypeEntry() { this->m_type_name = "vector_primitivetype"; }

  VectorPrimitiveTypeEntry(const std::vector<T> &val)
      : VectorPrimitiveTypeEntry() {
    this->data = std::vector<T>(val);
  }

  void write_val_string(std::string *dst_string) override {
    std::stringstream result_strstream;
    unsigned data_len = this->data.size();
    unsigned count = 0;

    // iterate through data vector
    result_strstream << this->str_enclosure[0];
    for (auto itr = this->data.begin(); itr != this->data.end(); ++itr) {
      result_strstream << std::to_string(*itr);
      count++;
      if (count < data_len)
        result_strstream << this->str_dl;
    }
    result_strstream << this->str_enclosure[1];

    *dst_string = result_strstream.str();
  }

  void read_val_string(const std::string &src_string) override {
    // remove '{', '}', and '_'
    std::string tmp_str =
        extract_between(src_string, str_enclosure[0], str_enclosure[1]);
    tmp_str = trim(tmp_str, std::unordered_set<char>{' '});
    // extract value string for each element
    std::vector<std::string> val_strs =
        split_string_with_delimiter(tmp_str, this->str_dl);

    if (std::is_fundamental<T>::value) { // validate data type
      // iterate through value strings for each element
      this->data.clear();
      for (auto itr = val_strs.begin(); itr != val_strs.end(); ++itr) {
        T tmp_val;
        std::stringstream(*itr) >> tmp_val;
        this->data.push_back(tmp_val);
      }
    }
  }
};
class VectorFloatEntry : public VectorPrimitiveTypeEntry<float> {
public:
  VectorFloatEntry(const std::vector<float> &val = {0.0}) {
    this->m_type_name = "vector_float";
    this->data = std::vector<float>(val);
  }
};
