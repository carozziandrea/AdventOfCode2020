#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();

std::vector<std::string> split(std::string inputString, char delim);
void printVector(std::vector<std::string> v);
void printMap(std::map<std::string, std::string> m);

int occupiedAdjacent(std::vector<std::string> m, int i, int j) {
    int occupied = 0;
    /* Row up
    o X o
    o S o
    o o o
    */
    if (i - 1 >= 0 && (m[i - 1][j] == '#')) {
        occupied++;
    }

    /* Row down
    o o o
    o S o
    o X o
    */
    if ((i + 1 < m.size()) && (m[i + 1][j] == '#')) {
        occupied++;
    } 

    /* Column left
    o o o
    X S o
    o o o
    */
    if ((j-1 >= 0) && (m[i][j - 1] == '#')) {
        occupied++;
    }

    /* Column right
    o o o
    o S X
    o o o
    */
    if((j+1 < m[i].size()) && (m[i][j + 1] == '#')) {
        occupied++;
    }
    
    /* Top left
    X o o
    o S o
    o o o
    */
    if ((i - 1 >= 0) && (j - 1 >= 0) && (m[i - 1][j - 1] == '#')) {
        occupied++;
    }

    /* Top right
    o o X
    o S o
    o o o
    */
    if ((i - 1 >= 0) && (j + 1 < m[i].size()) && (m[i - 1][j + 1] == '#')) {
        occupied++;
    }

    /* Bottom left
    o o o
    o S o
    X o o
    */
    if ((i + 1 < m.size()) && (j - 1 >= 0) && (m[i + 1][j - 1] == '#')) {
        occupied++;
    }

    /* Bottom right
    o o o
    o S o
    o o X
    */
    if ((i + 1 < m.size()) && (j + 1 < m[i].size()) && (m[i + 1][j + 1] == '#')) {
        occupied++;
    }

    return occupied;
}

int countOccopied(std::vector<std::string> m) {
    int occupied = 0;
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++) {
            if (m[i][j] == '#') {
                occupied++;
            }
        }
    }
    return occupied;
}

int main()
{
    std::ifstream inputFile;

    //Open File
    inputFile.open("Day11input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;
    std::vector<std::string> matrix;
    std::vector<std::string> curMat;
    std::vector<std::string> prevMat;

    while (std::getline(inputFile, line)) {
        matrix.push_back(line);
    }

    //printVector(matrix);

    prevMat = {};
    curMat = matrix;
    while (curMat != prevMat) {
        prevMat = curMat;
        for (int i = 0; i < curMat.size(); i++) {
            for (int j = 0; j < curMat[i].size(); j++) {
                if (prevMat[i][j] == 'L') {
                    if (occupiedAdjacent(prevMat, i, j) == 0) {
                        curMat[i][j] = '#';
                    }
                }
                else if (prevMat[i][j] == '#') {
                    if (occupiedAdjacent(prevMat, i, j) >= 4) {
                        curMat[i][j] = 'L';
                    }
                }
            }
        }

        //std::cout << std::endl;
        //printVector(curMat);
    }

    //std::cout << std::endl;
    //printVector(curMat);
    std::cout << "Part1: " << countOccopied(curMat)  << std::endl;
    std::cout << "Part2: " << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::endl << duration.count() / 1000.0 << " s " << std::endl;
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

void printVector(std::vector<std::string> v) {
    for (std::string ele : v) {
        std::cout << ele << std::endl;
    }
}

void printMap(std::map<std::string, std::string> m) {
    for (const auto& ele : m) {
        std::cout << ele.first << ":" << ele.second << std::endl;
    }
}