#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

using namespace std;

#define N 10 //размерность матрицы

//Заполнение матрицы числами
void initmatrix(int mat[N][N]) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            mat[i][j] = rand() % 100 - 50;
        }
    }
}

//Функция для печати матрицы=
void print_matrix(int mat[N][N]) {
    for (int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << setw(4) << mat[i][j];
        }
        cout << endl;
    }
    
}

//Функция, которая возвращает максимум в заданной строке и печатает макисмумы для других строк
int maxx(int mat[N][N], int row) {
    int max = abs(mat[row][row]);
    for(int j = row; j < N; ++j) {
        if(max < abs(mat[row][j])) max = abs(mat[row][j]);
    }

    cout << "результаты для всех строк: " << endl;
    for(int i = 0; i < N; ++i) {
        int maxi = abs(mat[i][i]);
        for(int j = i; j < N; ++j) {
            if(maxi < abs(mat[i][j])) maxi = abs(mat[i][j]);
        }
        cout << i+1 << " строка: максимум\t" << maxi << endl;
    }
    return max;
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    int matrix[N][N];
    initmatrix(matrix);
    cout << "Матрица:" << endl;
    print_matrix(matrix);

    int row;
    cout << "Введите номер строки (1-" << N << "): ";
    cin >> row;
    int ma = maxx(matrix, row-1);
    cout << "Максимум для заданной строки: " << ma << endl;
    system("pause");
    return 0;
}