#ifndef VALUE_H_
#define VALUE_H_

#include "type.h"


enum class value_kind {
    INTEGER, STRING
};

class value {
public:

};

class integer_value : public value {
public:
    integer_value(std::string& strval);

    bool is_unsigned() const { return _unsigned; }
    size_t size() const { return _size; }

private:
    bool _unsigned;
    size_t _size;
};

class string_value final : public value {
public:
    string_value(const std::string& val) : _value(val) {}

    size_t length() const { return _value.length(); }

private:
    std::string _value;
};



#endif