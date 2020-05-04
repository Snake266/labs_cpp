#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

using namespace std;

#define N 12 //размер матрицы

//Функция для заполнение матрциы целыми числами
void fillmatrix(int mat[N][N]) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            mat[i][j] = rand() % 100;
        }
    }
}

//Функция для печати матрицы на экран
void print(int mat[N][N]) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << setw(5) << mat[i][j];
        }
        cout << endl;
    }
}

//функция для нахождения суммы в заданной строке в заштрихованной зоне
int summ(int mat[N][N], int row) {
    int sum = 0;
    for(int j = 0; j < N; ++j) {
        //левый треугольник
        if(row >= j && row <=N - 1 - j) {
            sum += mat[row][j];
        }

        //правый треугольник
        if(row <= j && row >= N - 1 - j) {
            sum += mat[row][j];
        }
    }
    return sum;
}


int main() {
    setlocale(LC_ALL, "Rus");
    time_t t;
    srand(time(&t));
    
    int matrix[N][N];

    char c = 'n';
    do {
        fillmatrix(matrix);
        cout << "Матрица: " << endl;
        print(matrix);

        int row;
        cout << "Введите строку [1-" << N << "]: ";
        cin >> row;
        int sum = summ(matrix, row-1); //находим сумму для строки заданной пользователем
        cout << "Сумма для заданной строки: " << sum << endl;

        //находим суммы для остальных строк
        for(int i = 0; i < N; ++i) {
            int tmp = summ(matrix, i);
            cout << "Сумма для " << i+1 << "-ой строки: " << tmp << endl;
        }

        cout << "Хотите продолжить выполнение? (y/n): ";
        cin >> c;
        cout << endl;
    } while(c != 'n');
    return 0;
}