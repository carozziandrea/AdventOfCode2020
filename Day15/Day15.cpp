#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();

std::vector<int> split(std::string inputString, char delim);

struct Turns {
    int prevTurn = 0;
    int prev2Turns = 0;

    void update(int n) {
        prev2Turns = prevTurn;
        prevTurn = n;
    }
};

int main()
{
    std::ifstream inputFile;

    //Open File
    inputFile.open("Day15input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;
    std::unordered_map<int, Turns> nums;
    std::vector<int> temp;
    int prevTurn;
    int prev2Turns;
    int turn = 1;
    bool first = true;
    int curNum;
    int part1 = 0;

    while (std::getline(inputFile, line)) {
        temp = split(line, ',');
        for (int n : temp) {
            curNum = n;
            //std::cout << "Turn " << turn << " - Number spoken: " << curNum << std::endl;
            if (nums.find(n) != nums.end()) {
                first = false;
            }
            else {
                Turns t;
                t.update(turn);
                nums.insert({ n, t });
                first = true;
            }
            turn++;
        }
    }

    while (turn <= 30000000) {
        if (first) {
            curNum = 0;
        }
        else {
            prevTurn = nums[curNum].prevTurn;
            prev2Turns = nums[curNum].prev2Turns;
            curNum = prevTurn - prev2Turns;
        }
        if (turn == 2020) {
            part1 = curNum;
            //std::cout << "Turn " << turn << " - Number spoken: " << curNum << std::endl;
        }
        if (nums.find(curNum) != nums.end()) {
            first = false;
            nums[curNum].update(turn);
        }
        else {
            Turns t;
            t.update(turn);
            nums.insert({ curNum, t });
            first = true;
        }
        turn++;
    }

    std::cout << "Part1: " << part1 << std::endl;
    std::cout << "Part2: " << curNum << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::endl << duration.count() / 1000.0 << " s " << std::endl;
}

std::vector<int> split(std::string inputString, char delim) {
    std::stringstream ss(inputString);
    std::vector<int> tokens;
    std::string token;
    while (std::getline(ss, token, delim)) {
        if (!token.empty())
            tokens.push_back(stoi(token));
    }
    return tokens;
}