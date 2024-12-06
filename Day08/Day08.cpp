#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();

std::vector<std::string> instructions;

std::vector<std::string> split(std::string inputString, char delim);
std::pair<int, std::string> executeProgram(std::vector<std::string> instructions);

int main()
{
    std::ifstream inputFile;
    int index = 0;
    int acc = 0;

    std::string inst;
    char symbol;
    std::string operand = "";
    int num;

    std::string current;
    std::vector<std::string> ops;
    std::pair<int, std::string> res;

    //Open File
    inputFile.open("Day08input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        instructions.push_back(line);
    }

    res = executeProgram(instructions);
    std::cout << "Part1: " << res.first << std::endl;

    for(int idx = 0; idx<instructions.size(); idx++){
        current = instructions[idx];
        ops = split(current, ' ');
        inst = ops[0];
        symbol = ops[1][0];
        operand = "";
        for (int i = 1; i < ops[1].size(); i++) {
            operand += ops[1][i];
        }

        std::string newinst = "";
        if (inst == "nop") {
            newinst = newinst + "jmp " + symbol + operand;
            instructions[idx] = newinst;
            res = executeProgram(instructions);
            if (res.second == "ended") {
                break;
            }
            else {
                instructions[idx] = current;
            }
        }
        else if (inst == "jmp") {
            newinst = newinst + "nop " + symbol + operand;
            instructions[idx] = newinst;
            res = executeProgram(instructions);
            if (res.second == "ended") {
                break;
            }
            else {
                instructions[idx] = current;
            }
        }
    }

    std::cout << "Part2: " << res.first << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::endl << duration.count() / 1000.0 << " s " << std::endl;
}

std::pair<int, std::string> executeProgram(std::vector<std::string> instructions) {
    int index = 0;
    int acc = 0;

    std::string inst;
    char symbol;
    std::string operand = "";
    int num;

    std::string current;
    std::vector<std::string> ops;

    std::unordered_set<int> visited;

    while (visited.find(index) == visited.end() && index < instructions.size()) {
        visited.insert(index);
        current = instructions[index];
        ops = split(current, ' ');
        inst = ops[0];
        symbol = ops[1][0];
        operand = "";
        for (int i = 1; i < ops[1].size(); i++) {
            operand += ops[1][i];
        }
        num = stoi(operand);

        if (inst == "nop") {
            index = index + 1;
        }
        else if (inst == "acc") {
            if (symbol == '+') {
                acc += num;
            }
            else if (symbol == '-') {
                acc -= num;
            }
            index = index + 1;
        }
        else if (inst == "jmp") {
            if (symbol == '+') {
                index += num;
            }
            else if (symbol == '-') {
                index -= num;
            }
        }
    }

    std::string why;
    if (index >= instructions.size()) {
        why = "ended";
    }
    else {
        why = "loop";
    }
    return std::make_pair(acc, why);
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