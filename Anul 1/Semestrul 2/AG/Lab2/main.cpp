#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

/*
* 1. Implementați algoritmul lui Moore pentru un graf orientat neponderat 
* (algoritm bazat pe breadth-first search). 
* Datele sunt citite din fisierul graf.txt. 
* Primul rând din graf.txt conține numărul vârfurilor, 
* iar următoarele rânduri conțin muchiile grafului. 
* Programul trebuie să afiseze lanțul cel mai scurt dintr-un vârf 
* (vârful sursa poate fi citit de la tastatura).
*/

using namespace std;

ifstream f("graf.txt");

const int NMAX = 105;
const int INF = 100000;
vector<vector<int>> G(NMAX);
int n;

struct solution 
{
    vector<int> V, P;
};

void read() 
{
    f >> n;
    int x, y;
    while (f >> x >> y)
    {
        G[x].push_back(y); // Graf orientat
    }
}

// Algoritmul lui Moore
solution moore(int source) 
{
    vector<int> V(n + 1, INF);
    vector<int> P(n + 1, 0);
    queue<int> q;

    V[source] = 0;
    q.push(source);

    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();

        for (int v : G[u])
        {
            if (V[v] == INF) 
            { 
                V[v] = V[u] + 1;
                P[v] = u;
                q.push(v);
            }
        }
    }
    return { V, P };
}

// Reconstrucția drumului
vector<int> road(int dest, const vector<int>& P) 
{
    vector<int> sol;
    for (int x = dest; x != 0; x = P[x]) 
    {
        sol.push_back(x);
    }
    reverse(sol.begin(), sol.end());
    return sol;
}

void solve() 
{
    read();

    if (n == 0) return;

    int source, dest;
    cout << "Introduceti nodul sursa: ";
    cin >> source;
    cout << "Introduceti nodul destinatie: ";
    cin >> dest;

    solution res = moore(source);

    if (res.V[dest] == INF)
    {
        cout << "\nNu exista drum de la nodul " << source << " la nodul " << dest << "." << endl;
    }
    else 
    {
        vector<int> r = road(dest, res.P);
        cout << "\nLantul cel mai scurt are lungimea " << res.V[dest] << " si este: \n";
        for (int i = 0; i < r.size(); i++) 
        {
            cout << r[i] << (i == r.size() - 1 ? "" : " -> ");
        }
        cout << endl;
    }
}

int main()
{
    solve();
    return 0;
}