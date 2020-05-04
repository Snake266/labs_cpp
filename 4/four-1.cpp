#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <time.h>


#define N1 10
#define N2 15

#define N 10

//Функция-каркас для первого задания
void first_task(void);
//Функция-каркас для второго задания
void second_task(void);

//функции для инициализации массивов и матриц
void initarr(int*, int);
void initmatr(int(*)[N]);

//макрос для печати массива, потому что функция будет лишней сущностью, для двух строк
#define print_arr(var, size)\
for(int i = 0; i < size; ++i) printf("%d ", var[i]);\
printf("\n");

void print_matrix(int(*)[N]);


int main(int argc, char** argv) {
    srand(time(NULL));
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


////////////////////////////////////////////////////////////////////////////////////////////////////////
int* split_at_last_positive(int* arr, int size) {
    int* element = &arr[0];
    for(int i = size - 1; i >= 0; --i) {
        if (arr[i] > 0) {
            element = arr+i;
            break;
        }
    }
    return element;
}

int min(int* start, int* end) {
    int mini = *start;
    for (int* i = start; i < end; ++i) {
        if(*i < mini) mini = *i;
    }

    return mini;
}

void first_task(void) {
    int A[N1], B[N2];
    initarr(A, N1); //Инициализируем и печатаем массив A
    printf("Array A:\n");
    print_arr(A, N1);
    
    int* edge = split_at_last_positive(A, N1);
    int mini = min(edge, &A[N1-1]);
    printf("minimum of A(right direction from last postive): %d\n", mini);

    initarr(B, N2);//Инициализируем и печатаем массив B
    printf("Array B:\n");
    print_arr(B, N2);
    
    edge = split_at_last_positive(B, N2);
    mini = min(edge, &B[N2]);
    printf("minimum of B(right derection from last positive: %d\n", mini);

}

////////////////////////////////////////////////////////////////////////////////////////
//ищем минимум  в матрице, в заштрихованное зоне
int min_matrix(int mat[N][N]) {
    int min = mat[0][0];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if((j <= i && (i + j) <= N) || (j >= i && (i + j) >= N)) {
                if (mat[i][j] < min) min = mat[i][j];
            }
        }
    }
    return min;
}

//второе задание
void second_task(void) {
    int matrix[N][N];
    initmatr(matrix);
    
    print_matrix(matrix);

    printf("Minimum of matrix: %d\n", min_matrix(matrix));

}

//инициализируем массив
void initarr(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 80 - 40;
    }
}


//инициализируем матрицу
void initmatr(int (*mat)[N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mat[i][j] = rand() % 40 - 20;
        }
    }
}

//печатаем матрицу
void print_matrix(int (*mat)[N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << std::setw(8) << mat[i][j];
        }
        std::cout << std::endl;
    }
}
