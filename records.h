#pragma once

#include <vector>

class Records {
public:
    Records(const char* filePath = "scores.dat");

    void Save(int score);
    std::vector<int> LoadTop(int count = 10) const;

private:
    const char* filePath;
};