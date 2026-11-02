//ЛР 7.1 рек

#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void CreateRows(int** Q, const int rowCount, const int colCount, const int Low, const int High, int rowNo);
void CreateRow(int** Q, const int rowNo, const int colCount, const int Low, const int High, int colNo);
void PrintRows(int** Q, const int rowCount, const int colCount, int rowNo);
void PrintRow(int** Q, const int rowNo, const int colCount, int colNo);
void Sort(int** Q, const int rowCount, const int colCount, int j0);
void SortPass(int** Q, const int rowCount, const int colCount, const int j0, int j1);
void Change(int** Q, const int col1, const int col2, const int rowCount, int rowNo);
void CalcRows(int** Q, const int rowCount, const int colCount, int rowNo, int& S, int& k);
void CalcRow(int** Q, const int rowNo, const int colCount, int colNo, int& S, int& k);

int main()
{
    srand((unsigned)time(NULL));

    int Low = 7;
    int High = 62;
    int rowCount = 7;
    int colCount = 6;

    int** Q = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        Q[i] = new int[colCount];

    CreateRows(Q, rowCount, colCount, Low, High, 0);
    cout << endl;
    PrintRows(Q, rowCount, colCount, 0);

    Sort(Q, rowCount, colCount, 0);
    cout << endl;
    PrintRows(Q, rowCount, colCount, 0);

    int S = 0;
    int k = 0;
    CalcRows(Q, rowCount, colCount, 0, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << endl;
    PrintRows(Q, rowCount, colCount, 0);

    for (int i = 0; i < rowCount; i++)
        delete[] Q[i];
    delete[] Q;

    return 0;
}

void CreateRows(int** Q, const int rowCount, const int colCount, const int Low, const int High, int rowNo)
{
    CreateRow(Q, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(Q, rowCount, colCount, Low, High, rowNo + 1);
}

void CreateRow(int** Q, const int rowNo, const int colCount, const int Low, const int High, int colNo)
{
    Q[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(Q, rowNo, colCount, Low, High, colNo + 1);
}

void PrintRows(int** Q, const int rowCount, const int colCount, int rowNo)
{
    PrintRow(Q, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(Q, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void PrintRow(int** Q, const int rowNo, const int colCount, int colNo)
{
    cout << setw(4) << Q[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(Q, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void Sort(int** Q, const int rowCount, const int colCount, int j0)
{
    SortPass(Q, rowCount, colCount, j0, 0);
    if (j0 < colCount - 2)
        Sort(Q, rowCount, colCount, j0 + 1);
}

void SortPass(int** Q, const int rowCount, const int colCount, const int j0, int j1)
{
    if ((Q[0][j1] < Q[0][j1 + 1])
        ||
        (Q[0][j1] == Q[0][j1 + 1] &&
            Q[1][j1] > Q[1][j1 + 1])
        ||
        (Q[0][j1] == Q[0][j1 + 1] &&
            Q[1][j1] == Q[1][j1 + 1] &&
            Q[2][j1] > Q[2][j1 + 1]))
        Change(Q, j1, j1 + 1, rowCount, 0);
    if (j1 < colCount - j0 - 2)
        SortPass(Q, rowCount, colCount, j0, j1 + 1);
}

void Change(int** Q, const int col1, const int col2, const int rowCount, int rowNo)
{
    int t;
    t = Q[rowNo][col1];
    Q[rowNo][col1] = Q[rowNo][col2];
    Q[rowNo][col2] = t;
    if (rowNo < rowCount - 1)
        Change(Q, col1, col2, rowCount, rowNo + 1);
}

void CalcRows(int** Q, const int rowCount, const int colCount, int rowNo, int& S, int& k)
{
    CalcRow(Q, rowNo, colCount, 0, S, k);
    if (rowNo < rowCount - 1)
        CalcRows(Q, rowCount, colCount, rowNo + 1, S, k);
}

void CalcRow(int** Q, const int rowNo, const int colCount, int colNo, int& S, int& k)
{
    if (Q[rowNo][colNo] % 2 == 0 && !((rowNo + colNo) % 8 == 0))
    {
        S += Q[rowNo][colNo];
        k++;
        Q[rowNo][colNo] = 0;
    }
    if (colNo < colCount - 1)
        CalcRow(Q, rowNo, colCount, colNo + 1, S, k);
}