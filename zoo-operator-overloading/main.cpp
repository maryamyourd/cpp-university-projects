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
    Animal(const Animal& other);//////
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
}
///////
Animal::Animal(const Animal& other) {
    id = other.id;
    age = other.age;
    species = new char[strlen(other.species) + 1];
    strcpy(species, other.species);
    nickname = new char[strlen(other.nickname) + 1];
    strcpy(nickname, other.nickname);
    next = nullptr;
}
///////
Animal::~Animal() {
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
    ////////
    Zoo operator+(const Zoo& x) const;
    friend Zoo operator-(const Zoo& a, const Zoo& b);
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
    } else {
        newAnimal->next = current;
        if (prev) {
            prev->next = newAnimal;
        } else {
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
        } else {
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

Zoo Zoo::operator+(const Zoo& x) const {
    Zoo newZoo;
    Animal* temp1 = head;
    Animal* temp2 = x.head;

    while (temp1) {
        newZoo.add_Animal(temp1->id, temp1->species, temp1->age, temp1->nickname);
        temp1 = temp1->next;
    }

    while (temp2) {
        Animal* existing = newZoo.head;
        bool found = false;
        while (existing) {
            if (existing->id == temp2->id) {
                delete[] existing->species;
                delete[] existing->nickname;
                existing->species = new char[strlen(temp2->species) + 1];
                strcpy(existing->species, temp2->species);
                existing->nickname = new char[strlen(temp2->nickname) + 1];
                strcpy(existing->nickname, temp2->nickname);
                found = true;
                break;
            }
            existing = existing->next;
        }
        if (!found) {
            newZoo.add_Animal(temp2->id, temp2->species, temp2->age, temp2->nickname);
        }
        temp2 = temp2->next;
    }

    return newZoo;
}
/////
Zoo operator-(const Zoo& a, const Zoo& b) { ///////////////we check if each Animal is in Zoob or not and if not and something is not in Zoo b it will add to newZoo
    Zoo newZoo;

    Animal* temp = a.head;

    while (temp) {
        Animal* search = b.head;
        bool found = false;
        while (search) {
            if (search->id == temp->id) {
                found = true;
                break;
            }
            search = search->next;
        }
        if (!found) {
            newZoo.add_Animal(temp->id, temp->species, temp->age, temp->nickname);
        }
        temp = temp->next;
    }

    return newZoo;
}

int main() {
    Zoo zoo1, zoo2;

    zoo1.add_Animal(101, "Tiger", 5, "Bobby");
    zoo1.add_Animal(102, "Lion", 8, "Simba");
    zoo1.add_Animal(103, "Elephant", 12, "Dumbo");
////
    zoo2.add_Animal(102, "Lion", 8, "Simba");
    zoo2.add_Animal(104, "Panda", 4, "Pho");
    zoo2.add_Animal(105, "Giraffe", 7, "Tall");
    cout << "\nZoo 1:\n";
    zoo1.print();
    cout << "\nZoo 2:\n";
    zoo2.print();
/////
    Zoo zoo3 = zoo1 + zoo2;
    cout << "\nZoo 3 (Zoo 1 + Zoo 2):\n";
    zoo3.print();
/////
    Zoo zoo4 = zoo1 - zoo2;
    cout << "\nZoo 4 (Zoo 1 - Zoo 2):\n";
    zoo4.print();

    return 0;
}

