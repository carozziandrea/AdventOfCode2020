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
void printVector(std::vector<int> v);
void printMap(std::map<std::string, std::string> m);

bool checkPattern(std::vector<int> b, std::vector<int> occ) {
    for (int i = 0; i < occ.size(); i++) {
        if (occ[i] % b[i] != 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    std::ifstream inputFile;

    //Open File
    inputFile.open("Day13input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;
    int minDeparture;
    std::vector<std::string> bus;

    std::getline(inputFile, line);
    minDeparture = stoi(line);
    std::getline(inputFile, line);
    bus = split(line, ',');
    int departure = minDeparture - 1;
    bool found = false;
    int busNum = 0;

    while (!found) {
        departure++;
        for (int i = 0; i < bus.size(); i++) {
            if (bus[i] != "x") {
                busNum = stoi(bus[i]);
                int quo = departure % busNum;
                if (quo == 0) {
                    found = true;
                    break;
                }
            }
        }
    }

    std::cout << "Part1: " << (departure - minDeparture) * busNum  << std::endl;

    //Riempio occorrenze
    std::vector<int> occ;
    std::vector<int> bus2;
    for (int i = 0; i < bus.size(); i++) {
        if (bus[i] != "x") {
            bus2.push_back(stoi(bus[i]));
            occ.push_back(i);
        }
    }

    found = false;
    while (!found) {
        std::cout << occ[0] << std::endl;
        if (checkPattern(bus2, occ)) {
            break;
        }
        else {
            for (int i = 0; i < bus2.size(); i++) {
                occ[i] += bus2[i];
            }
        }
    }


    std::cout << "Part2: " << departure << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::endl << duration.count() / 1000.0 << " s " << std::endl;
}

std::vector<std::string> split(std::string inputString, char delim) {
    std::stringstream ss(inputString);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(ss, token, delim)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
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