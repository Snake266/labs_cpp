#include <iostream>
#include <iomanip>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

#define N 12 //Размер матрицы

void fillmatr(int mat[N][N]) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            mat[i][j] = rand() % 100 - 50;
        }
    }
}

void print(int mat[N][N]) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << setw(5) << mat[i][j];
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    time_t t;
    srand(time(&t));

    int matr[N][N];

    char c = 'n';
    do {
        fillmatr(matr);
        cout << "Матрица: " << endl;
        print(matr);

        //Находим максимум по модулю
        int max = abs(matr[0][0]);
        for(int i = 0; i < N; ++i) {
            for(int j = i; j < N; ++j) {
                if(max < abs(matr[i][j])) max = abs(matr[i][j]);
            }
        }

        //Считаем среднеее арифметическое для заштрихованной зоны, по столбцам
        double average[N];
        for(int i = 0; i < N; ++i) {
            average[i] = 0;
        }
        
        for(int j = 0; j < N; ++j) {
            int count = 0, sum = 0;
            for(int i = 0; i <= j; ++i) {
                count++;
                sum += matr[i][j];
            }
            average[j] = (double) sum / count;
        }
        
        for(int i = 0; i < N; ++i) {
            cout << "Среднее арифметическое " << i+1 << "-го столбца: " << average[i] << endl;
        }

        printf("Хотите повторить задание? (y/n): ");
        scanf("%c", &c);
        printf("\n");
    } while(c != 'n');
    return 0;
}