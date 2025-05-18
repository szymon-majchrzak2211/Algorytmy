#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include <fstream>
#include <ctime>

using namespace std;

struct Edge {
    int from;
    int to;
};

vector<Edge> generateDAG(int vertices, int edges) {
    vector<Edge> result;
    set<pair<int, int>> existing_edges;

    // Tworzymy wierzchołki 1..V
    vector<int> nodes(vertices);
    for (int i = 0; i < vertices; ++i)
        nodes[i] = i + 1;  // <-- indeksowanie od 1

    random_shuffle(nodes.begin(), nodes.end());

    mt19937 rng(time(0));

    while ((int)result.size() < edges) {
        int i = rng() % vertices;
        int j = rng() % vertices;

        if (i >= j) continue;

        int from = nodes[i];
        int to = nodes[j];

        if (existing_edges.count({from, to}) == 0) {
            result.push_back({from, to});
            existing_edges.insert({from, to});
        }
    }

    return result;
}

int main() {
    int V, E;
    cout << "Podaj liczbę wierzchołków: ";
    cin >> V;
    cout << "Podaj liczbę krawędzi: ";
    cin >> E;

    if (E > V * (V - 1) / 2) {
        cout << "Zbyt wiele krawędzi dla DAG z " << V << " wierzchołkami.\n";
        return 1;
    }

    vector<Edge> dag = generateDAG(V, E);

    ofstream outfile("graf.txt");
    if (!outfile.is_open()) {
        cerr << "Nie można otworzyć pliku do zapisu!\n";
        return 1;
    }

    // Pierwsza linia: liczba wierzchołków i krawędzi
    outfile << V << " " << E << "\n";

    // Lista krawędzi (indeksy od 1)
    for (const auto& edge : dag) {
        outfile << edge.from << " " << edge.to << "\n";
    }

    outfile.close();
    cout << "Graf zapisano do pliku 'graf.txt'\n";

    return 0;
}
