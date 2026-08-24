// Problema 3 - Ciclu eulerian (algoritmul Hierholzer iterativ)
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

static const int IN_BUF = 1 << 20;
static char inBuf[IN_BUF];
static int  inPos = 0, inLen = 0;
static FILE* fin;

static inline int readChar() {
    if (inPos == inLen) {
        inLen = (int)fread(inBuf, 1, IN_BUF, fin);
        inPos = 0;
        if (inLen == 0) return -1;
    }
    return inBuf[inPos++];
}

static inline int readInt() {
    int c, x = 0;
    do { c = readChar(); } while (c != -1 && (c < '0' || c > '9'));
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
    return x;
}

static const int OUT_BUF = 1 << 20;
static char outBuf[OUT_BUF];
static int  outPos = 0;
static FILE* fout;

static inline void flushOut() {
    fwrite(outBuf, 1, outPos, fout);
    outPos = 0;
}

static inline void writeInt(int x) {
    if (outPos > OUT_BUF - 16) flushOut();
    if (x == 0) {
        outBuf[outPos++] = '0';
    }
    else {
        char tmp[12];
        int n = 0;
        while (x > 0) { tmp[n++] = (char)('0' + x % 10); x /= 10; }
        while (n--) outBuf[outPos++] = tmp[n];
    }
    outBuf[outPos++] = ' ';
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");
    if (!fin || !fout) {
        fprintf(stderr, "Cannot open files\n");
        return 1;
    }

    int V = readInt();
    int E = readInt();

    vector<vector<int>> adj(V);
    vector<int> to(2 * E);
    vector<char> used(E, 0);

    for (int k = 0; k < E; k++) {
        int x = readInt();
        int y = readInt();
        to[2 * k] = y;
        to[2 * k + 1] = x;
        adj[x].push_back(2 * k);
        adj[y].push_back(2 * k + 1);
    }
    fclose(fin);

    int start = 0;
    for (int i = 0; i < V; i++) {
        if (!adj[i].empty()) { start = i; break; }
    }

    vector<int> cur(V, 0);

    vector<int> stack;
    vector<int> path;
    stack.reserve(E + 1);
    path.reserve(E + 1);

    stack.push_back(start);
    while (!stack.empty()) {
        int u = stack.back();
        while (cur[u] < (int)adj[u].size() && used[adj[u][cur[u]] >> 1]) {
            cur[u]++;
        }
        if (cur[u] == (int)adj[u].size()) {
            path.push_back(u);
            stack.pop_back();
        }
        else {
            int id = adj[u][cur[u]++];
            used[id >> 1] = 1;
            stack.push_back(to[id]);
        }
    }

    int n = (int)path.size();
    int writeCount = n;
    if (n >= 2 && path.front() == path.back()) writeCount = n - 1;

    for (int i = 0; i < writeCount; i++) writeInt(path[i]);

    flushOut();
    fclose(fout);
    return 0;
}