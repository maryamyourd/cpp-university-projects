#include <iostream>
#include <cstring>

using namespace std;
class Animal {
public:
    int id;
    char* species;
    int age;
    char* nickname;
    Animal* next;

    Animal(int id, const char* species, int age, const char* nickname);
    ~Animal();
    void print();
};

Animal::Animal(int id, const char* species, int age, const char* nickname) {
    this->id = id;
    this->age = age;
    this->species = new char[strlen(species) + 1];
    strcpy(this->species, species);
    this->nickname = new char[strlen(nickname) + 1];
    strcpy(this->nickname, nickname);
    this->next = nullptr;

    cout << "Created: ID = " << id << ", Species = " << species
        << ", Age = " << age << ", Nickname = " << nickname << endl;
}

Animal::~Animal() {
    cout << "Deleted: ID = " << id << ", Species = " << species
        << ", Age = " << age << ", Nickname = " << nickname << endl;
    delete[] species;
    delete[] nickname;
}

void Animal::print() {
    cout << "ID: " << id << ", Species: " << species
        << ", Age: " << age << ", Nickname: " << nickname << endl;
}

class Zoo {
public:
    Animal* head;

    Zoo();
    ~Zoo();
    void add_Animal(int id, const char* species, int age, const char* nickname);
    void remove_Animal(int id);
    void print();
    int& update(int id, const char* nickname, const char* species);
};

Zoo::Zoo() {
    head = nullptr;
}

Zoo::~Zoo() {
    while (head) {
        Animal* temp = head;
        head = head->next;
        delete temp;
    }
}

void Zoo::add_Animal(int id, const char* species, int age, const char* nickname) {
    Animal* newAnimal = new Animal(id, species, age, nickname);

    if (!head || id < head->id) {
        newAnimal->next = head;
        head = newAnimal;
        return;
    }

    Animal* current = head;
    Animal* prev = nullptr;

    while (current && current->id < id) {
        prev = current;
        current = current->next;
    }

    if (current && current->id == id) {
        delete newAnimal; 
    }
    else {
        newAnimal->next = current;
        if (prev) {
            prev->next = newAnimal;
        }
        else {
            head = newAnimal;
        }
    }
}

void Zoo::remove_Animal(int id) {
    Animal* current = head;
    Animal* prev = nullptr;

    while (current && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current) {
        if (prev) {
            prev->next = current->next;
        }
        else {
            head = current->next;
        }
        delete current;
    }
}

void Zoo::print() {
    Animal* current = head;
    while (current) {
        current->print();
        current = current->next;
    }
}
int& Zoo::update(int id, const char* nickname, const char* species) {
    Animal* current = head;
    Animal* prev = nullptr;

    while (current && current->id < id) {
        prev = current;
        current = current->next;
    }

    if (current && current->id == id) {
        if (strcmp(current->nickname, nickname) != 0) {
            delete[] current->nickname;
            current->nickname = new char[strlen(nickname) + 1];
            strcpy(current->nickname, nickname);
        }
        delete[] current->species;
        current->species = new char[strlen(species) + 1];
        strcpy(current->species, species);
        return current->age;
    }
    Animal* newAnimal = new Animal(id, species, -1, nickname);
    newAnimal->next = current;

    if (prev) {
        prev->next = newAnimal;
    }
    else {
        head = newAnimal;
    }
    return newAnimal->age;
}

int main() {
    Zoo zoo1;
    Zoo* zoo2 = new Zoo(); 
    zoo1.add_Animal(101, "Tiger", 5, "Bobby");
    zoo1.add_Animal(102, "Lion", 8, "Simba");
    zoo1.add_Animal(103, "Elephant", 12, "Dumbo");
    cout << "\nZoo 1 Animals:\n";
    zoo1.print();
    zoo1.remove_Animal(102);
    cout << "\nZoo 1 After Removing Lion:\n";
    zoo1.print();
    zoo2->add_Animal(201, "Panda", 4, "Po");
    zoo2->add_Animal(202, "Giraffe", 7, "LongNeck");
    cout << "\nZoo 2 Animals:\n";
    zoo2->print();
    zoo1.update(101, "King", "Tiger") = 10;
    cout << "\nZoo 1 After Updating Tiger:\n";
    zoo1.print(); 
    zoo1.update(12345, "King Kong", "Big Ape")++;
    cout << "\nZoo 1 After Adding and Incrementing King Kong:\n";
    zoo1.print();

    delete zoo2;

    return 0;
}

