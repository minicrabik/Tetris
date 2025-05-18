#include "records.h"
#include <fstream>
#include <algorithm>

Records::Records(const char* filePath) {
    this->filePath = filePath;
}

void Records::Save(int score) {
    std::ofstream file(filePath, std::ios::binary | std::ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<char*>(&score), sizeof(score));
        file.close();
    }
}

std::vector<int> Records::LoadTop(int count) const {
    std::vector<int> scores;
    std::ifstream file(filePath, std::ios::binary);
    int score;

    while (file.read(reinterpret_cast<char*>(&score), sizeof(score))) {
        scores.push_back(score);
    }

    std::sort(scores.rbegin(), scores.rend());  

    if ((int)scores.size() > count) {
        scores.resize(count);
    }

    return scores;
}