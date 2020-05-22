#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <forward_list>
#include <iterator>
#include <cstring>

#define sep_len 40

#define DEBUG

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
        
        #ifdef DEBUG
        std::cout << "destructor" << std::endl;
        #endif
    }

};


//Функция, которая добавляет в конец коллекции новую поссылку
void new_parcel(std::forward_list<parcel_t*>*);

//Печатаем таблицу
void print_parcel(parcel_t p);

void print_table(std::forward_list<parcel_t*>& p);

//ищет поссылку по фамилии и имени отправителя
void find_by_sender(std::forward_list<parcel_t*>&);

//ищет поссылку с весом больше заданного
void find_by_weight(std::forward_list<parcel_t*>&);

//вставляет поссылку в конец списка
void add(std::forward_list<parcel_t*>&, parcel_t*);

//находит и удаляет поссылки с весом меньше заданного
void find_and_delete(std::forward_list<parcel_t*>&);

//Сортирует список по фамилии отправителя
void sort_by_last_name(std::forward_list<parcel_t*>&);

//Сохраняет поссылку в формате
//s_last_name|s_first_name|s_adress|r_last_name|r_first_name|r_adress|weight
void save_list(std::forward_list<parcel_t*>&);

//Вытаскивает данные из файла, написанного в вышеизложенном формате
void load_list(std::forward_list<parcel_t*>&);

int main() {
    setlocale(LC_ALL, "Russian");
    //Будем использовать std::vector, чтобы не писать свой std::vector
    //вектор аллоцирует данные в динамической памяти, поэтому все по требованиям
    std::forward_list<parcel_t*> parcels; 
    load_list(parcels);
    char choice = '0';
    do {
        std::cout << "Что вы хотите сделать?" << std::endl;
        std::cout << "1. Добавить новую поссылку?\n2. Распечатать все посслыки\n" 
                  << "3. Найти все поссылки по их отправителю\n4. Найти поссылки больше заданного веса\n" 
                  << "5. Удалить поссылки нижу заданного веса\n6. Сортировать список поссылок по фамилии отправителя\n"
                  << "0. Выйти и сохранить данные\n(1/2/3/4/0): ";
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
        case '5':
            find_and_delete(parcels);
            break;
        case '6':
            sort_by_last_name(parcels);
            break;
        case '0':
            save_list(parcels);
            break;
        default:
            std::cout << "wrong argument" << std::endl;
            break;
        }
        std::cout << std::endl;
    } while(choice != '0');
    return 0;
}


void add(std::forward_list<parcel_t*>& list, parcel_t* p) {
    auto before_end = list.before_begin();
    for(auto& _ : list)
        before_end++;
    
    list.insert_after(before_end, p);
}

//Пишет message и возвращает введенную строку
char* promt(const char* message) {
    char buf[80];
    std::cout << message;
    std::cin.getline(buf, 80);
    char* dest = new char[strlen(buf) + 1];
    strcpy(dest, buf);
    return dest;
}

void new_parcel(std::forward_list<parcel_t*>* p) {
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
    
    //Добавляем в конец списка объект
    add(*p, new parcel_t(s_last_name, s_first_name, s_adress, 
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

void print_table(std::forward_list<parcel_t*>& p) {
    if(p.empty()) std::cout << "Поссылок нет" << std::endl;
    else {
        for(int i = 0; i < sep_len; ++i) {
            std::cout << '-';
        }
        std::cout << std::endl;
        for(auto& i : p) {
            print_parcel(i);
        }
    }
}

void find_by_sender(std::forward_list<parcel_t*>& p) {
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

void find_by_weight(std::forward_list<parcel_t*>& p) {

    for(int i = 0; i < sep_len; ++i) std::cout << '-';
    std::cout << std::endl;
    double w;
    std::cout << "Введите вес поссылки: ";
    std::cin >> w;

    std::forward_list<parcel_t*> tmp;
    
    for(auto i : p) {
        if(i->weight > w) add(tmp, i);
    }

    print_table(tmp);
}

void find_and_delete(std::forward_list<parcel_t*>& p) {
    double w;
    std::cout << "Введите вес поссылки: ";
    std::cin >> w;
    
    //проверяем корректны ли данные, если нет то просим пользователя повторить ввод
    while(!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(INT8_MAX, '\n');
        std::cout << "Неправильный ввод, попробуйте снова." << std::endl;
        std::cout << "Введите вес поссылки: ";
        std::cin >> w;
    }

    p.remove_if([w](parcel_t* a) {
        return a->weight < w;
    });

}

void sort_by_last_name(std::forward_list<parcel_t*>& p) {
    p.sort([](parcel_t* a1, parcel_t* a2) {
        if(strcmp(a1->s_last_name, a2->s_last_name) < 0) {
            return true;
        } else {
            return false;
        }
    });
}

void save_list(std::forward_list<parcel_t*>& p) {
    FILE* f = fopen("db.txt", "w");
    if(!f) {
     std::cout << "Не удается создать/открыть файл!" << std::endl;
     return;
    }
    rewind(f);
    for(auto i : p) {
        fprintf(f, "%s|", i->s_last_name);
        fprintf(f, "%s|", i->s_first_name);
        fprintf(f, "%s|", i->s_adress);
        fprintf(f, "%s|", i->r_last_name);
        fprintf(f, "%s|", i->r_first_name);
        fprintf(f, "%s|", i->r_adress);
        fprintf(f, "%lf\n", i->weight);
    }
    fclose(f);
}

void load_list(std::forward_list<parcel_t*>& p) {
    FILE* tmpfile = fopen("db.txt", "a");// нужно для того чтобы создать файл если его нет
    fclose(tmpfile);
    
    FILE* f = fopen("db.txt", "r");

    fseek(f, 0, SEEK_END); //Переносим "курсор" в начало файла
    if(ftell(f) == 0) {
        std::cout << "База данных пуста" << std::endl;
        return;
    }
    
    char buf[500]; //тут лучше на буфере не жалеть, т.к формат сохранения будет таков:
    // "Фамилия_отправителя|имя_отправителя|..." т.е. одна поссылка - одна строка
    // в качестве разделителя будет выступать 
    // вертикальная черта, таков способ очень удобен тем, что мы за одну строку читаем всю
    // нужную информацию для создания объекта
    while(fgets(buf, 500, f) != NULL) {
        char* tmp = new char[strlen(buf) + 1];
        strcpy(tmp, buf);

        tmp[strlen(tmp) - 1] = '\0'; //Убираем лишний \n в конце

        char* vars[7]; //Сюда мы будем складывать то что мы распарсили из строки

        int i = 0;
        char* token = strtok(tmp, "|");
        while(token) {
            vars[i] = new char[strlen(token) + 1];
            strcpy(vars[i], token);
            i++;
            token = strtok(NULL, "|");
        }
        add(p, new parcel_t(vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], atof(vars[6])));
        
        delete[] vars[0];
        delete[] vars[1];
        delete[] vars[2];
        delete[] vars[3];
        delete[] vars[4];
        delete[] vars[5];
        delete[] vars[6];
        delete[] tmp;

    }
    fclose(f);
}