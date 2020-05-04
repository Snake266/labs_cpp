#include <stdlib.h>
#include <stdio.h>

#define N 10 //Размер массива

//Функция для поиска минимума и максимума
void minimax(int* arr, int* min, int* max) {
    int local_min = arr[0]; //Задаем начальное значение минимума
    int local_max = arr[0]; //Задаем начальное значение максимума

    for(int i = 0; i < N; ++i) {
        if(local_min > arr[i]) local_min = arr[i]; //Если наш local_min больше элемента, то переназначаем local_min
        if(local_max < arr[i]) local_max = arr[i]; //Если наш local_max меньше элемента, то переназначаем local_max
    }

    //Пишем в указатели минимум и максимум
    *min = local_min; 
    *max = local_max;
}

void initarr(int* arr) {
    for(int i = 0; i < N; ++i) {
        arr[i] = rand() % 40 - 20; //Заполняем массив числами от -20 до 20
    }
}

//функция для печати массива на экран
void printarr(int* arr) {
    for(int i = 0; i < N; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[N];
    initarr(arr); //инициализируем массив
    printf("array:\n");
    printarr(arr); //Выводим массив на экран
    int min = 0, max = 0;
    minimax(arr, &min, &max); //Получаем минимум и максимум
    printf("Minimum: %d\nMaximum: %d\n", min, max); //выводим минимум и максимум на экран
    system("pause");
    return 0;
}