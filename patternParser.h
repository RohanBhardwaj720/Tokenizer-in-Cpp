#ifndef PATTERNPARSER_H
#define PATTERNPARSER_H

#include <regex>
#include <string>
#include <vector>
#include <regex>

std::vector<std::string> patternParser(const std::string& input) {
    //regex pattern
    std::regex pattern(R"('(?i:[sdmt]|ll|ve|re)|[^\r\n\p{L}\p{N}]?+\p{L}+|\p{N}{1,3}| ?[^\s\p{L}\p{N}]++[\r\n]*|\s*[\r\n]|\s+(?!\S)|\s+)");
    std::vector<std::string> tokens;

    // Tokenize using regex_iterator
    std::sregex_iterator next(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    while (next != end) {
        std::smatch match = *next;
        tokens.push_back(match.str());
        next++;
    }

    return tokens;
}

#endif