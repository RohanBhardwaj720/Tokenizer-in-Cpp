#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include <vector>
#include <map>

std::vector< std:: vector<int> > decoder(const std::vector< std:: vector<int> >& encoded, const std::map<int, std::pair<int, int>>& new_vocab) {

    std::vector< std:: vector<int> > decoded = encoded; // Start with the encoded data
    bool flag = true;

    while (flag) {

        flag = false; // Reset the flag
        std::vector< std:: vector<int> > temp( decoded.size() ); // Temporary vector to store decoded bytes

        for(int i = 0; i < decoded.size() ; i++){
            for (int byte : decoded[i]) {
                if (byte > 255) {
                    flag = true; // Set the flag if any byte needs decoding

                    temp[i].push_back(new_vocab.at(byte).first);
                    temp[i].push_back(new_vocab.at(byte).second);
                } else {
                    temp[i].push_back(byte); // Keep bytes < 256 unchanged
                }
            }
        }

        decoded = temp; // Update the decoded data for the next iteration
    }

    return decoded;
}

#endif 
