#ifndef ENCODER_H
#define ENCODER_H

#include <iostream>
#include <vector>
#include <map>

std::map<int, std::pair<int, int>> encoder(std::vector< std:: vector<int> > &compressed, int n_merges) {
    std::map<int, std::pair<int, int>> merges;
    int val = 256;

    while (n_merges--) {
        std::map<int, std::map<int, int>> count_pairs;

        int max_count = 0;
        std::pair<int, int> max_pair;

        // Count pairs and find the most frequent pair
        for(int j = 0; j<compressed.size(); j++){
            for (int i = 0; i + 1 < compressed[j].size(); i++) {
                count_pairs[compressed[j][i]][compressed[j][i + 1]]++;

                if (max_count < count_pairs[compressed[j][i]][compressed[j][i + 1]]) {
                    max_pair = std::make_pair(compressed[j][i], compressed[j][i + 1]);
                    max_count = count_pairs[compressed[j][i]][compressed[j][i + 1]];
                }
            }
        }

        // Add the merged pair to the vocabulary
        merges[val] = std::make_pair(max_pair.first, max_pair.second);

        // Update the compressed vector with merged pairs
        std::vector< std:: vector<int> > temp( compressed.size() );

        for(int j = 0; j<compressed.size(); j++){
            for (int i = 0; i < compressed[j].size();) {
                if (compressed[j][i] == max_pair.first && compressed[j][i + 1] == max_pair.second) {
                    temp[j].push_back(val);
                    i += 2;
                } else {
                    temp[j].push_back(compressed[j][i]);
                    i++;
                }
            }
        }

        val++;
        compressed = temp;
    }

    return merges;
}

#endif