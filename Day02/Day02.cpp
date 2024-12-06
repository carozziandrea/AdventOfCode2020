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
    inputFile.open("Day02input.txt");
    if (!inputFile) {
        cerr << "Unable to open file";
        exit(1);
    }

    string line;
    int min;
    int max;
    char letter;
    char extra;
    string pass;

    int valid_pass = 0;
    int valid_pass_p2 = 0;

    while (getline(inputFile, line)) {
        //Part 1
        // Usa stringstream per leggere e dividere la linea
        stringstream ss(line);

        // Parsing dell'input tipo "1-3 a: password"
        ss >> min >> extra >> max >> letter >> extra >> pass;

        int count = 0;
        for (int i = 0; i < pass.size(); i++) {
            if (pass[i] == letter) {
                count++;
            }
        }

        if (count >= min && count <= max) {
            valid_pass++;
        }

        //Part 2
        if (pass[min - 1] == letter && pass[max - 1] != letter) {
            valid_pass_p2++;
        }else if(pass[min - 1] != letter && pass[max - 1] == letter) {
            valid_pass_p2++;
        }
    }

    cout << "Part1: " << valid_pass << endl;
    cout << "Part2: " << valid_pass_p2 << endl;
}