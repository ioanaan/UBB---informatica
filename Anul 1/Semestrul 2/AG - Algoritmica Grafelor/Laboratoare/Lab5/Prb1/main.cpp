#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int V, E;

struct Edge {
    int to;
    int cap;
};

vector<Edge> edges;
vector<vector<int>> adj;

void addEdge(int u, int v, int c) {
    adj[u].push_back(edges.size());
    edges.push_back({ v, c });
    adj[v].push_back(edges.size());
    edges.push_back({ u, 0 });
}

int bfs(int s, int t, vector<int>& parentEdge) {
    fill(parentEdge.begin(), parentEdge.end(), -1);
    parentEdge[s] = -2; 

    queue<pair<int, int>> q;
    q.push({ s, INF });

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int id : adj[u]) {

            int v = edges[id].to;
            if (parentEdge[v] == -1 && edges[id].cap > 0) {

                parentEdge[v] = id;
                int newFlow = min(flow, edges[id].cap);
                if (v == t) return newFlow;
                q.push({ v, newFlow });
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int totalFlow = 0;
    vector<int> parentEdge(V);

    while (true) {
        int pushed = bfs(s, t, parentEdge);
        if (pushed == 0) break;

        totalFlow += pushed;

        int cur = t;
        while (cur != s) {
            int id = parentEdge[cur];
            edges[id].cap -= pushed;
            edges[id ^ 1].cap += pushed;
            cur = edges[id ^ 1].to;
        }
    }
    return totalFlow;
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

    int result = maxFlow(0, V - 1);
    fprintf(fout, "%d\n", result);

    fclose(fin);
    fclose(fout);
    return 0;
}