#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include "common.h"
#include "ast.h"

namespace utils {

enum class symbol_type {
    FUNCTION, VARIABLE, CLASS
};

class table_entry {
public:
    table_entry() {}
    table_entry(symbol_type typ) 
        : _type(typ), _module("") {}

    virtual ~table_entry() {}

    inline symbol_type get_type() const { 
        return _type; 
    }

    inline std::string get_module() const { 
        return _module; 
    }

    inline std::string get_parent() const { 
        return _parent; 
    }

private:
    symbol_type _type;
    std::string _module;
    std::string _parent;
};

class var_entry final : public table_entry {
public:
    var_entry() : table_entry(symbol_type::VARIABLE) {}

    inline std::string get_value() const {
        return _value;
    }

private:
    std::string _value;
};

class fn_entry final : public table_entry {
public:
    fn_entry() : table_entry(symbol_type::FUNCTION) {}
    fn_entry(const std::map<std::string, std::string>& args)
        : _args(args) {}
    
    inline size_t argc() const { 
        return _args.size(); 
    }

    std::string get_argument_type(const std::string& arg) {
        return _args[arg];
    }

private:
    // arguments
    std::map<std::string, std::string> _args;
};

class class_entry final : public table_entry {
    // todo???
};

class symbol_table final {
public:

    void add_variable();
    void add_function();
    void remove(const std::string& key);

    table_entry get(const std::string& key);
    table_entry operator[](const std::string& key);

private:
    std::map<std::string, table_entry> _entries;
};


}

#endif