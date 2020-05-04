#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

using namespace std;

#define N1 12
#define N2 15

//Функция, которая заполняет массив цифрами
void initarray(int* array, int size) {
    for(int i = 0; i < size; ++i) {
        array[i] = rand() % 40 - 20;
    }
}

//Функция для печати массива
void print_array(int* array, int size) {
    for(int i = 0; i < size; ++i) {
        cout << setw(4) << array[i];
    }
    
}

//Функция, которая возвращает индекс последнего положительного элемента
int last_positive(int* array, int size) {
    int index = 0;
    for(int i = size-1; i >= 0; --i) {
        if(array[i] > 0) {
            index = i;
            break;
        }
    }
    return index;
}

//ищет минмум от начала массива до заданного индекса
int mmin(int* arr, int index) {
    int mini = arr[0];
    for(int i = 0; i < index; ++i) {
        if(arr[i] < mini) mini = arr[i];
    }
    return mini;
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    int A[N1], B[N2];
    initarray(A, N1);
    initarray(B, N2);
    
    cout << "Массив A: ";
    print_array(A, N1);
    cout << endl;
    cout << "Массив B: ";
    print_array(B, N2);
    cout << endl;

    int index = last_positive(A, N1);
    int minA = mmin(A, index);
    index = last_positive(B, N2);
    int minB = mmin(B, index);

    cout << "Минимум массива A: " << minA << endl
        << "Минимум массива B: " << minB << endl;

    system("pause");
    return 0;
}