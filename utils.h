#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <type_traits>

// Funzione generica per split
template <typename T>
std::vector<T> split(const std::string& inputString, char delim) {
    std::stringstream ss(inputString);
    std::vector<T> tokens;
    std::string token;
    while (std::getline(ss, token, delim)) {
        if (!token.empty()) {
            if constexpr (std::is_same_v<T, std::string>) {
                tokens.push_back(token);
            } else {
                std::istringstream iss(token);
                T value;
                iss >> value;
                tokens.push_back(value);
            }
        }
    }
    return tokens;
}

// Funzione generica per stampare un vettore
template <typename T>
void printVector(const std::vector<T>& v) {
    for (const auto& ele : v) {
        std::cout << ele << std::endl;
    }
}

// Funzione generica per stampare una mappa
template <typename K, typename V>
void printMap(const std::unordered_map<K, V>& m) {
    for (const auto& ele : m) {
        std::cout << ele.first << ": " << ele.second << std::endl;
    }
}