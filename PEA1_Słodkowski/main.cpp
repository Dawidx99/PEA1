#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <stdio.h>

using namespace std;

bool visited[17];

int n;
int* droga;
int wynik = INT_MAX;

int min(int** tab, int i)
{
    int min = INT_MAX;
    for (int k = 0; k < n; k++)
    {
        if (tab[i][k] < min && i != k)
        {
            min = tab[i][k];
        }
    }
    return min;
}

int min2(int** tab, int i)
{
    int first = INT_MAX;
    int second = INT_MAX;
    for (int j = 0; j < n; j++)
    {
        if (i == j)
        {
            continue;
        }

        if (tab[i][j] <= first)
        {
            second = first;
            first = tab[i][j];
        }
        else if (tab[i][j] <= second && tab[i][j] != first)
        {
            second = tab[i][j];
        }
    }
    return second;
}

void tsp(int** tab, int bound, int waga, int pozycja, int pom_droga[])
{
    if (pozycja == n)
    {
        int wynik_pom = waga + tab[pom_droga[pozycja - 1]][pom_droga[0]];
        if (wynik_pom < wynik)
        {
            for (int i = 0; i < n; i++)
            {
                droga[i] = pom_droga[i];
            }
            droga[n] = pom_droga[0];
            wynik = wynik_pom;
        }
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            int reset = bound;
            waga += tab[pom_droga[pozycja - 1]][i];

            if (pozycja == 1)
            {
                bound -= ((min(tab, pom_droga[pozycja - 1]) + min(tab, i)) / 2);
            }
            else
            {
                bound -= ((min2(tab, pom_droga[pozycja - 1]) + min(tab, i)) / 2);
            }
            if (bound + waga < wynik)
            {
                pom_droga[pozycja] = i;
                visited[i] = true;
                tsp(tab, bound, waga, pozycja + 1, pom_droga);
            }
            waga -= tab[pom_droga[pozycja - 1]][i];
            bound = reset;

            for (int k = 0; k < n; k++)
            {
                visited[k] = false;
            }
            for (int j = 0; j <= pozycja - 1; j++)
            {
                visited[pom_droga[j]] = true;
            }
        }
    }
}

int main()
{
    fstream();

    ifstream plik("br17.atsp");

    plik >> n;

    droga = new int[n + 1];


    int** tab;
    tab = new int* [n];

    int* pom_droga;
    pom_droga = new int[n + 1];

    int bound = 0;

    for (int i = 0; i < n; i++)
    {
        tab[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            plik >> tab[i][j];
        }
    }

    struct timeval start, end;
    long mtime, secs, usecs;

    gettimeofday(&start, NULL);

    for (int i = 0; i < n; i++)
    {
        bound += (min(tab, i) + min2(tab, i));
    }
    if (bound & 1)
    {
        bound = bound / 2 + 1;
    }
    else
    {
        bound = bound / 2;
    }
    visited[0] = true;
    pom_droga[0] = 0;
    tsp(tab, bound, 0, 1, pom_droga);

    cout << "Koszt: " << wynik << endl << "Droga: ";

    for (int i = 0; i <= n; i++)
    {
        cout << droga[i] << " ";
    }
    cout << endl;
    gettimeofday(&end, NULL);
    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = (((secs) * 100 + usecs/100.0) + 0.5);
    printf("Czas: %ld ms\n", mtime);
    return 0;
}