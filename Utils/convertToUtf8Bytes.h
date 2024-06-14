#ifndef CONVERTTOUTF8BYTES_H
#define CONVERTTOUTF8BYTES_H

#include <iostream>
#include <vector>
#include <string>

std::vector<int> convertToUtf8Bytes(const std::string& input) {
    std::vector<int> utf8Bytes;

    for (unsigned char ch : input) {
        utf8Bytes.push_back(static_cast<int>(ch));
    }

    return utf8Bytes;
}

#endif 
