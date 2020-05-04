#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

using namespace std;

#define N 10 //Размер матрицы для заданий

void fillmatrix(int (*matrix)[N]) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 100 - 50;
        }
    }
}

void print(int (*matrix)[N]) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << setw(4) << matrix[i][j];
        }
        cout << endl;
    }
}

double* average_by_column(int (*matrix)[N]) {
    static double average[N];
    for(int i = 0; i < N; ++i) average[i] = 0;

    for(int j = 0; j < N; ++j) {
        int count = 0, sum = 0;
        for(int i = 0; i < N; ++i) {
            count++;
            sum += matrix[i][j];
        }
        average[j] = (double)sum / count;
    }

    return average;
}

void first() {
    int matrix[N][N];
    fillmatrix(matrix);
    cout << "Матрица: " << endl;
    print(matrix);
    
    double* average = average_by_column(matrix);

    for(int i = 0; i < N; ++i)
        cout << "Среднее арифметическое для " << i+1 << "-го столбца: " << average[i] << endl;


}


void minimax(int (*matrix)[N], int* min, int* max) {
    *min = abs(matrix[0][0]);
    *max = abs(matrix[0][0]);
    for(int i = 0; i < N; ++i) {
        for(int j = i; j < N; ++j) {
            if(*min > abs(matrix[i][j])) *min = abs(matrix[i][j]);
            
            if(*max < abs(matrix[i][j])) *max = abs(matrix[i][j]);
        }
    }
}


void second() {
    int matrix[N][N];
    fillmatrix(matrix);
    cout << "Матрица:" << endl;
    print(matrix);

    int min = 0, max = 0;
    minimax(matrix, &min, &max);

    cout << "Минимум для заштрихованной зоны: " << min << endl;
    cout << "Максимум для заштрихованной зоны: " << max << endl;
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    char v = '0';
    do {
        cout << "Введите номер задания:\n1. Первое задание\n2. Второе задание\n0. Выход\n";
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
            cout << "Неправильный номер" << endl;
            break;
        }
        cout << endl;
    } while(v != '0');
    return 0;
}