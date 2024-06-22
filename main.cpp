#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "./utils/convertToUtf8Bytes.h"
#include "./utils/convertBytesToString.h"
#include "./utils/patternParser.h"
#include "./utils/encoder.h"
#include "./utils/decoder.h"
//
int main() {
    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile("./io_streams/in.txt");
    std::ofstream outputFile("./io_streams/out.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string input;
    
    // input string
    std::getline(inputFile, input);
    
    // string is divided, so the unwanted merges will not take place
    std::vector<std::string> splitted_string = patternParser(input);

    // UTF-8 conversion
    std::vector<std::vector<int>> utf8Bytes;
    std::vector<int> temp;

    for (int i = 0; i < splitted_string.size(); ++i) {
        temp = convertToUtf8Bytes(splitted_string[i]);
        utf8Bytes.push_back(temp);
    }

    outputFile << "UTF-8 Expression of Splitted String: " << std::endl;
    for (int i = 0; i < utf8Bytes.size(); ++i) {
        outputFile << "'" << splitted_string[i] << "' : ";
        for (int j = 0; j < utf8Bytes[i].size(); ++j) {
            outputFile << utf8Bytes[i][j] << " ";
        }
        outputFile << std::endl;
    }
    outputFile << std::endl;

    int new_vocab_size;
    // input new vocab size >= 256
    inputFile >> new_vocab_size;
    int n_merges = new_vocab_size - 256;

    // To store the compressed form of expression after merges
    std::vector<std::vector<int>> compressed = utf8Bytes;

    std::map<int, std::pair<int, int>> new_vocab = encoder(compressed, n_merges);

    outputFile << "Merges:" << std::endl;
    for (auto it = new_vocab.begin(); it != new_vocab.end(); ++it) {
        int a = it->first;
        std::pair<int, int> b = it->second;
        outputFile << a << ": " << b.first << " " << b.second << std::endl;
    }
    outputFile << std::endl;

    if (utf8Bytes == decoder(compressed, new_vocab)) {
        outputFile << "passed" << std::endl;
    }
    outputFile << std::endl;

    // Calculate final length
    int final_len = 0;
    for (int i = 0; i < compressed.size(); ++i) {
        final_len += compressed[i].size();
    }

    // Calculate initial length
    int initial_len = 0;
    for (int i = 0; i < utf8Bytes.size(); ++i) {
        initial_len += utf8Bytes[i].size();
    }

    outputFile << "Initial Length: " << initial_len << std::endl;
    outputFile << "Final Length: " << final_len << std::endl;

    // Calculate and print compression ratio
    float compression_ratio = static_cast<float>(initial_len) / final_len;
    outputFile << "Compression Ratio: " << compression_ratio << std::endl;

    inputFile.close();
    outputFile.close();

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Print the duration
    std:: cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
