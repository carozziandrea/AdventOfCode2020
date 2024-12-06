#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();

struct Node {
    char dir;
    int data;
    Node* left;
    Node* right;

    Node(char dirletter, int value) {
        dir = dirletter;
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

struct Ship {
    int x = 0;
    int y = 0;
};

struct Waypoint {
    int x = 10;
    int y = 1;

    void move(int direction, int value) {
        switch (direction) {
        case 'N': y += value; break;
        case 'S': y -= value; break;
        case 'E': x += value; break;
        case 'W': x -= value; break;
        }
    }

    void rotate(char direction, int degrees) {
        int times = (degrees / 90) % 4;
        if (direction == 'L') times = (4 - times) % 4;
        for (int i = 0; i < times; ++i) {
            int temp = x;
            x = y;
            y = -temp;
        }
    }
};

Node* newDirection(Node* current, int degs, char dir) {
    int times = degs / 90;
    Node* n = current;
    for (int i = 0; i < times; i++) {
        if (dir == 'L') {
            n = n->left;
        }
        else if (dir == 'R') {
            n = n->right;
        }
    }
    return n;
}

void moveShipToWaypoint(Ship& ship, const Waypoint& waypoint, int value) {
    ship.x += waypoint.x * value;
    ship.y += waypoint.y * value;
}

int main()
{
    std::ifstream inputFile;

    //Open File
    inputFile.open("Day12input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    Node* north = new Node('N', 1);
    Node* south = new Node('S', 0);
    Node* east = new Node('E', 10);
    Node* west = new Node('W', 0);

    north->left = west;
    north->right = east;

    south->left = east;
    south->right = west;

    east->left = north;
    east->right = south;

    west->left = south;
    west->right = north;


    //Part 1
    std::string line;
    Node* curDir = east;
    int we = 0;
    int ns = 0;
    char command;
    int value;


    while (std::getline(inputFile, line)) {
        command = line[0];
        value = std::stoi(line.substr(1));
        switch (command) {
        case 'N':
            ns += value;
            break;
        case 'S':
            ns -= value;
            break;
        case 'E':
            we += value;
            break;
        case 'W':
            we -= value;
            break;
        case 'L':
            curDir = newDirection(curDir, value, 'L');
            break;
        case 'R':
            curDir = newDirection(curDir, value, 'R');
            break;
        case 'F':
            if (curDir == east) {
                we += value;
            }
            else if (curDir == west) {
                we -= value;
            }
            else if (curDir == north) {
                ns += value;
            }
            else if (curDir == south) {
                ns -= value;
            }
            break;
        }
    }

    //Part 2
    Ship ship;
    Waypoint waypoint;
    inputFile.close();
    //Open File
    inputFile.open("Day12input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    while (std::getline(inputFile, line)) {
        command = line[0];
        value = std::stoi(line.substr(1));
        switch (command) {
        case 'N': case 'S': case 'E': case 'W':
            waypoint.move(command, value);
            break;
        case 'L': case 'R':
            waypoint.rotate(command, value);
            break;
        case 'F':
            moveShipToWaypoint(ship, waypoint, value);
            break;
        }
    }

    std::cout << "Part1: " << abs(ns) + abs(we) << std::endl;
    std::cout << "Part2: " << std::abs(ship.x) + std::abs(ship.y) << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::endl << duration.count() / 1000.0 << " s " << std::endl;
}
