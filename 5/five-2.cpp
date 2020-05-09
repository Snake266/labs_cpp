#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <locale.h>

//Функция, которая возвращает указатель на заполненую матрицу
int* initmatrix(int N, int M) {
    int* matr = (int*)malloc(N * M * sizeof(int));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            *(matr + i*N + j) = rand() % 100;
        }
    }
    return matr;
}

//Функция для печати матрицы на экран
void print(int* matrix, int N, int M) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            std::cout << std::setw(5) << *(matrix + i*N + j);
        }
        std::cout << std::endl;
    }
}


char** str_word_with_bletter(char* str, char sym) {
    int size = 1, ch = 0;
    char** strs = (char**)malloc(sizeof(char*) * size);

    for(int i = 0; i < strlen(str); ++i) {
        if(ch == size) {
            size++;
            strs = (char**)realloc(strs, sizeof(char*) * size);
        }

        if(str[i] == sym) {
            strs[ch] = &str[i];
            ch++;
        }
    }
    return strs;
}
        

    

//Функция, которая изменяет четные и нечетные строки
//В нечетных строках слова начинающиеся с заданного символа пишутся с заглавной буквы
//В четных строках слова начинающиеся с заданного символа удаляются из строки
void function(char** str, int count, char sym) {
    for(int i = 0; i < count; ++i) {
        if(i % 2 == 0) {
            int len = strlen(str[i]);
            
        } else {
            int j = 0;
            while(str[i][j]) {
                if(str[i][j] == sym && (j == 0 ||str[i][j-1] == ' ' )) {
                    str[i][j] = toupper(sym);
                }
                j++;
            }
        }
    }
}

//Функция для печати текста, выравнивая его по правому краю
void print_right_aligned(char* str, int width) {
    std::cout.width(width);
    std::cout << str << std::endl;
}

//Первое задание
void first_task() {
    std::cout << "изменить текст: в четных столбцах удалить слова начинающиеся с заданной буквы\n "
            << "в нечетных строках такие слова написать с заглавной буквы\n" 
            << "реализовать функцию для выравнивания текста по правому краю" << std::endl;
    
    
    int size = 10; //кол-во строк матрицы
    char** text = (char**)malloc(sizeof(char*) * size);//выделяем матрицу с 10 (size) строками
    int ch = 0; //индекс записи строки
    
    std::cin.ignore(INT32_MAX, '\n');
    while(true) {
        char buf[160]; //временный буффер
        
        std::cout << "Введите текст на латинице: ";
        std::cin.getline(buf, 160);
        
        if(!strncmp(buf, "end\0", strlen("end\0"))) { //если строка равна "end" тогда мы выходим из цикла
            break;
        }

        if(ch == size) { //если мы дошли до дна нашей матрицы
            size *= 2; //увеличиваем размер в два раза
            text = (char**)realloc(text, size); //и увеличиваем матрицу
        }
        
        text[ch] = (char*)malloc(sizeof(char) * strlen(buf)); //выделяем память для новой строчки
        strcpy(text[ch], buf); //копируем данные из буфера в нашу строчку
        
        ch++; //увеличиваем индекс на единицу
    }

    std::cout << "Введенные строки" << std::endl;
    for(int i = 0; i < ch; ++i) {
        std::cout << text[i] << std::endl;
    }
    
    char** s = str_word_with_bletter(text[0], 'a');
    for(int i = 0; s[i]; ++i) {
        std::cout << s[i] << std::endl;
    }
    /*
    

    //Находим самую длинную строку чтобы по ней вровнять в правый край
    int maxlen = strlen(text[0]);
    for(int i = 0; i < ch; ++i) {
        if(maxlen < strlen(text[i])) maxlen = strlen(text[i]);
    }
    
    //печатаем изменненый текст выровненый по правому краю
    for(int i = 0; i < ch; ++i) {
        print_right_aligned(text[i], maxlen);
    }

    for(int i = 0; i < ch; ++i) //очищаем строки матрицы
        free(text[i]);
    free(text); //чистим саму матрицу
    */
}


int* find_max_of_zones(int* matrix, int N, int M) {
    int* minimax = (int*)malloc(sizeof(int) * 2);
    minimax[0] = *matrix; //максимум слева
    minimax[1] = *matrix; //максимум справа

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {

            //обходим левый треугольник
            if(i >= j && i <= M - 1 - j) {
                if(minimax[0] < *(matrix + i*N + j)) {
                    minimax[0] = *(matrix + i*N + j);
                }
            }
            //обходим правый треугольник
            if(i <= j && i >= N - 1 - j) {
                if(minimax[1] < *(matrix + i*N + j)) {
                    minimax[1] = *(matrix + i*N + j);
                }
            }
            
        }
    }

    return minimax;
}

//Второе задание
void second_task() {
    std::cout << "Создать динмическую матрицу, размеры задать с  клавиатуры" << std::endl
            << "Написать функцию, которая юудет возвращать массив из двух максимумов" << std::endl
            << "заштрихованной зоны (по половинкам)" << std::endl;
    int N, M;
    
    std::cout << "Введите размер матрицы" << std::endl;
    std::cout << "Введите кол-во строк: ";
    std::cin >> N;
    std::cout << "Введите кол-во колонок: ";
    std::cin >> M;
    
    int* matrix = initmatrix(N, M);
    std::cout << "Матрица:" << std::endl;
    print(matrix, N, M);
    int* minimax = find_max_of_zones(matrix, N, M);

    std::cout << "Максимум левой заштрихованной зоны: " << minimax[0] << std::endl
            << "Максимум правой заштрихованной зоны: " << minimax[1] << std::endl;
    free(matrix);
    free(minimax);
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    char choice = '0';
    do {
        std::cout << "1. First task\n2. Second task\n0. Exit\n(1/2/0): ";
        std::cin >> choice;
        std::cout << std::endl;
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
