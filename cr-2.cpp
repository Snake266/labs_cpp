//Вариант 4

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int* new_array(int size) {
    int* array = new int[size];
    for(int i = 0; i < size; ++i) {
        array[i] = rand() % 100 - 50; 
    }
    return array;
}

void print_array(int* array, int size) {
    for(int i = 0; i < size; ++i) {
        std::cout << std::setw(4) << array[i];
    }
    std::cout << std::endl;
}

int f(int* array, int size) {
    int count = 0;
    for(int i = 0; i < size; ++i) {
        if(array[i] < 0) {
            array[i] = i;
            count++;
        }
    }

    return count;
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    int N1, N2;
    std::cout << "Введите размер первого массива: ";
    std::cin >> N1;
    std::cout << "Введите размер второго массива: ";
    std::cin >> N2;

    int* A = new_array(N1);
    int* B = new_array(N2);

    std::cout << "Массив A: ";
    print_array(A, N1);
    std::cout << "Массив B: ";
    print_array(B, N2);
    //Передаем указатель на вторую треть массива, дходим до последней трети, но не берем ее
    std::cout << "Кол-во отрицательных чисел во второй трети массива A: " << f(A + N1/3, N1/3) << std::endl;
    //ОТправляем указатель на половину массива. Размер тоже сокращаем до половины
    std::cout << "Кол-во отрицательных чисел во второй половине массива B: " << f(B + N2/2, N2/2) << std::endl;

    std::cout << "Изменненый массив A: ";
    print_array(A, N1);
    std::cout << "Измененный массив B: ";
    print_array(B, N2);

    delete[] A;
    delete[] B;

    system("pause");
    return 0;
}