// Problema 2 - Flux maxim prin pompare preflux (push-relabel)
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int V, E;

struct Edge {
    int to;
    int cap;
};

vector<Edge> edges;
vector<vector<int>> adj;

void addEdge(int u, int v, int c) {
    adj[u].push_back((int)edges.size());
    edges.push_back({ v, c });
    adj[v].push_back((int)edges.size());
    edges.push_back({ u, 0 });
}

vector<int>  height; 
vector<long long> excess;
vector<int>  cur;
vector<int>  countH;
vector<bool> inQueue;
queue<int>   activeQueue;

int s, t;

inline void enqueue(int u) {
    if (!inQueue[u] && u != s && u != t && excess[u] > 0) {
        inQueue[u] = true;
        activeQueue.push(u);
    }
}

void globalRelabel() {
    fill(height.begin(), height.end(), 2 * V);
    fill(countH.begin(), countH.end(), 0);

    height[t] = 0;
    queue<int> q;
    q.push(t);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int id : adj[u]) {
            int v = edges[id].to;
            if (height[v] == 2 * V && edges[id ^ 1].cap > 0) {
                height[v] = height[u] + 1;
                q.push(v);
            }
        }
    }

    height[s] = V;

    while (!activeQueue.empty()) activeQueue.pop();
    fill(inQueue.begin(), inQueue.end(), false);
    for (int u = 0; u < V; u++) {
        if (height[u] < 2 * V) countH[height[u]]++;
        cur[u] = 0;
        if (u != s && u != t && excess[u] > 0 && height[u] < 2 * V) {
            enqueue(u);
        }
    }
}

void push(int u, int idEdge) {
    Edge& e = edges[idEdge];
    int v = e.to;
    long long d = min(excess[u], (long long)e.cap);
    e.cap -= (int)d;
    edges[idEdge ^ 1].cap += (int)d;
    excess[u] -= d;
    excess[v] += d;
    enqueue(v);
}

void relabel(int u) {
    int oldH = height[u];
    int newH = 2 * V;
    for (int id : adj[u]) {
        if (edges[id].cap > 0) {
            newH = min(newH, height[edges[id].to] + 1);
        }
    }

    countH[oldH]--;
    if (countH[oldH] == 0 && oldH < V) {
        for (int i = 0; i < V; i++) {
            if (i != s && i != t && height[i] > oldH && height[i] < V) {
                countH[height[i]]--;
                height[i] = V + 1;
            }
        }
    }

    height[u] = newH;
    if (newH < 2 * V) countH[newH]++;
    cur[u] = 0;
}

void discharge(int u) {
    while (excess[u] > 0) {
        if (cur[u] == (int)adj[u].size()) {
            relabel(u);
            if (height[u] >= 2 * V) return;
        }
        else {
            int id = adj[u][cur[u]];
            int v = edges[id].to;
            if (edges[id].cap > 0 && height[u] == height[v] + 1) {
                push(u, id);
            }
            else {
                cur[u]++;
            }
        }
    }
}

long long maxFlow() {
    height.assign(V, 0);
    excess.assign(V, 0);
    cur.assign(V, 0);
    countH.assign(2 * V + 1, 0);
    inQueue.assign(V, false);

    height[s] = V;
    countH[0] = V - 1;
    countH[V] = 1;

    for (int id : adj[s]) {
        int v = edges[id].to;
        int c = edges[id].cap;
        if (c > 0) {
            edges[id].cap = 0;
            edges[id ^ 1].cap += c;
            excess[v] += c;
            excess[s] -= c;
            if (v != t) enqueue(v);
        }
    }

    globalRelabel();

    int workCounter = 0;
    int workLimit = V;

    while (!activeQueue.empty()) {
        int u = activeQueue.front();
        activeQueue.pop();
        inQueue[u] = false;
        discharge(u);

        if (++workCounter >= workLimit) {
            globalRelabel();
            workCounter = 0;
        }
    }

    return excess[t];
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE* fin = fopen(argv[1], "r");
    FILE* fout = fopen(argv[2], "w");
    if (!fin || !fout) {
        fprintf(stderr, "Cannot open files\n");
        return 1;
    }

    fscanf(fin, "%d %d", &V, &E);
    adj.assign(V, vector<int>());
    edges.reserve(2 * E);

    for (int i = 0; i < E; i++) {
        int x, y, c;
        fscanf(fin, "%d %d %d", &x, &y, &c);
        addEdge(x, y, c);
    }

    s = 0;
    t = V - 1;

    long long result = maxFlow();
    fprintf(fout, "%lld\n", result);

    fclose(fin);
    fclose(fout);
    return 0;
}