#pragma once
#include "Entry.h"
#include <sstream>
template <typename T> class PrimitiveTypeEntry : public TypedEntry<T> {
  // NOTE: Only need to define contructor giving type_name in the subclasses
public:
  PrimitiveTypeEntry() { this->m_type_name = "primitivetype_entry"; }
  PrimitiveTypeEntry(const T &data) : PrimitiveTypeEntry() {
    this->data = T(data);
  }
  virtual void write_val_string(std::string *dst_string) override {
    *dst_string = std::to_string(this->data);
  }
  virtual void read_val_string(const std::string &src_string) override {
    if (std::is_fundamental<T>::value) { // validate the data type is
                                         // primitive data type
      std::stringstream(src_string) >>
          this->data; // use stringstream to convert value string to value
    }
  }
};
class IntEntry : public PrimitiveTypeEntry<int> {
public:
  IntEntry(int val = 0) {
    this->m_type_name = "int";
    this->data = val;
  }
};
