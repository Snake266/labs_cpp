#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");
    int n;
    printf("Введите колличество вершин: ");
    scanf("%d", &n); //Получаем n
    
    //Передаем n в свитч
    switch (n)
    {
    //описываем многоугольники
    case 3:
        printf("Треугольник\n");
        break;
    case 4:
        printf("Квадрат\n");
        break;
    case 5:
        printf("Пятиугольник\n");
        break;
    case 6:
        printf("Шестиугольник\n");
        break;
    case 7:
        printf("Семиугольник\n");
        break;
    case 8:
        printf("Восьмиугольник\n");
        break;

    //любые другие числа попадут в default
    default:
        printf("Неизвестная фигура\n");
        break;
    }
    system("pause");
    return 0;
}