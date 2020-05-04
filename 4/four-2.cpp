#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

#define N 10

//инициализация матрицы
void initmatrix(int (*)[N]);

//печать матрицы
void print_matrix(int (*)[N]);

void first_task();
void second_task();

int main(int argc, char** argv) {
    srand(time(NULL));
    
    //меню выбора заданий
    char choice = '0';
    do {
        std::cout << "1. First task\n2. Second task\n0. Exit\n(1/2/0): ";
        std::cin >> choice;
        switch (choice)
        {
        case '1':
            first_task();
            break;
        case '2':
            second_task();
            break;
        case '0': 
            break;
        default:
            std::cout << "wrong argument" << std::endl;
            break;
        }

        std::cout << std::endl;
    } while(choice != '0');
    
    return 0;
}

void first_task() {
    int matrix[N][N]; //создаем, инициализируем печатаем
    initmatrix(matrix);
    std::cout << "Matrix:" << std::endl;
    print_matrix(matrix);

    //находим кол-во нулей в нечетных столбцах матрицы
    int zeros[N/2], pos = 0;
    for(int i = 0; i < N/2; ++i) zeros[i] = 0;
    for(int j = 0; j < N; j+= 2) {
        int c = 0;
        for(int i = 0; i < N; ++i) {
            if(matrix[i][j] == 0) zeros[pos] = ++c;
        }
        pos++;
    }

    std::cout << "zeros:\n";
    for(int i = 0; i < N/2; ++i) {
        std::cout << std::setw(2) << zeros[i];
    }
    std::cout << std::endl;
}

void second_task() {
    int matrix[N][N];//инициализируем, печатаем 
    initmatrix(matrix);
    std::cout << "matrix:" << std::endl;
    print_matrix(matrix);

    //находим минимум в левой треугольнике
    int min = matrix[0][0];
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j) {
            if(j <= i && (i + j) <= N) {
                if (min > matrix[i][j]) min = matrix[i][j];
            }
        }
    }

    //находим максимум в правом прямоугольнике
    int max = matrix[0][N-1];
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j) {
             if(j >= i && (i + j) >= N) {
                if (max < matrix[i][j]) max = matrix[i][j];
            }
        }
    }

    //Выводим на экран мимнимум и максимум
    std::cout << "Minimum of left side: " << min << std::endl;
    std::cout << "Maximum of right side: " << max << std::endl;
}

void initmatrix(int (*mat)[N]) {
    for (int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            mat[i][j] = rand() % 20 - 10;
        }
    }
}

void print_matrix(int (*matrix)[N]) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            std::cout << std::setw(8) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}