"""
CERINTA

8) Generați toate sub-secvențele de lungime 2n+1, formate din 0, -1 și 1,
astfel încât a1 = 0, ..., a2n+1 = 0 și
|a(i+1) - ai| = 1 sau 2, pentru orice i,  1 <= i <= 2n
"""

def gener_recursiv(k, n, v):
    """
    Specificatii Recursiv:
    :param k: Pozitia curenta in vector (nivelul recursivitatii).
    :param n: Parametrul de lungime (2n+1).
    :param v: Vectorul solutie.
    """
    for i in range(-1, 2):
        v[k] = i
        if abs(v[k - 1] - v[k]) in [1, 2]:
            if k == 2 * n + 1:
                if v[k] == 0:
                    print(*(v[1:2 * n + 2]))
            else:
                gener_recursiv(k + 1, n, v)


def gener_iterativ(n):
    """
    Specificatii Iterativ:
    :param n: Parametrul de lungime (2n+1).
    :v: Vectorul solutie (gestionat local).
    :val: Stiva de stari pentru a retine progresul pe fiecare pozitie.
    """
    m = 2 * n + 1
    v = [0] * (m + 1)
    val = [-2] * (m + 1)
    v[1] = 0
    k = 2

    while k > 1:
        gasit = False
        for i in range(val[k] + 1, 2):
            v[k] = i
            val[k] = i
            if abs(v[k - 1] - v[k]) in [1, 2]:
                gasit = True
                break

        if gasit:
            if k == m:
                if v[k] == 0:
                    print(*(v[1:m + 1]))
            else:
                k += 1
                val[k] = -2
        else:
            k -= 1


def menu():
    while True:
        print("\n--- MENIU GENERARE SECVENTE ---")
        print("0. Iesire")
        print("1. Varianta iterativa")
        print("2. Varianta recursiva")

        optiune = input("\nIntrodu optiunea: ")

        if optiune == '1':
            n = int(input("Scrie numar: "))
            gener_iterativ(n)

        elif optiune == '2':
            n = int(input("Scrie numar: "))
            v = [0] * (2 * n + 2)
            v[1] = 0
            gener_recursiv(2, n, v)

        elif optiune == '0':
            print("Bye bye!")
            break

        else:
            print("Nu este alta!")

if __name__ == "__main__":
    menu()