#ifndef TYPE_H_
#define TYPE_H_
#include "common.h"

enum class type_kind {

};

class base_type {
public:
    base_type() {}
    virtual ~base_type() {}

    type_kind kind() const { return _k; }

    bool operator==(const base_type& typ) const {
        return typ.kind() == _k;
    }

private:
    type_kind _k;
};

class boolean_type : public base_type {
};

class number_type : public base_type {
};

class integer_type : public number_type {
public:
    size_t size() const { return _size; }

private:
    size_t _size;
};

class float_type : public number_type {

};





#endif