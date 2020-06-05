#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <iterator>
#include <cstring>

#define sep_len 40

#define DEBUG

//Копирует строку и возвращает указатель новую строку
char* alloc_and_copy(char* str) {
    char* res = new char[strlen(str) + 1];
    if(!res) throw std::exception();
    strcpy(res, str);
    res[strlen(res)] = '\0';
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

typedef struct Node {
    parcel_t* data;
    struct Node* next;
} Node;

//Функция, которая добавляет в конец коллекции новую поссылку
void new_parcel(Node**);

//Печатаем таблицу
void print_parcel(parcel_t p);

void print_table(Node*);

//ищет поссылку по фамилии и имени отправителя
void find_by_sender(Node*);

//ищет поссылку с весом больше заданного
void find_by_weight(Node*);

//вставляет поссылку в конец списка
void add(Node**, parcel_t*);

//находит и удаляет поссылки с весом меньше заданного
void find_and_delete(Node*);

//Сортирует список по фамилии отправителя
void sort_by_last_name(Node**);

//Сохраняет поссылку в формате
//s_last_name|s_first_name|s_adress|r_last_name|r_first_name|r_adress|weight
void save_list(Node*);

//Вытаскивает данные из файла, написанного в вышеизложенном формате
void load_list(Node*);

void clear_nodes(Node* head) {
    if(head == NULL) return;
    else {
        Node* prev = NULL;
        while(head->next) {
            prev = head;
            head = head->next;
            
            delete prev->data;
            delete prev;
        }
        delete head->data;
        delete head;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    Node* parcels = NULL; 
    load_list(parcels);
    char choice = '0';
    do {
        std::cout << "Что вы хотите сделать?" << std::endl;
        std::cout << "1. Добавить новую поссылку?\n2. Распечатать все посслыки\n" 
                  << "3. Найти все поссылки по их отправителю\n4. Найти поссылки больше заданного веса\n" 
                  << "5. Удалить поссылки ниже заданного веса\n6. Сортировать список поссылок по фамилии отправителя\n"
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
            sort_by_last_name(&parcels);
            break;
        case '0':
            save_list(parcels);
            clear_nodes(parcels);
            break;
        default:
            std::cout << "wrong argument" << std::endl;
            break;
        }
        std::cout << std::endl;
    } while(choice != '0');
    return 0;
}


void add(Node** head, parcel_t* p) {
    Node* node = new Node;
    node->data = p;
    node->next = NULL;

    if(*head == NULL) {
        *head = node;
        return;
    }
    Node* tmp = *head;
    while(tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = node;
}

//Пишет message и возвращает введенную строку
char* promt(const char* message) {
    char buf[80];
    std::cout << message;
    std::cin.getline(buf, 80);
    char* dest = new char[strlen(buf) + 1];
    strcpy(dest, buf);
    dest[strlen(dest)] = '\0';
    return dest;
}

void new_parcel(Node** head) {
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
    add(head, new parcel_t(s_last_name, s_first_name, s_adress, 
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

void print_table(Node* head) {
    if(head == NULL)  {
        for(int i = 0; i < sep_len; ++i) {
            std::cout << '-';
        }
        std::cout << std::endl;
        
        std::cout << "Поссылок нет" << std::endl;
        
        for(int i = 0; i < sep_len; ++i) {
            std::cout << '-';
        }
    }
    else {
        for(int i = 0; i < sep_len; ++i) {
            std::cout << '-';
        }
        std::cout << std::endl;
        Node* tmp = head;
        while(tmp) {
            print_parcel(tmp->data);
            tmp = tmp->next;
        }
    }
}

void find_by_sender(Node* head) {
    for(int i = 0; i < sep_len; ++i) std::cout << '-';
    std::cout << std::endl;

    char sender_fname[80], sender_lname[80];
    std::cin.ignore(INT8_MAX, '\n');
    std::cout << "Введите фамилию отправителя: ";
    std::cin.getline(sender_lname, 80);
    std::cout << "Введите имя отправителя: ";
    std::cin.getline(sender_fname, 80);
    
    //Проходим по всему массиву
    Node* tmp = head;
    while(tmp) {
        if(!strncmp(tmp->data->s_first_name, sender_fname, strlen(tmp->data->s_first_name))
        && !strncmp(tmp->data->s_last_name, sender_lname, strlen(tmp->data->s_last_name))) {
            print_parcel(tmp->data);
        }
    }

    for(int i = 0; i < sep_len; ++i) std::cout << '-';
    std::cout << std::endl;
}

void find_by_weight(Node* head) {

    for(int i = 0; i < sep_len; ++i) std::cout << '-';
    std::cout << std::endl;
    double w;
    std::cout << "Введите вес поссылки: ";
    std::cin >> w;

    while(head) {
        if(head->data->weight > w) {
            print_parcel(head->data);
        }
        head = head->next;
    } 
}

void delete_node(Node* prev, Node* next) {
    delete prev->next->data;
    delete prev->next;
    prev->next = next;
}

void find_and_delete(Node* head) {
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
    Node* prev = NULL;
    while(head->next) {
        if(head->data->weight < w) {
            if(prev == NULL) {
                delete head->data;
                Node* tmp = head;
                head = head->next;
                delete tmp;
            } else {
                delete_node(prev, head->next);
            }
        }
        prev = head;
        head = head->next;
    }

}


void sortedInsert(Node** head, struct Node* new_node) 
{ 
    Node* current; 
    if (*head == NULL || (*head)->data >= new_node->data) 
    { 
        new_node->next = *head; 
        *head = new_node; 
    } 
    else
    { 
        /* Locate the node before the point of insertion */
        current = *head; 
        while (current->next!=NULL && 
               current->next->data < new_node->data) 
        { 
            current = current->next; 
        } 
        new_node->next = current->next; 
        current->next = new_node; 
    } 
} 

void sort_by_last_name(Node** head) {
    std::cout << "not implemented" << std::endl;
    Node *sorted = NULL; 
  
    Node *current = *head; 
    while (current != NULL) 
    { 
        struct Node *next = current->next; 
  
        sortedInsert(&sorted, current); 
  
        current = next; 
    } 
  
    *head = sorted; 
}

void save_list(Node* head) {
    FILE* file = fopen("db.txt", "w");
    if(!file) {
        std::cout << "Не удается создать/открыть файл!" << std::endl;
        exit(-1);
    }
    rewind(file);
    while(head) {
        fprintf(file, "%s|", head->data->s_last_name);
        fprintf(file, "%s|", head->data->s_first_name);
        fprintf(file, "%s|", head->data->s_adress);
        fprintf(file, "%s|", head->data->r_last_name);
        fprintf(file, "%s|", head->data->r_first_name);
        fprintf(file, "%s|", head->data->r_adress);
        fprintf(file, "%lf\n", head->data->weight);
        head = head->next;
    }
    fclose(file);
}

void load_list(Node* head) {
    FILE* tmpfile = fopen("db.txt", "a");// нужно для того чтобы создать файл если его нет
    if(!tmpfile) {
        std::cout << "Проблемы с файлом!" << std::endl;
        exit(-1);
    }
    fclose(tmpfile);
    
    FILE* f = fopen("db.txt", "r");
    if(!f) {
        std::cout << "Проблемы с файлом!" << std::endl;
        exit(-1);
    }
    
    fseek(f, 0, SEEK_END); //Переносим "курсор" в начало файла
    int len = ftell(f);
    if(len == 0) {
        std::cout << "База данных пуста" << std::endl;
        return;
    }

    //char buf[500]; //тут лучше на буфере не жалеть, т.к формат сохранения будет таков:
    // "Фамилия_отправителя|имя_отправителя|..." т.е. одна поссылка - одна строка
    // в качестве разделителя будет выступать 
    // вертикальная черта, таков способ очень удобен тем, что мы за одну строку читаем всю
    // нужную информацию для создания объекта
    char* buf = NULL;
    size_t lenn = 0;
    fseek(f, 0, SEEK_END);
    while(getline(&buf, &lenn, f) != -1) {
        char* tmp = new char[strlen(buf) + 1];
        strcpy(tmp, buf);

        tmp[strlen(tmp) - 1] = '\0'; //Убираем \n в конце

        char* vars[7]; //Сюда мы будем складывать то что мы распарсили из строки

        int i = 0;
        char* token = strtok(tmp, "|");
        while(token) {
            vars[i] = new char[strlen(token) + 1];
            strcpy(vars[i], token);
            vars[i][strlen(vars[i])] = '\0';
            i++;
            token = strtok(NULL, "|");
        }
        add(&head, new parcel_t(vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], atof(vars[6])));
        

        //для легкости дебага придется написать такое...
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
