#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "convertToUtf8Bytes.h"
#include "convertBytesToString.h"
#include "patternParser.h"
#include "encoder.h"
#include "decoder.h"

int main() {
    std::ifstream inputFile("in.txt");
    std::ofstream outputFile("out.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string input;
    
    outputFile << "Enter a string: ";
    std::getline(inputFile, input);
    
    std::vector<int> utf8Bytes = convertToUtf8Bytes(input);

    outputFile << "UTF-8 Encoded Bytes: ";
    for (size_t i = 0; i < utf8Bytes.size(); ++i) {
        outputFile << utf8Bytes[i] << " ";
    }
    outputFile << std::endl;
    outputFile << convertBytesToString(utf8Bytes);
    outputFile << std::endl;

    // To store the compressed form of expression after merges
    std::vector<int> compressed = utf8Bytes;
    
    int new_vocab_size;
    outputFile << "Enter new vocab size: ";
    inputFile >> new_vocab_size;

    int n_merges = new_vocab_size - 256;
    std::map<int, std::pair<int, int>> new_vocab = encoder(compressed, n_merges);

    // for (int byte : compressed) {
    //     outputFile << byte << " ";
    // }
    // outputFile << std::endl;
    for (auto it = new_vocab.begin(); it != new_vocab.end(); ++it) {
        int a = it->first;
        std::pair<int, int> b = it->second;
        outputFile << a << ": " << b.first << " " << b.second << std::endl;
    }
    
    if (utf8Bytes == decoder(compressed, new_vocab)) {
        outputFile << "passed";
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
