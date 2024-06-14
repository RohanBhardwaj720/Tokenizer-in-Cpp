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
    
    // input string
    std::getline(inputFile, input);
    
    // string is divided, so the unwanted merges will not take place
    std::vector<std::string> splitted_string = patternParser(input);

    // UTF-8 conversion
    std::vector<std:: vector<int> > utf8Bytes;
    std::vector<int> temp;

    for(int i=0; i< splitted_string.size();i++){
        temp = convertToUtf8Bytes(splitted_string[i]);
        utf8Bytes.push_back(temp);
    }

    outputFile << "UTF-8 Expression of Splitted String: " << std:: endl;
    for (int i = 0; i < utf8Bytes.size(); ++i) {

        outputFile << "'" << splitted_string[i] << "' : ";
        for(int j=0; j< utf8Bytes[i].size(); ++j){
            outputFile << utf8Bytes[i][j] <<" ";
        }
        outputFile << std:: endl;
    }

    int new_vocab_size;
    // input new vocab size >= 256
    inputFile >> new_vocab_size;
    int n_merges = new_vocab_size - 256;



    // To store the compressed form of expression after merges
    std::vector<std::string> compressed_splitted_string = splitted_string;

    std::map<int, std::pair<int, int>> new_vocab = encoder(compressed_splitted_string, n_merges);

    for (auto it = new_vocab.begin(); it != new_vocab.end(); ++it) {
        int a = it->first;
        std::pair<int, int> b = it->second;
        outputFile << a << ": " << b.first << " " << b.second << std::endl;
    }
    
    if (utf8Bytes == decoder(compressed_splitted_string, new_vocab)) {
        outputFile << "passed" << std::endl;
    }
    
    int final_len = 0;
    for(int i = 0; i < compressed_splitted_string.size(); i++){
        final_len += compressed_splitted_string[i].size();
    }

    int initial_len;
    for(int i = 0; i < utf8Bytes.size(); i++){
        initial_len += utf8Bytes[i].size();
    }    

    float compression_ratio = initial_len/(float)final_len;
    outputFile << "Compression Ratio: " << compression_ratio << std::endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
