#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin(R"(C:\Users\Admin\Desktop\UBB\Anul 1\Sem 2\AG\Practic\input.txt)");

    int n;
    fin >> n;

    int A[11][11] = {};

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fin >> A[i][j];

    fin.close();

    int u[51], v[51];
    int m = 0;

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (A[i][j] == 1)
            {
                m++;
                u[m] = i;
                v[m] = j;
            }

    int M[11][51] = {};
    for (int j = 1; j <= m; j++)
    {
        M[u[j]][j] = 1;
        M[v[j]][j] = 1;
    }

    cout << "Matricea de incidenta pentu " << n << " varfuri si " << m << " muchii:" << endl;
    cout << endl;
    cout << "     ";

    for (int j = 1; j <= m; j++)
        cout << "m" << j << " ";

    cout << endl;

    for (int i = 1; i <= n; i++)
    {
        cout << "v" << i << " : ";
        for (int j = 1; j <= m; j++)
            cout << " " << M[i][j] << " ";
        cout << endl;
    }

    return 0;
}