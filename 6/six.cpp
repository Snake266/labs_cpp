#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

//Копирует строку и возвращает указатель новую строку
char* alloc_and_copy(char* str) {
    char* res = new char[strlen(str)];
    if(!res) throw std::exception();
    std::strncpy(res, str, std::strlen(str));
    return res;
}

//структура поссылки
struct parcel_t {
    //Можно было бы и std::string, но это, скорее всего, посчитают читом

    char* s_last_name; // Фамилия отправителя
    char* s_first_name; // Имя отправителя
    char* s_adress; // Адрес отправителя
    
    char* r_last_name; // Фамилия получателя
    char* r_first_name; // Имя получателя
    char* r_adress; // Адрес получателя

    double weight; //Вес поссылки

    
    //Конструктор 
    parcel_t(char* s_ln, char* s_fn, char* s_a, char* r_ln, char* r_fn, char* r_a, double w) {
        s_last_name = alloc_and_copy(s_ln);
        s_first_name = alloc_and_copy(s_fn);
        s_adress = alloc_and_copy(s_a);
        
        r_last_name = alloc_and_copy(r_ln);
        r_first_name = alloc_and_copy(r_fn);
        r_adress = alloc_and_copy(r_a);
        weight = w;
        
        
    }


    ~parcel_t() {
        //Так как мы все строки копируем, double free не будет, значит все классно
        delete[] s_last_name;
        delete[] s_first_name;
        delete[] s_adress;

        delete[] r_last_name;
        delete[] r_first_name;
        delete[] r_adress;
    }

};

//Пишет message и вводит в переменную dest
//ради простоты можно условитс что строки не длиннее 160 символов 
void promt(const char* message, char* dest);

//Функция, которая добавляет в конец коллекции новую поссылку
void new_parcel(std::vector<parcel_t*>*);

//Печатаем таблицу
void print_table(std::vector<parcel_t*>);

//ищем поссылку по фамилии и имени отправителя
void find_by_sender(char* full_name, std::vector<parcel_t*>);

int main() {
    setlocale(LC_ALL, "Russian");
    //Будем использовать std::vector, чтобы не писать свой std::vector
    //вектор аллоцирует данные в динамической памяти, поэтому все по требованиям
    std::vector<parcel_t*> parcels; 
    new_parcel(&parcels);
    new_parcel(&parcels);
    print_table(parcels);
    return 0;
}

void promt(const char* message, char* dest) {
    std::cout << message;
    std::cin.getline(dest, 160);
}

void new_parcel(std::vector<parcel_t*>* p) {
    std::cout << std::endl;
    for(int i = 0; i < 30; ++i) {
        std::cout << '-';
    }
    std::cout << std::endl;
    std::cout << "Добавление новой поссылки" << std::endl;

    //Аллоцируем память под наши параметры
    char *s_last_name = new char[160], *s_first_name = new char[160], *s_adress = new char[160],
        *r_last_name = new char[160], *r_first_name = new char[160], *r_adress = new char[160];
    double weight;

    std::cin.ignore(INT8_MAX, '\n');
    //Вводим данные
    promt("Введите фамилию отправителя: ", s_last_name);
    promt("Введите имя отправителя: ", s_first_name);
    promt("Введите адрес отправителя: ", s_adress);

    promt("Введите фамилию получателя: ", r_last_name);
    promt("Введите имя получателя: ", r_first_name);
    promt("Введите адрес получателя: ", r_adress);
    

    std::cout << "Введите вес посылки: ";
    std::cin >> weight;
    
    //Добавляем в конец массива объект
    p->push_back(new parcel_t(s_last_name, s_first_name, s_adress, 
                        r_last_name, r_first_name, r_adress, weight));

    //Чистим память
    delete[] s_last_name; delete[] s_first_name; delete[] s_adress;
    delete[] r_last_name; delete[] r_first_name; delete[] r_adress;
    
    for(int i = 0; i < 30; ++i) {
        std::cout << '-';
    }
    std::cout << std::endl;
}


void print_table(std::vector<parcel_t*> p) {
    std::cout << "not implemented" << std::endl;
}

void find_by_sender(char* sender, std::vector<parcel_t*> p) {
    for(auto i : p) {
    }
}