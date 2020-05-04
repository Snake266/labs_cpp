#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

using namespace std;

#define N1 10 //размер первого массива
#define N2 20 //размер второго массива


//Функция для заполнения массив вещественными числами
void fillmas(double* mas, int size) {
    for(int i = 0; i < size; ++i) {
        mas[i] = (double)rand() / RAND_MAX * 100;
    }
}

//Функция для печати массива на экран
void print(double* mas, int size) {
    for(int i = 0; i < size; ++i) {
        cout << setw(5) << mas[i];
    }
    cout << endl;
}

//функция которая возвращает индекс максимального элемента в массиве 
int index_of_max(double* mas, int size) {
    double max = mas[0];
    int index = 0;
    for(int i = 0; i < size; ++i) {
        if(max < mas[i]) {
            max = mas[i];
            index = i;
        }
    }
    return index;
}

int main() {
    setlocale(LC_ALL, "Rus");
    time_t t;
    srand(time(&t));

    double A[N1], B[N2];
    
    char c = 'n';
    do {
        fillmas(A, N1); //заполняем массивы числами
        fillmas(B, N2);
        cout << "Массив A: "; //печатаем массивы на экран
        print(A, N1);
        cout << "Массив B: ";
        print(B, N2);

        int index1 = index_of_max(A, N1); //находим индекс максимального элемента в первом массиве
        int index2 = index_of_max(B, N2); //находим индекс максимального элемента во втором массиве

        //sum1 - сумма для первого массива
        //sum2 - сумма для второго массива
        double sum1 = 0, sum2 = 0;
        
        //сумируем элементы, которые нахдодятся правее максимума
        for(int i = index1; i < N1; ++i) {
            sum1 += A[i];
        }

        for(int i = index2; i < N2; ++i) {
            sum2 += B[i];
        }

        //сравниваем суммы
        if(sum1 > sum2) {
            cout << "Сумма элементов второй половины в первом массиве больше" << endl;
        } else if (sum1 < sum2) {
            cout << "Сумма элементов второй половины во втором массиве больше" << endl;
        } else {
            cout << "Суммы вторых половин равны" << endl;
        }

        cout << "Хотите продолжить выполнение? (y/n): ";
        cin >> c;   
        cout << endl;     
    } while(c != 'n');
    return 0;
}