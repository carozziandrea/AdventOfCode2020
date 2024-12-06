#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <chrono>
#include <numeric>

auto start = std::chrono::high_resolution_clock::now();

int main()
{
    std::ifstream inputFile;

    //Open File
    inputFile.open("Day09input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    int part1 = 0;
    std::string line;
    std::deque<int> nums;
    int preamble = 25;
    int curnum = 0;
    int complement = 0;
    bool found = false;

    for (int i = 0; i < preamble; i++) {
        std::getline(inputFile, line);
        nums.push_back(std::stoi(line));
    }

    while (std::getline(inputFile, line)) {
        curnum = std::stoi(line);
        for (int n : nums) {
            complement = curnum - n;
            if (std::find(nums.begin(), nums.end(), complement) != nums.end() && (n != complement)) {
                found = true;
            }
        }

        if (!found) {
            part1 = curnum;
            break;
        }
        else {
            nums.pop_front();
            nums.push_back(curnum);
            found = false;
        }
    }

    std::cout << "Part1: " << part1 << std::endl;

    //Part2
    std::ifstream inputFile2;
    long long part2 = 0;
    std::deque<long long> nums2;
    nums.clear();

    inputFile2.open("Day09input.txt");
    if (!inputFile2) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    while (std::getline(inputFile2, line)) {
        nums2.push_back(std::stoll(line));
    }

    int i = 0;
    int j = 0;
    long long acc = nums2[i];
    while (j<nums2.size()) {
        j++;
        acc += nums2[j];
        if (acc == part1) {
            auto min = std::min_element(nums2.begin()+i, nums2.begin() + j + 1);
            auto max = std::max_element(nums2.begin()+1, nums2.begin() + j + 1);
            part2 = *min + *max;
            break;
        }
        else if (acc > part1) {
            i++;
            j=i;
            acc = nums2[i];
        }
    }
    
    std::cout << "Part2: " << part2 << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::endl << duration.count() / 1000.0 << " s " << std::endl;
}