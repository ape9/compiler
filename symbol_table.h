#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include "common.h"
#include "ast.h"

namespace utils {

enum class symbol_kind {
    FUNCTION, VARIABLE, CLASS
};

class table_entry {
public:
    table_entry() {}
    table_entry(symbol_kind typ) 
        : _type(typ), _module("") {}

    virtual ~table_entry() {}

    inline symbol_kind get_type() const { 
        return _type; 
    }

    inline std::string get_module() const { 
        return _module; 
    }

    inline std::string get_parent() const { 
        return _parent; 
    }

    bool operator==(const table_entry& other) {
        return other.get_type() == _type;
    }

private:
    std::string _name;
    std::string _mangled_name;
    symbol_kind _type;
    std::string _module;
    std::string _parent;
};

class var_entry final : public table_entry {
public:
    var_entry() : table_entry(symbol_kind::VARIABLE) {}

    inline std::string get_value() const {
        return _value;
    }

private:
    std::string _value;
};

class fn_entry final : public table_entry {
public:
    fn_entry() : table_entry(symbol_kind::FUNCTION) {}
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
    static void add_variable(const std::string& name, const std::string& value);
    static void add_function(const std::string& name, const std::map<std::string, std::string>& args);
    static void remove(const std::string& key);

    static table_entry get(const std::string& key);

private:
    static inline std::map<std::string, table_entry> _entries{};
};


}

#endif