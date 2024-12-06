#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <chrono>
#include <regex>

auto start = std::chrono::high_resolution_clock::now();

std::vector<std::string> split(std::string inputString, char delim);
void printVector(std::vector<int> v);
void printMap(std::map<long long, long long> m);

std::string toBinary(long long n, int l) {
    std::string result = "";
    std::stringstream ss;
    while (n != 0) {
        result.append(std::to_string(n % 2));
        n = n / 2;
    }
    int size = result.size();
    for (int i = 0; i < (l - size); i++){
        result.append("0");
    }
    std::reverse(result.begin(), result.end());
    return result;
}

long long fromBinary(std::string b) {
    return std::stoll(b, nullptr, 2);
}

int main()
{
    std::ifstream inputFile;

    //Open File
    inputFile.open("Day14input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;
    std::map<long long, long long> memory;
    std::vector<std::string> instr;
    std::string mask;
    std::string binary;
    std::regex pattern(R"(\[(\d+)\])");
    std::smatch match;
    int index = 0;

    while (std::getline(inputFile, line)) {
        //std::cout << line << std::endl;
        instr = split(line, ' ');
        if (line[1] == 'a') {
            mask = instr[2];
        }
        else {
            //Get index
            if (std::regex_search(line, match, pattern)) {
                index = stoi(match[1].str());
            }
            else {
                std::cout << "Nessun numero trovato tra parentesi quadre." << std::endl;
            }
            binary = toBinary(stoi(instr[2]), mask.size());
            for (int i = 0; i < mask.size(); i++) {
                if (mask[i] != 'X') {
                    binary[i] = mask[i];
                }
            }
            memory[index] = fromBinary(binary);
        }
    }

    printMap(memory);

    long long sum = 0;
    for (std::pair<long long, long long> k : memory) {
        sum += k.second;
    }
    

    std::cout << "Part1: " << sum << std::endl;
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

void printVector(std::vector<int> v) {
    for (int ele : v) {
        std::cout << ele << std::endl;
    }
}

void printMap(std::map<long long, long long> m) {
    for (const auto& ele : m) {
        std::cout << ele.first << ":" << ele.second << std::endl;
    }
}