#include <iostream>
#include <cstring>

using namespace std;
struct Animal {
    int id;
    char* species;
    int age;
    char* nickname;
    Animal* next;
};
Animal* Zoo = nullptr;
void add_Animal(int id, const char* species, int age, const char* nickname) {

    Animal* newAnimal = new Animal;
    newAnimal->id = id;
    newAnimal->age = age;
    newAnimal->species = new char[strlen(species) + 1];
    newAnimal->nickname = new char[strlen(nickname) + 1];
    strcpy(newAnimal->species, species);
    strcpy(newAnimal->nickname, nickname);
    newAnimal->next = nullptr;
    if (!Zoo || id < Zoo->id) {
        newAnimal->next = Zoo;
        Zoo = newAnimal;
        return;
    }
    Animal* current = Zoo;
    Animal* prev = nullptr;
    while (current && current->id < id) {
        prev = current;
        current = current->next;
    }
    newAnimal->next = current;
    if (prev) {
        prev->next = newAnimal;
    } else {
        Zoo = newAnimal;
    }
}
void remove_Animal(int id) {
    if (!Zoo) return;
    Animal* current = Zoo;
    Animal* prev = nullptr;
    while (current && current->id != id) {
        prev = current;
        current = current->next;
    }
    if (!current) return;
    if (prev) {
        prev->next = current->next;
    } else {
        Zoo = current->next;
    }
    delete[] current->species;
    delete[] current->nickname;
    delete current;
}
void print_Zoo() {
    Animal* current = Zoo;
    while (current) {
        cout << "ID: " << current->id << ", Nickname: " << current->nickname
<< ", Species: " << current->species << ", Age: " << current->age << endl;
        current = current->next;
    }
}
int defaultAge = -1;
int& update(int id, const char* nickname, const char* species) {
    Animal* current = Zoo;
    Animal* prev = nullptr;
    while (current && current->id < id) {
        prev = current;
        current = current->next;
    }
    if (current && current->id == id) {
        if (strcmp(current->nickname, nickname) != 0) {
            delete[] current->nickname;
            delete[] current->species;
            current->nickname = new char[strlen(nickname) + 1];
            current->species = new char[strlen(species) + 1];
            strcpy(current->nickname, nickname);
            strcpy(current->species, species);
            current->age = -1; // Reset age
        }
        return current->age;
    }
    Animal* newAnimal = new Animal;
    newAnimal->id = id;
    newAnimal->age = -1;
    newAnimal->species = new char[strlen(species) + 1];
    newAnimal->nickname = new char[strlen(nickname) + 1];
    strcpy(newAnimal->species, species);
    strcpy(newAnimal->nickname, nickname);
    newAnimal->next = current;
    if (prev) {
        prev->next = newAnimal;
    } else {
        Zoo = newAnimal;
    }
    return newAnimal->age;
}
int main() {
    add_Animal(101, "Tiger", 5, "Bobby");
    add_Animal(102, "Lion", 8, "Simba");
    add_Animal(103, "Elephant", 12, "Dumbo");
    cout << "Initial List:\n";
    print_Zoo();
    remove_Animal(102);
    cout << "\nAfter Removing Lion:\n";
    print_Zoo();
    update(101, "King", "Tiger") = 10;
    cout << "\nAfter Updating ID 101:\n";
    print_Zoo();
    update(12345, "King Kong", "Big Ape")++; 
    cout << "\nAfter Adding and Incrementing King Kong:\n";
    print_Zoo();
    return 0;
} 
