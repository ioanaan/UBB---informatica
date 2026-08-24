//Problema 1

#include <iostream>
#include <fstream>

using namespace std;

void citire(int a[][101], int &n, int &nr_muchii) 
{
    ifstream f("in.txt");

    if (!f.is_open()) 
    {
        cout << "Nu s-a gasit fisierul" << endl;
        exit(1);
    }
    
    f >> n >> nr_muchii;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = 0;

    int x, y;
    for (int i = 0; i < nr_muchii; i++)
    {
        f >> x >> y;
        a[x][y] = 1;
        a[y][x] = 1;
    }

    f.close();
}

void afisare_matrice(int a[][101], int n, int m) 
{
    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= m; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }

    cout << endl;
}

void lista_adiacenta(int a[][101], int n, int l[][101]) 
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            l[i][j] = 0;

    for (int i = 1; i <= n; i++) 
    {
        int k = 1;

        for (int j = 1; j <= n; j++)
            if (a[i][j] != 0) 
            {
                l[i][k] = j;
                k++;
            }
    }
}

void afisare_lista_adiacenta(int l[][101], int n) 
{
    for (int i = 1; i <= n; i++) 
    {
        int j = 1, ok = 0;

        cout << "Varful " << i << " are vecinii:  ";

        while (l[i][j] != 0 && j <= n) 
        {
            cout << l[i][j] << " ";
            j++;
            ok = 1;
        }
        if (ok == 0)
            cout << " -";

        cout << "\n";
    }
    cout << "\n";
}

void matrice_incidenta(int l[][101], int n, int mat_inc[][101], int nr_muchii) {

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= nr_muchii; j++) {
            mat_inc[i][j] = 0;
        }
    }

    int coloana = 1;
    for (int i = 1; i <= n; i++) 
    {
        int j = 1;
        while (l[i][j] != 0 && j <= n)
        {
            if (i < l[i][j]) {
                mat_inc[i][coloana] = 1; 
                mat_inc[l[i][j]][coloana] = 1; 
                coloana++;
            }

            j++;
        }
    }
}

void lista_adiacenta_din_matrice_incidenta(int m[][101], int vf, int nr_muchii, int l[][101]) 
{
    for (int i = 1; i <= vf; i++)
        for (int j = 1; j <= vf; j++)
            l[i][j] = 0;

    for (int j = 1; j <= nr_muchii; j++) 
    {
        int stg = -1, dr = -1;
        for (int i = 1; i <= vf; i++) 
        {
            if (m[i][j] == 1) 
            {
                if (stg == -1)
                    stg = i;
                else
                    dr = i;
            }
        }

        int c;
        c = 1;

        while (l[stg][c] != 0)
            c++;

        l[stg][c] = dr;

        c = 1;

        while (l[dr][c] != 0)
            c++;

        l[dr][c] = stg;
    }
}

void matrice_adiacenta_din_lista_adiacenta(int l[][101], int n, int a[][101]) 
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = 0;

    for (int i = 1; i <= n; i++) 
    {
        int j = 1;
        while (l[i][j] != 0 && j <= n) 
        {
            a[i][l[i][j]] = 1;
            j++;
        }
    }
}

int main() 
{

    int a[101][101], n, l[101][101], m[101][101], nr_muchii;

    citire(a, n, nr_muchii);
    cout << "Matricea de adiacenta este:\n";
    afisare_matrice(a, n, n);

    lista_adiacenta(a, n, l);
    cout << "Lista de adiacenta:\n";
    afisare_lista_adiacenta(l, n);

    matrice_incidenta(l, n, m, nr_muchii);
    cout << "Matricea de incidenta este:\n";
    afisare_matrice(m, n, nr_muchii);

    lista_adiacenta_din_matrice_incidenta(m, n, nr_muchii, l);
    cout << "Lista de adiacenta:\n";
    afisare_lista_adiacenta(l, n);

    matrice_adiacenta_din_lista_adiacenta(l, n, a);
    cout << "Matricea de adiacenta este:\n";
    afisare_matrice(a, n, n);

    lista_adiacenta(a, n, l);
    cout << "Lista de adiacenta:\n";
    afisare_lista_adiacenta(l, n);

    return 0;
}