#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <deque>
#include <chrono>
#include <algorithm>

auto start = std::chrono::high_resolution_clock::now();

std::map<int, long long> memo;  // Cache per la memoization

class Adapter {
public:
    int valore;                             // Valore del nodo
    std::vector<Adapter*> figli;            // Lista dei figli

    Adapter(int val) : valore(val) {}       // Costruttore
};

long long contaCammini(Adapter* nodo) {
    // Controllo se il valore del nodo è già nella cache
    if (memo.find(nodo->valore) != memo.end()) {
        return memo[nodo->valore];
    }

    // Se il nodo è una foglia (non ha figli), un cammino termina qui
    if (nodo->figli.empty()) {
        return 1;  // C'è un cammino che termina qui
    }

    long long conteggio = 0;

    // Calcolo ricorsivamente il numero di cammini per ciascun figlio
    for (Adapter* figlio : nodo->figli) {
        conteggio += contaCammini(figlio);
    }

    // Salva il risultato nella cache e restituiscilo
    memo[nodo->valore] = conteggio;
    return conteggio;
}

int main()
{
    std::ifstream inputFile;

    // Open File
    inputFile.open("Day10input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::string line;
    std::deque<int> adapters;

    adapters.push_back(0);
    while (std::getline(inputFile, line)) {
        adapters.push_back(std::stoi(line));
    }
    std::sort(adapters.begin(), adapters.end());
    adapters.push_back(adapters.back() + 3);

    int i = 0;
    int j = 1;
    int diff1 = 0, diff2 = 0, diff3 = 0;
    while (j < adapters.size()) {
        int diff = adapters[j] - adapters[i];
        switch (diff) {
        case 1:
            diff1++;
            break;
        case 2:
            diff2++;
            break;
        case 3:
            diff3++;
            break;
        }
        i++;
        j++;
    }
    std::cout << "Part1: " << diff1 * diff3 << std::endl;

    // Part 2: Costruzione del grafo degli adattatori
    std::vector<Adapter*> nodes;
    for (int i = 0; i < adapters.size(); i++) {
        Adapter* nodo = new Adapter(adapters[i]);
        nodes.push_back(nodo);
    }

    for (int i = 0; i < nodes.size(); i++) {
        for (int j = i + 1; j < nodes.size(); j++) {
            if ((nodes[j]->valore - nodes[i]->valore) <= 3) {
                nodes[i]->figli.push_back(nodes[j]);
            }
        }
    }

    Adapter* root = nodes[0];
    long long paths = contaCammini(root);

    std::cout << "Part2: " << paths << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::endl << duration.count() << " ms ";
    std::cout << std::endl << duration.count() / 1000.0 << " s " << std::endl;




    // Dealloca i nodi
    for (Adapter* node : nodes) {
        delete node;
    }
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