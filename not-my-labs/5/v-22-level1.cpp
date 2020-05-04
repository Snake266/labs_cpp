#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

using namespace std;

void first() {

}


double** new_matrix(int N, int M) {
    double** matr = (double**)malloc(sizeof(double*) * N);
    for(int i = 0; i < N; ++i) {
        matr[i] = (double*)malloc(sizeof(double) * M);
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            matr[i][j] = (double)(rand())/RAND_MAX * 100;
        }
    }
    return matr;
}

void delete_matrix(double** matrix, int N, int M) {
    for(int i = 0; i < N; ++i) 
        free(matrix[i]);
    
    free(matrix);
}

double sum_of_zone(double** matrix, int N, int M) {
    double sum = 0;
    for(int j = 1; j < M; j += 2) {
        for(int i = 0; i <= j; ++i) {
            sum += matrix[i][j];
        }
    }

    return sum;
}

void second() {
    //Получаем размеры матрицы
    int N, M;
    cout << "Введите кол-во строк матрицы: ";
    cin >> N;
    cout << "Введите кол-во столбцов в матрице: ";
    cin >> M;
    //Создаем матрицу
    double** matrix = new_matrix(N, M);
    

}

int main() { 
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    char choice = '0';
    do {
        cout << "1. Первое задание\n2. Второе задание\n0. Выход\n(1/2/0): ";
        cin >> choice;
        cout << endl;
        switch (choice)
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
            cout << "Вы ввели неправильный номер" << std::endl;
            break;
        }

        cout << endl;
    } while(choice != '0');
    return 0;
}