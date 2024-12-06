#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <set>

std::vector<std::string> split(std::string inputString, char delim);
void printVector(std::vector<int> v);
void printMap(std::map<std::string, std::string> m);

int main()
{
    std::ifstream inputFile;

    //Open File
    inputFile.open("Day06input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;
    std::set<int> questions;
    std::map<char, int> questions_P2;
    int tot_q = 0;
    int tot_q2 = 0;
    int people = 0;

    while (std::getline(inputFile, line)) {
        if(line != "") {
            for (char c : line) {
                if (questions.find(c) == questions.end()) {
                    questions.insert(c);
                }

                //Part 2
                questions_P2[c]++;
            }
            people++;
        }else {
            tot_q += questions.size();
            questions.clear();

            //Part 2
            for (const auto& ele : questions_P2) {
                if (ele.second == people) {
                    tot_q2++;
                }
            }
            people = 0;
            questions_P2.clear();
        }
    }

    tot_q += questions.size();
    questions.clear();

    //Part 2
    for (const auto& ele : questions_P2) {
        if (ele.second == people) {
            tot_q2++;
        }
    }

    std::cout << "Part1: " << tot_q << std::endl;
    std::cout << "Part2: " << tot_q2 << std::endl;

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