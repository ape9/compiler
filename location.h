#ifndef LOCATION_H_
#define LOCATION_H_

#include <string>

namespace utils {

struct Location {

    Location() = default;

    explicit Location(const std::string& filename) 
        : _fileName(filename), _function(""), _row(0), _col(0)  {}

    Location(const std::string& filename, uint32_t row, uint32_t col)
        : _fileName(filename), _function(""), _row(row), _col(col) {}

    void setRow(int row) {
        _row = row;
    }

    void setCol(int col) {
        _col = col;
    }
    
    // name of the source file
    std::string _fileName;

    // If the location is inside of a function
    std::string _function;

    // Row in source file
    uint32_t _row;

    // Column in source file
    uint32_t _col;


};


}



#endif