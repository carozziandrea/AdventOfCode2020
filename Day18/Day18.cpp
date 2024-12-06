#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <stack>
#include <queue>

auto start = std::chrono::high_resolution_clock::now();

std::vector<std::string> split(std::string inputString, char delim);
void printVector(std::vector<int> v);
void printMap(std::unordered_map<std::string, std::string> m);

int calculate(int a, int b, char operation) {
    if (operation == '+') {
        return a + b;
    }
    else if (operation == '*') {
        return a * b;
    }
    else {
        std::cerr << "ERRORE OPERATORE";
        return -1;
    }
}

int evalParenthesis(std::string subStr) {
    std::queue<char> operators;
    std::queue<char> numbers;
    int result = 0;
    int index = 0;
    char curChar = subStr[0];
    std::string curStr = "";
    while (index < subStr.size() && curChar != ')') {
        if (curChar == '+' || curChar == '*') {
            operators.push(curChar);
        }
        else if (curChar == '(') {
            numbers.push(evalParenthesis(subStr.substr(index)));
        }
        else if (curChar != ' ') {
            curStr.push_back(curChar);
        }
        else {
            numbers.push(stoi(curStr));
            curStr = "";
        }
        index++;
    }

    return result;
}

int main()
{
    std::ifstream inputFile;

    //Open File
    inputFile.open("Day18input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;
    std::getline(inputFile, line);
    //std::vector<std::string> expression;
    std::string curStr = "";
    std::queue<int> numbers;
    std::stack<char> operatorStack;
    std::stack<std::string> subExp;
    char curChar;

    int exprIndex = 0;
    while (exprIndex < line.size()) {
        curChar = line[exprIndex];
        if (curChar == '+' || curChar == '*') {
            operatorStack.push(curChar);
        }
        else if (curChar == '(') {
            numbers.push(evalParenthesis(line.substr(exprIndex)));
        }
        else if (curChar != ' ') {
            curStr.push_back(curChar);
        }
        else {
            numbers.push(stoi(curStr));
            curStr = "";
        }
        exprIndex++;
    }

    numbers.push(stoi(curStr));

    std::cout << "Part1: " << std::endl;
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

void printMap(std::unordered_map<std::string, std::string> m) {
    for (const auto& ele : m) {
        std::cout << ele.first << ":" << ele.second << std::endl;
    }
}