#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    printf("Введите диапозон: ");
    scanf("%d%d", &a, &b); //получаем диапозон

    //Если b окажется меньше a
    if(a > b) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    int ch = 0;

    printf("Введите 15 чисел\n");
    //цикл на 15 итераций
    for(int i = 0; i < 15; ++i) {
        int tmp;
        scanf("%d", &tmp); //складываем во временную переменную число
        if(tmp >= a && tmp <= b) ch++; //проверяем лежит ли число в заданном диапозоне
    }

    printf("Введено %d чисел, которые входят в диаозон [%d, %d]\n", ch, a, b);
    system("pause");
    return 0;
}