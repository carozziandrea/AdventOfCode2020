#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <vector>
using namespace std;

vector<string> split(string inputString, char delim);
void printVector(vector<string> v);
void printMap(map<string, string> m);
bool isValid(map<string, string> m);

int main()
{
    ifstream inputFile;

    //Open File
    inputFile.open("Day04input.txt");
    if (!inputFile) {
        cerr << "Unable to open file";
        exit(1);
    }

    string line;
    map<string, string> passport;
    vector<string> entries;
    vector<string> data;
    int valid = 0;
    int validP2 = 0;

    while (getline(inputFile, line)) {
        if(line != "") {
            entries = split(line, ' ');
            for (string entry : entries) {
                data = split(entry, ':');
                passport.insert({data[0], data[1]});
            }
        }else {
            if (passport.size() == 8) {
                valid++;
                if (isValid(passport)) {
                    validP2++;
                }
            }
            else if (passport.size() == 7 && passport.find("cid") == passport.end()) {
                valid++;
                if (isValid(passport)) {
                    validP2++;
                }
            }
            passport.clear();
        }
    }

    if (passport.size() == 8) {
        valid++;
        if (isValid(passport)) {
            validP2++;
        }
    }
    else if (passport.size() == 7 && passport.find("cid") == passport.end()) {
        valid++;
        if (isValid(passport)) {
            validP2++;
        }
    }
    cout << endl;;
    cout << "Part1: " << valid << endl;
    cout << "Part2: " << validP2 << endl;

}

bool isValid(map<string, string> m) {
    //*** Check birth year ***
    int byr = stoi(m.find("byr")->second);
    if (byr < 1920 || byr > 2002) {
        cout << byr << "Wrong birth year" << endl;
        return false;
    }

    //*** Check issue year ***
    int iyr = stoi(m.find("iyr")->second);
    if (iyr < 2010 || iyr > 2020) {
        cout << iyr << "Wrong issue year" << endl;
        return false;
    }

    //*** Check expiration year ***
    int eyr = stoi(m.find("eyr")->second);
    if (eyr < 2020 || eyr > 2030) {
        cout << eyr << "Wrong expiration year" << endl;
        return false;
    }

    //*** Check height ***
    string hgt = m.find("hgt")->second;
    int h = stoi(hgt);
    if (hgt.substr(hgt.size() - 2, 2) == "cm") {
        if (h < 150 || h > 193) {
            cout << hgt << "Wrong cm height" << endl;
            return false;
        }
    }
    else if (hgt.substr(hgt.size() - 2, 2) == "in") {
        if (h < 59 || h > 76) {
            cout << hgt << "Wrong in height" << endl;
            return false;
        }
    }
    else {
        cout << hgt << "Wrong height" << endl;
        return false;
    }

    //** Check hair color ***
    string hcl = m.find("hcl")->second;
    if (hcl[0] != '#') {
        cout << hcl << "Missing # in hair color" << endl;
        return false;
    }
    if (hcl.size() != 7) {
        cout << hcl << "Wrong hair color length" << endl;
        return false;
    }
    for (char c : hcl.substr(1, 6)) {
        if (!isdigit(c) && !islower(c)) {
            cout << hcl << "Wrong hair color format" << endl;
            return false;
        }
    }

    //*** Check eye color ***
    vector<string> colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    string ecl = m.find("ecl")->second;
    if (find(colors.begin(), colors.end(), ecl) == colors.end()) {
        cout << ecl << "Wrong eye color" << endl;
        return false;
    }

    //*** Check passport id ***
    string pid = m.find("pid")->second;
    if (pid.size() != 9) {
        cout << pid << "Wrong passport id size" << endl;
        return false;
    }
    for (char c : pid) {
        if (!isdigit(c)) {
            cout << pid << "Wrong passport id format" << endl;
            return false;
        }
    }
    return true;
}

vector<string> split(string inputString, char delim) {
    stringstream ss(inputString);
    vector<string> tokens;
    string token;
    while (getline(ss, token, delim)) {
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

void printVector(vector<string> v) {
    for (string ele : v) {
        cout << ele << endl;
    }
}

void printMap(map<string, string> m) {
    for (const auto& ele : m) {
        cout << ele.first << ":" << ele.second << endl;
    }
}