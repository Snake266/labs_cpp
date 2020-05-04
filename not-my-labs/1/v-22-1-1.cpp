#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("Введите возраст: ");
    int k;
    scanf("%d", &k);
    if(k == 1) {
        printf("Мне %d год\n", k);
    } else if(k >= 5 && k <= 20) {
        printf("Мне %d лет\n", k);
    } else if(k % 10 == 0) {
        printf("Мне %d лет\n", k);
    } else if(k % 10 == 1) {
        printf("Мне %d год\n", k);
    } else if(k % 10 > 1 && k % 10 < 5) {
        printf("Мне %d года\n", k);
    } else if(k % 10 >= 5 && k % 10 <= 9) {
        printf("Мне %d лет\n", k);
    }
    system("pause");
    return 0;
}