#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const int dim = 1e6;

struct Nod {
    int x, y, w;
} u[dim], sol[dim];

int p[dim], t[dim];

bool cmp(Nod a, Nod b) {
    return a.w < b.w;
}

int root(int x) {
    while (x != t[x]) {
        t[x] = t[t[x]]; 
        x = t[x];
    }
    return x;
}

void uneste(int x, int y) {
    if (p[x] < p[y])      t[x] = y;
    else if (p[x] > p[y]) t[y] = x;
    else { t[y] = x; p[x]++; }
}

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, m;
    fin >> n >> m;

    for (int i = 0; i < n; i++) t[i] = i;

    for (int i = 1; i <= m; i++)
        fin >> u[i].x >> u[i].y >> u[i].w;
    fin.close();

    sort(u + 1, u + m + 1, cmp);

    int i = 1, k = 0, ct = 0;
    while (k < n - 1) {
        int rx = root(u[i].x);
        int ry = root(u[i].y);
        if (rx != ry) {
            k++;
            ct += u[i].w;
            sol[k] = u[i];
            uneste(rx, ry);
        }
        i++;
    }

    fout << ct << "\n" << k << "\n";
    for (int i = 1; i <= k; i++)
        fout << sol[i].x << " " << sol[i].y << "\n";
    fout.close();

    return 0;
}