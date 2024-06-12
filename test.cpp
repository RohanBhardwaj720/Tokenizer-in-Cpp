#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

std::vector<int> convertToUtf8Bytes(const std::string& input) {
    std::vector<int> utf8Bytes;

    for (unsigned char ch : input) {
        utf8Bytes.push_back(static_cast<int>(ch));
    }

    return utf8Bytes;
}

std::string convertBytesToString(const std::vector<int>& utf8Bytes) {
    std::string utf8Str;
    for (int byte : utf8Bytes) {
        utf8Str += static_cast<char>(byte);
    }
    
    return utf8Str;
}

std:: map<int,std:: pair<int,int> > BPE(std:: vector<int> &compressed,int n_merges){
    std:: map<int,std:: pair<int,int> > merges;
    int val = 256;

    while(n_merges--){
        std:: map<int,std:: map<int,int> > count_pairs;
        int max_count = 0;
        std:: pair<int,int> max_pair;
        for(int i=0;i+1<compressed.size();i++){
            // This is how we count number of times that pair occured in the expression
            count_pairs[compressed[i]][compressed[i+1]]++;
            if(max_count<count_pairs[compressed[i]][compressed[i+1]]){
                max_pair = std:: make_pair(compressed[i],compressed[i+1]);
                max_count = count_pairs[compressed[i]][compressed[i+1]];
            }
        }
        // now max_pair is merged and added into vocabulary 
        merges[val]= std:: make_pair(max_pair.first,max_pair.second);

        std:: vector<int> temp;
        for(int i=0;i<compressed.size();){
            if(compressed[i] == max_pair.first && compressed[i+1] == max_pair.second){
                temp.push_back(val);
                i+=2;
            }else{
                temp.push_back(compressed[i]);
                i++;
            }
        }
        val++;
        compressed = temp;
    }
    return merges;
}

std::vector<int> decode(const std::vector<int>& encoded, const std::map<int, std::pair<int, int>>& new_vocab) {
    std::vector<int> decoded = encoded; // Start with the encoded data

    bool flag = true;
    while (flag) {
        flag = false; // Reset the flag
        std::vector<int> temp; // Temporary vector to store decoded bytes

        for (int byte : decoded) {
            if (byte > 255) {
                flag = true; // Set the flag if any byte needs decoding
                temp.push_back(new_vocab.at(byte).first);
                temp.push_back(new_vocab.at(byte).second);
            } else {
                temp.push_back(byte); // Keep bytes < 256 unchanged
            }
        }

        decoded = temp; // Update the decoded data for the next iteration
    }

    return decoded;
}


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
    std:: map<int,std:: pair<int,int> > new_vocab = BPE(compressed,n_merges);

    // for(int byte : compressed){
    //     std:: cout << byte << " ";
    // }
    // std:: cout<< std::endl;
    for (auto it = new_vocab.begin(); it != new_vocab.end(); ++it) {
    int a = it->first;
    std::pair<int, int> b = it->second;
    std::cout << a << ": " << b.first << " " << b.second << std::endl;
    }
    
    if(utf8Bytes == decode(compressed,new_vocab)){
        std:: cout<<"oh yesss";
    }
    return 0;
}
