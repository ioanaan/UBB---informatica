#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii; // (cost, nod)

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E, S;
    fin >> V >> E >> S;

    // Lista de adiacenta: adj[u] = { (v, w), ... }
    vector<vector<pii>> adj(V);

    for (int i = 0; i < E; i++) {
        int x, y, w;
        fin >> x >> y >> w;
        adj[x].push_back({ y, w });
    }

    // Dijkstra cu priority queue (min-heap)
    vector<long long> dist(V, LLONG_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[S] = 0;
    pq.push({ 0, S });

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Daca am gasit deja un drum mai scurt, sarim
        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }

    // Scriem rezultatele
    for (int i = 0; i < V; i++) {
        if (i > 0) fout << " ";
        if (dist[i] == LLONG_MAX)
            fout << "INF";
        else
            fout << dist[i];
    }
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}