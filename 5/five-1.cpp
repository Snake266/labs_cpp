#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

int* length_of_every_word(char* str, int* s) {
    int i = 0;
    *s = 0;
    while(str[i]) {
        if(str[i] == ' ') (*s)++;
        i++;
    }
    int* len = (int*)malloc(sizeof(int) * (++(*s)));
    
    i = 0;
    int ch = 0, a = 0;
    while(str[i]) {
        if(str[i] != ' ') a++;
        if((str[i+1] == ' ' || str[i+1] == '\0') && str[i] != ' ') {
            len[ch++] = a;
            a = 0;
        }
        
        i++;
    }
    return len;
}

void print_array(char** arr, int count) {
    for(int i = 0; i < count; ++i) {
        std::cout  << arr[i]  << " ";
    }
    std::cout << std::endl;
}

//сортировать массив проще
char** string_to_array(char* str, int count) {
    char** array = (char**)malloc(sizeof(char) * count);
    char* tmp = (char*)malloc(strlen(str) + 1);
    strcpy(tmp, str);
    char* tok = strtok(tmp, " ");
    int i = 0;
    while(tok) {
        array[i] = (char*) malloc(strlen(tok) + 1);
        strcpy(array[i], tok);
        tok = strtok(NULL, " ");
        i++;
    }
    return array;
}


int comparator1(const void* a, const void* b) {
    int la = strlen((const char*)a);
    int lb = strlen((const char*)b);
    return (la > lb) - (la < lb);
}

int comparator2(const void* a, const void* b) {
    int la = strlen((const char*)a);
    int lb = strlen((const char*)b);
    return (la < lb) - (la > lb);
}

void bubbleSort1(char** array, int count) {
    for(int i = 1; i < count; ++i) {
        for(int j = 0; j < count - i; ++j) {
            if(strlen(array[j]) > strlen(array[j+1])) {
                char tmp[80];
                strcpy(tmp, array[j]);
                strcpy(array[j], array[j+1]);
                strcpy(array[j+1], tmp);
            }
        }
    }
}

void bubbleSort2(char** array, int count) {
    for(int i = 1; i < count; ++i) {
        for(int j = 0; j < count - i; ++j) {
            if(strlen(array[j]) < strlen(array[j+1])) {
                char tmp[80];
                strcpy(tmp, array[j]);
                strcpy(array[j], array[j+1]);
                strcpy(array[j+1], tmp);
            }
        }
    }
}

void first_task() {
    std::cout << "Первое задание" << std::endl;
    char** text = (char**)malloc(sizeof(char*) * 2);
    
    std::cin.ignore(INT8_MAX, '\n');
    for(int i = 0; i < 2; ++i) {
        std::cout << "Введите строку: ";
        char buf[80];
        std::cin.getline(buf, 80);
        text[i] = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
        strcpy(text[i], buf);

    }

    int* lens[2];
    int size[2];
    for(int i = 0; i < 2; ++i) {
        lens[i] = length_of_every_word(text[i], &size[i]);
    }
    char** array = string_to_array(text[0], size[0]);
    
    bubbleSort1(array, size[0]);
    print_array(array, size[0]);

    for(int i = 0; i < size[0]; ++i) {
        free(array[i]);
    }
    free(array);


    array = string_to_array(text[1], size[1]);
    bubbleSort2(array, size[1]);
    print_array(array, size[1]);
    std::cout << std::endl;
    for(int i = 0; i < size[0]; ++i) {
        free(array[i]);
    }
    free(array);

    free(text);
}

int main() {
    setlocale(LC_ALL, "Rus");
    char choice = '0';
    do {
        std::cout << "1. First task\n0. Exit\n(1/0): ";
        std::cin >> choice;
        std::cout << std::endl;
        switch (choice)
        {
        case '1':
            first_task();
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