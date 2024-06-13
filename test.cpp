#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "convertToUtf8Bytes.h"
#include "convertBytesToString.h"
#include "patternParser.h"
#include "encoder.h"
#include "decoder.h"

int main() {
    std:: string input;
    
    std:: cout << "Enter a string: ";
    std:: getline(std::cin, input);
    
    std:: vector<int> utf8Bytes = convertToUtf8Bytes(input);

    std:: cout << "UTF-8 Encoded Bytes: ";
    for (size_t i = 0; i < utf8Bytes.size(); ++i) {
        std::cout << utf8Bytes[i]<<" ";
    }
    std:: cout<< std::endl;
    std:: cout<<convertBytesToString(utf8Bytes);
    std:: cout<< std::endl;

    // To store the compressed form of expression after merges
    std:: vector<int> compressed = utf8Bytes;
    
    int new_vocab_size;
    std:: cout << "Enter new vocab size: ";
    std:: cin >> new_vocab_size;

    int n_merges = new_vocab_size - 256;
    std:: map<int,std:: pair<int,int> > new_vocab = encoder(compressed,n_merges);

    // for(int byte : compressed){
    //     std:: cout << byte << " ";
    // }
    // std:: cout<< std::endl;
    for (auto it = new_vocab.begin(); it != new_vocab.end(); ++it) {
    int a = it->first;
    std::pair<int, int> b = it->second;
    std::cout << a << ": " << b.first << " " << b.second << std::endl;
    }
    
    if(utf8Bytes == decoder(compressed,new_vocab)){
        std:: cout<<"oh yesss";
    }
    return 0;
}
