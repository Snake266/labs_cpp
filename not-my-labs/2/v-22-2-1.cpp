#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>

#define N 20 //размер массива 

//функция для заполнения массив числами
void fillmas(int* mas) {
    for(int i = 0; i < N; ++i) {
        mas[i] = rand() % 100;
    }
}

//функция для вывода массива на экран
void print(int X[N]) {
    for(int i = 0; i < N; ++i) {
        printf("%d ", X[i]);
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Rus");
    time_t t;
    srand(time(&t));
    int X[N];
    char c = 'n';
    do {
        fillmas(X);
        printf("Массив:\n");
        print(X);

        //sum1 - сумма четных чисел в первой половине
        //sum2 - сумма нечетных чисел во второй половине
        int sum1 = 0, sum2 = 0;

        //цикл по первой половине массива
        for(int i = 0; i < N/2; ++i) {
            if(X[i] % 2 == 0) sum1 += X[i];
        }

        //цикл по второй половине массива
        for(int i = N/2; i < N; ++i) {
            if(X[i] % 2 != 0) sum2 += X[i];
        }

        printf("Сумма четных элементов в первой половине массива: %d\n", sum1);
        printf("Сумма нечетных элементов во второй половине массива: %d\n", sum2);

        printf("Хотите повторить задание? (y/n): ");
        scanf("%c", &c);
        printf("\n");
    } while(c != 'n');

    return 0;
}