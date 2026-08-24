#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;


const int NMAX = 100005;
const int LOG = 17;

struct Muchie {
    int u, v, c, idx;
};

int n, m;
Muchie muchii[NMAX]; 

vector<pair<int, int>> adj[NMAX];

int parent[NMAX][LOG];
int depth[NMAX];
int edge_to_parent[NMAX];

int best[NMAX];

void dfs(int nod, int par, int d) {
    depth[nod] = d;
    parent[nod][0] = par;
    for (int k = 1; k < LOG; k++)
        parent[nod][k] = parent[parent[nod][k - 1]][k - 1];

    for (auto [vecin, idx_muchie] : adj[nod]) {
        if (vecin != par) {
            edge_to_parent[vecin] = idx_muchie;
            dfs(vecin, nod, d + 1);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int k = 0; k < LOG; k++)
        if ((diff >> k) & 1)
            u = parent[u][k];

    if (u == v) return u;

    for (int k = LOG - 1; k >= 0; k--)
        if (parent[u][k] != parent[v][k]) {
            u = parent[u][k];
            v = parent[v][k];
        }
    return parent[u][0];
}


void urca_si_actualizeaza(int nod, int anc, int idx_muchie) {
    while (nod != anc) {
        int em = edge_to_parent[nod];
        if (muchii[idx_muchie].c < muchii[best[nod]].c) {
            best[nod] = idx_muchie;
        }
        nod = parent[nod][0];
    }
}

int main() {
    ifstream fin("arb.in");
    ofstream fout("arb.out");

    fin >> n >> m;

    for (int i = 0; i < m; i++) {
        fin >> muchii[i].u >> muchii[i].v >> muchii[i].c;
        muchii[i].idx = i;
    }

    for (int i = 0; i < n - 1; i++) {
        adj[muchii[i].u].push_back({ muchii[i].v, i });
        adj[muchii[i].v].push_back({ muchii[i].u, i });
    }

    muchii[m].c = INT_MAX; muchii[m].idx = -1;
    for (int i = 0; i < n; i++) best[i] = m; 

    dfs(0, 0, 0);


    for (int i = n - 1; i < m; i++) {
        int u = muchii[i].u;
        int v = muchii[i].v;
        int l = lca(u, v);
        urca_si_actualizeaza(u, l, i);
        urca_si_actualizeaza(v, l, i);
    }

    vector<int> copil_al_muchiei(n - 1, -1);
    for (int v = 1; v < n; v++) { 
        copil_al_muchiei[edge_to_parent[v]] = v;
    }

    for (int i = 0; i < n - 1; i++) {
        int v = copil_al_muchiei[i];
        if (best[v] == m)
            fout << -1 << "\n"; // nu exista inlocuire
        else
            fout << best[v] << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}