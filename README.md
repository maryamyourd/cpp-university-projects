# C++ University Projects

A collection of small C++ projects from my Electrical Engineering studies at
Warsaw University of Technology. They cover core programming topics: pointers
and dynamic memory, linked lists, classes and OOP, operator overloading, and
object-oriented system design.

## Projects

| Project | Description | Concepts |
|---|---|---|
| [Zoo Linked List (Update)](./zoo-linked-list-update) | Procedural zoo manager built on a sorted singly linked list, with add, remove, print and an `update` function that returns a reference | Structs, pointers, dynamic memory, returning references |
| [Zoo Management](./zoo-management) | The same zoo rewritten with `Animal` and `Zoo` classes; constructors and destructors log object creation and deletion | Classes, constructors/destructors, linked list, `new`/`delete[]` |
| [Zoo Operator Overloading](./zoo-operator-overloading) | `Zoo` class with `+` (merge two zoos) and `-` (animals that are not in the other zoo), plus a copy constructor | Operator overloading, friend functions, copy constructor |
| [Bike Sharing System](./bike-sharing) | Class design for a smart-city bike sharing system: bikes, stations, users, rentals, payments, maintenance and feedback | OOP design, header files, class relationships |
| [City Bike Hire Company](./city-bike-hire) | A complete, runnable simulation of a bike hire company with docks, customers, hires, transactions and repair requests | OOP, header/source split, `std::vector`, pointers between objects |

## Progression

The three zoo projects are three versions of the same idea:

1. **Procedural**: a linked list managed with plain functions
2. **Object-oriented**: the same logic moved into classes with proper memory management
3. **Operator overloading**: combining and comparing zoos with `+` and `-`

## How to build and run

You need a C++ compiler such as `g++` (C++11 or newer).

**Zoo projects** (single file each):

```bash
cd zoo-management
g++ main.cpp -o zoo
./zoo
```

**City Bike Hire**:

```bash
cd city-bike-hire
g++ CityBikeHire.cpp main.cpp -o citybike
./citybike
```

On Windows, run `zoo.exe` / `citybike.exe` instead of `./zoo` / `./citybike`.

## Sample output (City Bike Hire)

```
[INFO] Maryam rented Bike1001.
Transaction #201 | Hire: 1 | Customer: 1 | Amount: $3 | Status: paid
Request #301 | Bike: 1003 | Issue: Broken chain | Status: open
Inspecting bike 1003
Bike 1003 released for use.
Request #301 | Bike: 1003 | Issue: Broken chain | Status: resolved

[ERROR] Dock2 is full. Cannot add more bikes.
```

## Notes

- The Bike Sharing project contains the class declarations (`bike_sharing.h`),
  a test scenario and a written system description. The class implementations
  are not part of this repository, so it is a design-focused project and does
  not build on its own. City Bike Hire is the fully implemented version.
- The zoo projects are written with raw pointers and manual memory management
  on purpose, to practise how `new` and `delete[]` work.

## Tools

C++ · g++ · Git · GitHub

## Author

Maryam Yourdkhani, Electrical Engineering student, Warsaw University of Technology
