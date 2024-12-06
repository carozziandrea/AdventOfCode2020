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
    int numline = 2;
    int tot_trees = 0;
    int trees1 = 0;
    int trees2 = 0;
    int trees3 = 0;
    int trees4 = 0;
    int trees5 = 0;
    int index1 = 1;
    int index2 = 3;
    int index3 = 5;
    int index4 = 7;
    int index5 = 0;
    int l = 0;

    getline(inputFile, line);
    l = line.size();

    while (getline(inputFile, line)) {
        if (line[index1] == '#') {
            trees1++;
        }
        if (line[index2] == '#') {
            trees2++;
        }
        if (line[index3] == '#') {
            trees3++;
        }
        if (line[index4] == '#') {
            trees4++;
        }
        if ((numline % 2) != 0 && line[index5] == '#') {
            trees5++;
            index5 = (index5 + 1) % l;
        }

        index1 = (index1 + 1) % l;
        index2 = (index2 + 3) % l;
        index3 = (index3 + 5) % l;
        index4 = (index4 + 7) % l;
        numline++;
    }

    tot_trees = trees1 * trees2 * trees3 * trees4 * trees5;

    cout << "Part1: " << trees2 << endl;
    cout << "Part2: " << tot_trees << endl;

}