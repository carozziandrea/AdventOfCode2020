#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <unordered_set>
#include <unordered_map>

auto start = std::chrono::high_resolution_clock::now();

std::unordered_set<std::string> valid;
std::unordered_map<std::string, bool> memo;
std::vector<std::string> split(std::string inputString, char delim);
bool checkColor(std::map<std::string, std::vector<std::pair<int, std::string>>> m, std::vector<std::pair<int, std::string>> v);

int main()
{
    std::ifstream inputFile;

    //Open File
    inputFile.open("Day07input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;

    int numCol = 0;
    std::map<std::string, std::vector<std::pair<int, std::string>>> colors;

    std::vector<std::string> rule;
    while (std::getline(inputFile, line)) {
        //Parsing Input
        rule = split(line, ' ');
        std::string colName = rule[0] + ' ' + rule[1];

        colors[colName] = {};

        std::vector<std::pair<int, std::string>> value = {};

        for (int i = 4; i < rule.size(); i+=4) {
            if (isdigit(rule[i][0])) {
                value.push_back({ (std::stoi(rule[i])), rule[i + 1] + ' ' + rule[i + 2]});
            }
            else {
                break;
            }
        }

        colors[colName] = std::move(value);
    }

    int counter = 0;;
    //Go through map
    for (auto c : colors) {
        counter += 1;
        std::cout << counter << std::endl;
        if (valid.find(c.first) != valid.end()) {
            numCol++;
        }else if (checkColor(colors, c.second)) {
            valid.insert(c.first);
            numCol++;
        }
    }

    //Part 2
    std::string curr = "shiny gold";


    std::cout << "Part1: " << numCol << std::endl;
    std::cout << "Part2: " << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::endl << duration.count() / 1000.0 << " s " << std::endl;

}

bool checkColor(std::map<std::string, std::vector<std::pair<int, std::string>>> m, std::vector<std::pair<int, std::string>> v){
    if (v.empty()) {
        return false;
    }
    for (auto color : v) {
        if (memo.find(color.second) != memo.end()) {
            return memo[color.second];
        }
        //std::cout << color.second << " --> ";
        if (valid.find(color.second) != valid.end()) {
            return true;
        }
        if (color.second == "shiny gold") {
            return true;
        }
        else {
            bool result = checkColor(m, m[color.second]);
            if (result) {
                return true;
            }
        }
    }
    return false;
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