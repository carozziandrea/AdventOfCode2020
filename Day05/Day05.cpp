#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include<algorithm>

std::vector<std::string> split(std::string inputString, char delim);
void printVector(std::vector<int> v);
void printMap(std::map<std::string, std::string> m);

int main()
{
    std::ifstream inputFile;

    //Open File
    inputFile.open("Day05input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;
    int row = 0;
    int rlow = 0;
    int rhigh = 127;

    int col = 0;
    int clow = 0;
    int chigh = 7;

    int seatID = 0;

    std::vector<int> ids;

    while (std::getline(inputFile, line)) {
        for (int i = 0; i < 7; i++) {
            if (line[i] == 'F') {
                rhigh = (rhigh + rlow) / 2;
            }else if (line[i] == 'B') {
                rlow = (rhigh + rlow + 1) / 2;
            }else {
                std::cout << "Errore";
            }
        }

        row = rlow;

        for (int i = 7; i < 10; i++) {
            if (line[i] == 'L') {
                chigh = (chigh + clow) / 2;
            }
            else if (line[i] == 'R') {
                clow = (chigh + clow + 1) / 2;
            }
            else {
                std::cout << "Errore";
            }
        }

        col = chigh;

        seatID = (row * 8) + col;
        ids.push_back(seatID);

        row = 0;
        rlow = 0;
        rhigh = 127;
        col = 0;
        clow = 0;
        chigh = 7;
        seatID = 0;
    }

    auto max = std::max_element(ids.begin(), ids.end());
    std::sort(ids.begin(), ids.end());

    int num = ids[0];
    for (int id : ids) {
        if (id != num) {
            break;
        }
        num++;
    }

    std::cout << "Part1: " << *max << std::endl;
    std::cout << "Part2: " << num-- << std::endl;

}

std::vector<std::string> split(std::string inputString, char delim) {
    std::stringstream ss(inputString);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(ss, token, delim)) {
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

void printVector(std::vector<int> v) {
    for (int ele : v) {
        std::cout << ele << std::endl;
    }
}

void printMap(std::map<std::string, std::string> m) {
    for (const auto& ele : m) {
        std::cout << ele.first << ":" << ele.second << std::endl;
    }
}