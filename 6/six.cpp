#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstring>

#define sep_len 40

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


//Функция, которая добавляет в конец коллекции новую поссылку
void new_parcel(std::vector<parcel_t*>*);

//Печатаем таблицу
void print_parcel(parcel_t p);

void print_table(std::vector<parcel_t*>& p);

//ищем поссылку по фамилии и имени отправителя
void find_by_sender(std::vector<parcel_t*>&);

void find_by_weight(std::vector<parcel_t*>&);

int main() {
    setlocale(LC_ALL, "Russian");
    //Будем использовать std::vector, чтобы не писать свой std::vector
    //вектор аллоцирует данные в динамической памяти, поэтому все по требованиям
    std::vector<parcel_t*> parcels; 
        char choice = '0';
    do {
        std::cout << "Что вы хотите сделать?" << std::endl;
        std::cout << "1. Добавить новую поссылку?\n2. Распечатать все посслыки\n" 
                  << "3. Найти все поссылки по их отправителю\n4. Найти поссылки больше заданного веса\n" 
                  << "0. Выйти\n(1/2/3/4/0): ";
        std::cin >> choice;
        std::cout << std::endl;
        switch (choice)
        {
        case '1':
            new_parcel(&parcels);
            break;
        case '2':
            print_table(parcels);
            break;
        case '3':
            find_by_sender(parcels);
            break;
        case '4':
            find_by_weight(parcels);
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


//Пишет message и вводит в переменную dest
//ради простоты можно условитс что строки не длиннее 80 символов 
char* promt(const char* message) {
    char buf[80];
    std::cout << message;
    std::cin.getline(buf, 80);
    char* dest = new char[strlen(buf) + 1];
    strcpy(dest, buf);
    return dest;
}

void new_parcel(std::vector<parcel_t*>* p) {
    std::cout << std::endl;
    for(int i = 0; i < sep_len; ++i) {
        std::cout << '-';
    }
    std::cout << std::endl;
    std::cout << "Добавление новой поссылки" << std::endl;

    //Аллоцируем память под наши параметры
    char *s_last_name, *s_first_name, *s_adress,
        *r_last_name, *r_first_name, *r_adress;
    double weight;

    std::cin.ignore(INT8_MAX, '\n');
    //Вводим данные
    s_last_name = promt("Введите фамилию отправителя: ");
    s_first_name = promt("Введите имя отправителя: ");
    s_adress = promt("Введите адрес отправителя: ");

    r_last_name = promt("Введите фамилию получателя: ");
    r_first_name = promt("Введите имя получателя: ");
    r_adress = promt("Введите адрес получателя: ");
    

    std::cout << "Введите вес посылки: ";
    std::cin >> weight;
    
    //Добавляем в конец массива объект
    p->push_back(new parcel_t(s_last_name, s_first_name, s_adress, 
                        r_last_name, r_first_name, r_adress, weight));

    //Чистим память
    delete[] s_last_name; 
    delete[] s_first_name; 
    delete[] s_adress;
    delete[] r_last_name;
    delete[] r_first_name;
    delete[] r_adress;
    
    for(int i = 0; i < sep_len; ++i) {
        std::cout << '-';
    }
    std::cout << std::endl;
}

void print_parcel(parcel_t* p) {
    for(int i = 0; i < sep_len; ++i) std::cout << '-';
    std::cout << std::endl;
    std::cout << "Фамилия отправителя: " << p->s_last_name  << std::endl;
    std::cout << "Имя отправителя    : " << p->s_first_name << std::endl;
    std::cout << "Адрес отправителя  : " << p->s_adress     << std::endl;
    std::cout << "Фамилия получутеля : " << p->r_last_name  << std::endl;
    std::cout << "Имя получателя     : " << p->r_first_name << std::endl;
    std::cout << "Адрес получателя   : " << p->r_adress     << std::endl;
    std::cout << "Вес поссылки       : " << p->weight       << std::endl;
    
    for(int i = 0; i < sep_len; ++i) std::cout << '-';
    std::cout << std::endl;
}

void print_table(std::vector<parcel_t*>& p) {
    if(p.size() == 0) std::cout << "Поссылок нет" << std::endl;
    else {
        for(int i = 0; i < sep_len; ++i) {
            std::cout << '-';
        }
        std::cout << std::endl;

        for(int i = 0; i < p.size(); ++i) {
            print_parcel(p[i]);
        }
    }
}

void find_by_sender(std::vector<parcel_t*>& p) {
    for(int i = 0; i < sep_len; ++i) std::cout << '-';
    std::cout << std::endl;

    char sender_fname[80], sender_lname[80];
    std::cin.ignore(INT8_MAX, '\n');
    std::cout << "Введите фамилию отправителя: ";
    std::cin.getline(sender_lname, 80);
    std::cout << "Введите имя отправителя: ";
    std::cin.getline(sender_fname, 80);
    
    //Проходим по всему массиву
    for(auto& i : p) {
        if(!strncmp(i->s_first_name, sender_fname, strlen(i->s_first_name)) 
           && !strncmp(i->s_last_name, sender_lname, strlen(i->s_last_name))) {
            print_parcel(i);
        }
    }
    for(int i = 0; i < sep_len; ++i) std::cout << '-';
    std::cout << std::endl;
}

void find_by_weight(std::vector<parcel_t*>& p) {
    for(int i = 0; i < sep_len; ++i) std::cout << '-';
    std::cout << std::endl;
    double w;
    std::cout << "Введите вес поссылки: ";
    std::cin >> w;

    std::vector<parcel_t*> tmp;
    
    for(auto i : p) {
        if(i->weight > w) tmp.push_back(i);
    }

    std::sort(tmp.begin(), tmp.end(), [](parcel_t* a1, parcel_t* a2) {
        //Создадим временные строки, которые мы будем дальше сравнивать
        char* tmp1 = new char[strlen(a1->s_last_name) + strlen(a1->s_first_name) + 2];
        char* tmp2 = new char[strlen(a2->s_last_name) + strlen(a2->s_first_name) + 2];
        
        strcpy(tmp1, a1->s_last_name);
        strcat(tmp1, a1->s_first_name);

        strcpy(tmp2, a2->s_last_name);
        strcat(tmp2, a2->s_first_name);

        if(strcmp(tmp1, tmp2) < 0) {
            delete[] tmp1;
            delete[] tmp2;
            return true;
        }
        else{
            delete[] tmp1;
            delete[] tmp2;
            return false;
        } 
    });

    print_table(tmp);

}