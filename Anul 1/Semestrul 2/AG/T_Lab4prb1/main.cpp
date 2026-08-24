#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n;
    fin >> n;

    vector<int> parent(n);
    vector<int> degree(n, 0);

    for (int i = 0; i < n; i++) {
        fin >> parent[i];
        if (parent[i] != -1)
            degree[parent[i]]++;
    }
    fin.close();

    int root = -1;
    for (int i = 0; i < n; i++)
        if (parent[i] == -1) { root = i; break; }

    set<int> leaves;
    for (int i = 0; i < n; i++)
        if (i != root && degree[i] == 0)
            leaves.insert(i);

    vector<int> prufer;
    prufer.reserve(n - 1);

    for (int step = 0; step < n - 1; step++) {
        int v = *leaves.begin();
        leaves.erase(leaves.begin());

        int p = parent[v];
        prufer.push_back(p);

        degree[p]--;
        if (p != root && degree[p] == 0)
            leaves.insert(p);
    }

    fout << prufer.size() << "\n";
    for (int i = 0; i < (int)prufer.size(); i++) {
        if (i > 0) fout << " ";
        fout << prufer[i];
    }
    fout << "\n";

    fout.close();
    return 0;
}