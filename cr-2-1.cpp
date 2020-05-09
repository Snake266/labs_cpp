#include <iostream>
#include <iomanip>

using namespace std;

void initarray(int* arr, int size) {
    for(int i = 0; i < size; ++i) {
        arr[i] = rand() % 100;
    }
}

void print(int* arr, int size) {
    for(int i = 0; i < size; ++i) {
        cout << setw(4) << arr[i];
    }
    cout << endl;
}

int f(int* arr, int size, int A, int B) {
    int sum = 0;
    for(int i = 0; i < size; ++i) {
        if(arr[i] >= A && arr[i] <= B) {
            sum += arr[i];
        }
    }

    return sum;
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    int N1, N2;
    cout << "Введите размерность массива A: ";
    cin >> N1;
    cout << "Введите размерность массива B: ";
    cin >> N2;
    
    int* ar1 = new int[N1];
    int* ar2 = new int[N2];

    initarray(ar1, N1);
    initarray(ar2, N2);

    cout << "Массив A: ";
    print(ar1, N1);
    cout << "Массив B: ";
    print(ar2, N2);

    int A, B;
    cout << "Введите левую границу: ";
    cin >> A;
    cout << "Введите правую границу: ";
    cin >> B;

    if(A > B) {
        int tmp = A;
        A = B;
        B = tmp;
    }

    cout << "Сумма заданного промежутка в массиве A: " << f(ar1 + N1/2, N1/2, A, B) << endl;
    cout << "Сумма заданного промежутка в массиве B: " << f(ar2, N2/3, A, B) << endl;
    return 0;
}