#ifndef CONVERTBYTESTOSTRING_H
#define CONVERTBYTESTOSTRING_H

#include <iostream>
#include <vector>
#include <string>

std::string convertBytesToString(const std::vector<int>& utf8Bytes) {
    std::string utf8Str;
    
    for (int byte : utf8Bytes) {
        utf8Str += static_cast<char>(byte);
    }
    
    return utf8Str;
}

#endif 
