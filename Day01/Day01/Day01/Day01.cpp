#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <string>
using namespace std;

int main()
{
    ifstream inputFile;

    //Open File
    inputFile.open("day01input.txt");
    if (!inputFile) {
        cerr << "Unable to open file";
        exit(1);
    }

    string line;
    list<int> nums;
    map<int, int> map;
    int complement = 0;

    while (inputFile >> line) {
        complement = 2020 - stoi(line);
        if (map.find(complement) != map.end()) {
            cout << "Part 1:" << stoi(line) * complement << endl;
        }

        for (auto& elem : map) {
            int complement2 = elem.second - stoi(line);
            if (map.find(complement2) != map.end()) {
                std::cout << "Part 2: " << complement2 * stoi(line) * elem.first << endl;
                break;
            }
        }
        map[stoi(line)] = complement;
    }