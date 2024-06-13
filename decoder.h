#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include <vector>
#include <map>

std::vector<int> decoder(const std::vector<int>& encoded, const std::map<int, std::pair<int, int>>& new_vocab) {

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

#endif 
