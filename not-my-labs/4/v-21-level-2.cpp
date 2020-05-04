#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <time.h>

using namespace std;

#define N 10
#define M 12

//Заполняем матрицу числами
void initmatrix(int (*)[M]);

//Печатаем матрцу
void print_matrix(int (*)[M]);

void first();
void second();

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    char v = '0';
    do {
        cout << "Введите номер пункта:\n1. Первое задание\n2. Второе задание\n0. Выход\n";
        cin >> v;
        switch (v)
        {
        case '1':
            first();
            break;
        case '2':
            second();
            break;
        case '0': 
            break;
        default:
            cout << "wrong argument" << endl;
            break;
        }
        cout << endl;
    } while(v != '0');
    return 0;
}

//функция, которая возвращает массив с кол-ом нулей в четных столбцах
int* zeros(int (*matrix)[M], int* arr) {
    for(int i = 0; i < M/2; ++i) arr[i] = 0;
    int pos = 0;

    for(int j = 1; j < M; j += 2) {
        int count = 0;
        for(int i = 0; i < N; ++i) {
            if(matrix[i][j] == 0) arr[pos] = ++count;
        }
        pos++;
    }
    return arr;
}
void first() {
    int matrix[N][M];
    initmatrix(matrix);
    cout << "Матрица: " << endl;
    print_matrix(matrix);

    
    int arr[M/2];
    zeros(matrix, arr);
    cout << "Кол-во нулей в четных столбцах: ";
    for (int i = 0; i < M/2; i++) cout << arr[i] << " ";
    cout << endl;    
}
 
//Функция с помощью указателей возвращает минимум и максимум
void min_and_max(int (*matrix)[M], int* min, int* max) {
    for(int i = N/2; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            if(matrix[i][j] > *max) *max = matrix[i][j];
            if(matrix[i][j] < *min) *min = matrix[i][j];
        }
    }
}

void second () {
    int matrix[N][M];
    initmatrix(matrix);
    cout << "Матрица: " << endl;
    print_matrix(matrix);

    int min = matrix[0][0];
    int max = matrix[0][0];

    min_and_max(matrix, &min, &max);
    cout << "Минимум: " << min << endl
        << "Максимум: " << max << endl;
}

void initmatrix(int (*matrix)[M]) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            matrix[i][j] = rand() % 40 - 20;
        }
    }
}

void print_matrix(int (*matrix)[M]) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            cout << setw(4) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}