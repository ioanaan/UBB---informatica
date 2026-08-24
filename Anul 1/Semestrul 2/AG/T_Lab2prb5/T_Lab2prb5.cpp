#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("citire.txt");

void dfs(int varf, int n, int mat[101][101], int v[]) {
    cout << varf << " ";
    v[varf] = 1;
    for (int i = 1; i <= n; i++) {
        if (mat[varf][i] == 1 && v[i] == 0)
            dfs(i, n, mat, v);
    }
}

int main() {
    int n, m, mat[101][101] = { 0 }, x, y;

    fin >> n >> m;  // citește din fișier

    for (int i = 1; i <= m; i++) {
        fin >> x >> y;
        mat[x][y] = 1;
    }

    for (int i = 1; i <= n; i++) {
        int v[101] = { 0 };
        dfs(i, n, mat, v);
        cout << '\n';
    }

    return 0;
}