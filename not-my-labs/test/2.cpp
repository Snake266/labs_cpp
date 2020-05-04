#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#define N 10

//Функция для поиска минимума и максимума
void min_and_max(int* arr, int* min, int* max) {
    *min = arr[0];
    *max = arr[0];
    for(int i = 0; i < N; ++i) {
        if(*min > arr[i]) {
            *min = arr[i];
        }
        if(*max < arr[i]) {
            *max = arr[i];
        }
    }
}

//функция для заполнения массива
void init_array(int* array) {
    for(int i = 0; i < N; ++i) {
        array[i] = rand() % 100;
    }
}

//Функция для печати массив
void print(int* array) {
    for(int i = 0; i < N; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Rus");
    int arr[N];
    init_array(arr); //заполняем массив
    printf("Массив:\n");
    print(arr); //Выводим массив на экран
    int min = 0, max = 0;
    min_and_max(arr, &min, &max); //минимум и максимум
    printf("Минимум: %d\nМаксимум: %d\n", min, max); //выводим минимум и максимум на экран
    system("pause");
    return 0;
}