#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <array>
#include <map>

#define HALF 100
#define FULL 1000

auto start = std::chrono::high_resolution_clock::now();

std::vector<std::string> split(std::string inputString, char delim);
void printVector(std::vector<int> v);
void printMap(std::unordered_map<std::string, std::string> m);

bool isValid(std::vector<std::string> fields, std::array<std::set<std::string>, FULL> a) {
    for (std::string s : fields) {
        int index = stoi(s);
        if (a[index].size() == 0) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> max_values(const std::unordered_map<std::string, int>& map) {
    std::vector<std::string> result;
    if (map.empty()) {
        return result;  // Restituisce un vettore vuoto se la mappa è vuota
    }

    // Trova il valore massimo nella mappa
    int max_value = std::numeric_limits<int>::min();
    for (const auto& pair : map) {
        if (pair.second > max_value) {
            max_value = pair.second;
        }
    }

    // Aggiunge tutte le chiavi con il valore massimo al vettore
    for (const auto& pair : map) {
        if (pair.second == max_value) {
            result.push_back(pair.first);
        }
    }

    return result;
}

int main()
{
    std::ifstream inputFile;

    //*********** Part 1 ***************

    //Open File
    inputFile.open("Day16input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;
    std::vector<std::string> temp;
    std::array<std::string, FULL> fields;
    std::string range1, range2;
    int errorRate = 0;

    std::getline(inputFile, line);
    //Fields
    while (line != "") {
        //Prendo nome campo
        temp = split(line, ':');
        std::string name = temp[0];

        //Prendo 1-3 or 5-7
        temp = split(temp[1], ' ');

        //Prendo range
        range1 = temp[0];   //1-3
        range2 = temp[2];   //5-7

        temp = split(range1, '-');
        for (int i = stoi(temp[0]); i <= stoi(temp[1]); i++) {
            fields[i] = name;
        }

        temp = split(range2, '-');
        for (int i = stoi(temp[0]); i <= stoi(temp[1]); i++) {
            fields[i] = name;
        }

        std::getline(inputFile, line);
    }

    //"your ticket:"
    std::getline(inputFile, line);

    //My ticket
    std::string myticket;
    std::getline(inputFile, myticket);
    std::getline(inputFile, myticket);      //empty line

    //"nearby tickets:"
    std::getline(inputFile, line);
    while (std::getline(inputFile, line)) {
        temp = split(line, ',');
        for (std::string s : temp) {
            int index = stoi(s);
            if (fields[index] == "") {
                errorRate += index;
            }
        }
    }

    std::cout << "Part1: " << errorRate << std::endl;

    //*********** Part 2 ***************
    inputFile.close();
        //Open File
    inputFile.open("Day16input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::array<std::set<std::string>, FULL> fields2;
    errorRate = 0;
    std::unordered_map<int, std::unordered_map<std::string, int>> occ;

    std::getline(inputFile, line);
    //Fields
    while (line != "") {
        //Prendo nome campo
        temp = split(line, ':');
        std::string name = temp[0];

        //Prendo 1-3 or 5-7
        temp = split(temp[1], ' ');

        //Prendo range
        range1 = temp[0];   //1-3
        range2 = temp[2];   //5-7

        temp = split(range1, '-');
        for (int i = stoi(temp[0]); i <= stoi(temp[1]); i++) {
            fields2[i].insert(name);
        }

        temp = split(range2, '-');
        for (int i = stoi(temp[0]); i <= stoi(temp[1]); i++) {
            fields2[i].insert(name);
        }

        std::getline(inputFile, line);
    }

    //"your ticket:"
    std::getline(inputFile, line);

    //My ticket
    std::getline(inputFile, myticket);
    std::vector<std::string> myTicketVector = split(myticket, ',');
    int maxCols = myTicketVector.size();
    std::getline(inputFile, line);      //empty line

    //"nearby tickets:"
    int rows = 0;
    int col = 0;
    std::getline(inputFile, line);
    while (std::getline(inputFile, line)) {
        rows++;
        temp = split(line, ',');
        if (isValid(temp, fields2)) {
            for (int i = 0; i < temp.size(); i++) {
                std::set<std::string> fieldsForIndex = fields2[stoi(temp[i])];
                for (std::string field : fieldsForIndex) {
                    if (occ[col].find(field) != occ[col].end()) {
                        occ[col][field] = occ[col][field] + 1;
                    }
                    else {
                        occ[col][field] = 1;
                    }
                }
                col++;
            }
        }
        col = 0;
    }
    std::map<std::string, int> finals;
    std::set<std::string> finalFields;

    while (!occ.empty()) {
        for (int i = 0; i < maxCols; i++) {
            std::vector<std::string> max = max_values(occ[i]);
            if (max.size() == 1) {
                finals[max[0]] = i;
                finalFields.insert(max[0]);
                occ.erase(i);
            }
            else {
                for (auto it = occ[i].begin(); it != occ[i].end(); ) {
                    if (it->second < rows || finalFields.find(it->first) != finalFields.end()) {
                        it = occ[i].erase(it);  // erase ritorna l'iteratore al prossimo elemento valido
                    }
                    else {
                        ++it;  // Avanza solo se non si cancella l'elemento corrente
                    }
                }
            }
        }
    }

    int tot = 0;
    //Trovo
    for (std::pair<std::string, int> pair : finals) {
        if (pair.first.find("departure") != std::string::npos) {
            tot += stoi(myTicketVector[pair.second]);
        }
    }

    std::cout << "Part2: " << tot << std::endl;

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

void printMap(std::unordered_map<std::string, std::string> m) {
    for (const auto& ele : m) {
        std::cout << ele.first << ":" << ele.second << std::endl;
    }
}