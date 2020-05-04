#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

using namespace std;

#define N1 5
#define N2 10

#define N 6
#define M 9

//Функция для заполнения массива числами
void initarray(int*, int);

//Функция для заполнения матрицы числами
void initmatrix(int (*)[M]);

//Печатаем матрицу
void print_matrix(int(*)[M]);

//печатаем массив
void print_array(int*, int);

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

//Возвращаем указатель на последний положительный элемент
int* last_positive(int* array, int size) {
    int* number = &array[0];
    for(int i = size - 1; i >= 0; --i) {
        if (array[i] > 0) {
            number = array+i;
            break;
        }
    }
    return number;
}

//Находим минимум от начала массива до заданного конца
int minimum(int* array, int* end) {
    int mini = array[0];
    for (int* i = array; i < end; ++i) {
        if(*i < mini) mini = *i;
    }

    return mini;
}

void first() {
    int A[N1], B[N2]; //создаем, заполняем и печатаем массивы
    initarray(A, N1);
    cout << "Массив A: ";
    print_array(A, N1);
    initarray(B, N2);
    cout << endl << "Массив B: ";
    print_array(B, N2);
    cout << endl;

    int *number, min1, min2;
    number = last_positive(A, N1);//Находим позицую последнего положительно элемента в первом массиве
    min1 = minimum(A, number); //минимум первого массива

    number = last_positive(B, N2); //Находим позицию последного положительного элемента во втором массиве
    min2 = minimum(B, number); //минимум второго массива

    cout << "Минимум первого массива: " << min1 << endl 
        << "Минимум второго массива: " << min2 << endl;
}

//Находим сумму заштрихованной зоны
int fsum(int (*matrix)[M]) {
    int sum = 0;
    for(int i = N/2; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

void second() {
    int matrix[N][M];//Создаем, заполняем, печатаем матрицу
    initmatrix(matrix);
    cout << "Матрица: " << endl;
    print_matrix(matrix);

    
    int sum = fsum(matrix);
    cout << "Сумма заштрихованной области: " << sum << endl; 
}

void initarray(int* array, int size) {
    for(int i = 0; i < size; ++i) {
        array[i] = rand() % 40 - 20;
    }
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

void print_array(int* array, int size) {
    for(int i = 0; i < size; ++i) {
        cout << setw(4) << array[i];
    }
}