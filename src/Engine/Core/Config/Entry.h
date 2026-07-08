#pragma once
#pragma once
#include <string>
class GenericEntry {
protected:
  std::string m_type_name;

public:
  GenericEntry() { this->m_type_name = "generic_entry"; }
  virtual ~GenericEntry() = default;

  const std::string &type_name() { return this->m_type_name; }
  virtual void write_val_string(std::string *dst_string) = 0;
  virtual void read_val_string(const std::string &src_string) = 0;
};

// Entry of generic type definition
template <typename T> class TypedEntry : public GenericEntry {
protected:
  T data;

public:
  TypedEntry() { this->m_type_name = "typed_entry"; }
  TypedEntry(T value) : TypedEntry() { this->data = value; }

  void set(const T &_data) { this->data = T(_data); }

  const T &get() { return this->data; }
};
