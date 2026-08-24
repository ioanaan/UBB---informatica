#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int M;
    fin >> M;

    int N = M + 1;
    deque<int> K(M);
    vector<int> cnt(N, 0);

    for (int i = 0; i < M; i++) {
        fin >> K[i];
        cnt[K[i]]++;
    }
    fin.close();

    set<int> notInK;
    for (int i = 0; i < N; i++)
        if (cnt[i] == 0) notInK.insert(i);

    vector<int> parent(N, -1);

    for (int i = 0; i < N - 1; i++) {
        int x = K.front();

        int y = *notInK.begin();
        notInK.erase(notInK.begin());
        parent[y] = x;

        K.pop_front();
        cnt[x]--;
        if (cnt[x] == 0) notInK.insert(x);

        K.push_back(y);
        cnt[y]++;
    }

    fout << N << "\n";
    for (int i = 0; i < N; i++) {
        if (i > 0) fout << " ";
        fout << parent[i];
    }
    fout << "\n";

    fout.close();
    return 0;
}