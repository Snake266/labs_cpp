#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int* length_of_every_word(char* str) {
    int size = 5;
    int* len = (int*)malloc(sizeof(int) * size);
    
    return len;
}

void first_task() {

}

void second_task() {

}

int main() {
    setlocale(LC_ALL, "Rus");
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