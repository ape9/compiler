#include "symbol_table.h"


namespace utils {


void symbol_table::add_variable(const std::string& name, const std::string& value) {

}

void symbol_table::add_function(const std::string& name, const std::map<std::string, std::string>& args) {

}

void symbol_table::remove(const std::string& key) {
    _entries.erase(key);
}

table_entry symbol_table::get(const std::string& key) {
    auto entry = _entries.find(key);
}



}