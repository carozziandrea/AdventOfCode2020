#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "../utils.h"

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile;

    //Open File
    inputFile.open("DayXXinput.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        return 1;
    }

    std::string line;

    while (std::getline(inputFile, line)) {
    }

    std::cout << "Part1: " << std::endl;
    std::cout << "Part2: " << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::endl << duration.count() / 1000.0 << " s " << std::endl;

    return 0;
}