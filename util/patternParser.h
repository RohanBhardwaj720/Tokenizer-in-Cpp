#ifndef PATTERNPARSER_H
#define PATTERNPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

std::vector<std::string> patternParser(const std::string& text) {
    std::vector<std::string> tokens;

    const char* const pattern = R"('(?i:[sdmt]|ll|ve|re)|[^\r\n\p{L}\p{N}]?+\p{L}+|\p{N}{1,3}| ?[^\s\p{L}\p{N}]++[\r\n]*|\s*[\r\n]|\s+(?!\S)|\s+)";

    pcre2_code* re;
    int errornumber;
    PCRE2_SIZE erroroffset;
    re = pcre2_compile(
        reinterpret_cast<PCRE2_SPTR>(pattern),
        PCRE2_ZERO_TERMINATED,
        PCRE2_UTF | PCRE2_UCP,
        &errornumber,
        &erroroffset,
        nullptr);

    if (re == nullptr) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
        throw std::runtime_error(std::string("PCRE2 compilation failed at offset ") + 
                                 std::to_string(erroroffset) + ": " + 
                                 reinterpret_cast<char*>(buffer));
    }

    pcre2_match_data* match_data = pcre2_match_data_create_from_pattern(re, nullptr);

    PCRE2_SIZE* ovector;
    PCRE2_SIZE start = 0;
    int rc;

    while (true) {
        rc = pcre2_match(
            re,
            reinterpret_cast<PCRE2_SPTR>(text.c_str()),
            text.length(),
            start,
            0,
            match_data,
            nullptr);

        if (rc < 0) {
            break;
        }

        ovector = pcre2_get_ovector_pointer(match_data);
        PCRE2_SIZE token_length = ovector[1] - ovector[0];
        std::string token = text.substr(ovector[0], token_length);
        if (!token.empty()) {
            tokens.push_back(token);
        }

        if (start == ovector[1]) break;  // Prevent infinite loop
        start = ovector[1];
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);

    return tokens;
}

#endif