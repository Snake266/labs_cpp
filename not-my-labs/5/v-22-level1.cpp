#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
using namespace std;

char *substring(char *string, int position, int length)
{
   int c;
 
   char* pointer = (char*)malloc(length+1);
 
   for( c = 0 ; c < length ; c++ )
      *(pointer+c) = *((string+position-1)+c);      
       
   *(pointer+c) = '\0';
 
   return pointer;
}

void insert_substring(char *a, char *b, int position)
{
   char *f, *e;
   int length;
   
   length = strlen(a);
   
   f = substring(a, 1, position - 1 );      
   e = substring(a, position, length-position+1);

   strcpy(a, "");
   strcat(a, f);
   free(f);
   strcat(a, b);
   strcat(a, e);
   free(e);
}

void sort_str(char* str) {
    // if (strcmp(words[i], words[j]) < 0)
    char* tmp = (char*)malloc(strlen(str));
    strcpy(tmp, str);
    int space = 0;
    for (int i = 0;i < strlen(str);i++) {
        if (str[i] == ' ') {
            space++;
        }
    }
    // a b c d e f
    char** p = (char**) malloc(space+1); 
    for (int i = 0, j = 0, k = 0; j < strlen(str); j++)
    {
        if (str[j] == ' ')  
        {    
            p[i][k] = '\0';
            i++;
            k = 0;
        }        
        else
             p[i][k++] = str[j];
    }
    for (int i = 0; i < space;i++)    //loop for sorting
    {
        for (int j = i + 1;j <= space;j++)
        {
            if ((strcmp(p[i], p[j]) > 0))
            {
                strcpy(cmp, p[i]);
                strcpy(p[i], p[j]);
                strcpy(p[j], cmp);
            }
        }
    }
}

void first() {
    char* text[2];
    cin.ignore(INT32_MAX, '\n');
    for(int i = 0; i < 2; ++i) {
        char buf[160];
        cout << "Введите текст на латинице: ";
        cin.getline(buf, 160);
        text[i] = (char*)malloc(strlen(buf));
        strcpy(text[i], buf);
    }
    sort_str(text[1]);
}


double** new_matrix(int N, int M) {
    double** matr = (double**)malloc(sizeof(double*) * N);
    for(int i = 0; i < N; ++i) {
        matr[i] = (double*)malloc(sizeof(double) * M);
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            matr[i][j] = (double)(rand())/RAND_MAX * 100;
        }
    }
    return matr;
}

void delete_matrix(double** matrix, int N, int M) {
    for(int i = 0; i < N; ++i) 
        free(matrix[i]);
    
    free(matrix);
}

double sum_of_zone(double** matrix, int N, int M) {
    double sum = 0;
    for(int j = 1; j < M; j += 2) {
        for(int i = 0; i <= j; ++i) {
            sum += matrix[i][j];
        }
    }

    return sum;
}

void second() {
    //Получаем размеры матрицы
    int N, M;
    cout << "Введите кол-во строк матрицы: ";
    cin >> N;
    cout << "Введите кол-во столбцов в матрице: ";
    cin >> M;
    //Создаем матрицу
    double** matrix = new_matrix(N, M);
    

}

int main() { 
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    char choice = '0';
    do {
        cout << "1. Первое задание\n2. Второе задание\n0. Выход\n(1/2/0): ";
        cin >> choice;
        cout << endl;
        switch (choice)
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
            cout << "Вы ввели неправильный номер" << std::endl;
            break;
        }

        cout << endl;
    } while(choice != '0');
    return 0;
}