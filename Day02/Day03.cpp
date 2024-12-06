#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
using namespace std;

int main()
{
    ifstream inputFile;

    //Open File
    inputFile.open("Day03input.txt");
    if (!inputFile) {
        cerr << "Unable to open file";
        exit(1);
    }

    string line;

    int trees = 0;
    int index = 3;

    while (getline(inputFile, line)) {
        cout << line[index] << endl;
        index += 3;
    }

    cout << "Part1: " << trees << endl;
}