#ifndef CITYBIKEHIRE_H
#define CITYBIKEHIRE_H

#include <string>
#include <vector>

// Location class representing a city with coordinates
class Location {
public:
    std::string city;
    double latitude, longitude;

    Location(std::string c = "", double lat = 0.0, double lon = 0.0);
    void showLocation() const;
};

// Bike class represents a single bike in the system
class Bike {
private:
    int bikeID;
    std::string status; // "available", "rented", "maintenance"
    int dockID; // station ID

public:
    Bike(int id, int dock);
    int getID() const;
    std::string getStatus() const;
    int getDockID() const; // Returns the current dock ID
    bool isAvailable() const;
    void setStatus(const std::string& newStatus);
    void moveToDock(int newDockID);
    void displayInfo() const;
};

class Hire; // Forward declaration for use in Customer class

// Customer class for users renting bikes
class Customer {
private:
    int customerID;
    std::string fullName;
    Location location;
    Hire* currentHire;
    std::vector<Hire*> history;

public:
    Customer(int id, std::string name, Location loc = {});
    int getID() const;
    std::string getName() const; // Returns customer's full name
    bool canHire() const; // Checks if customer currently has an active hire
    void startHire(Hire* h);
    void endHire(std::string endTime);
    Hire* getCurrentHire() const;
    void showHistory() const;
    void printCustomerInfo() const;
};

// Dock class representing bike stations
class Dock {
private:
    int dockID; // ID of the dock station
    std::string dockName;
    Location location;
    int capacity;
    std::vector<Bike*> parkedBikes;

public:
    Dock(int id, std::string name, int cap, Location loc = {});
    int getID() const;
    std::string getName() const;
    int getCapacity() const;
    int availableSlots() const;
    bool hasSpace() const;
    void addBike(Bike* b);
    bool removeBike(int bikeID); // Remove a bike from the dock when rented
    std::vector<Bike*> getAvailableBikes() const;
    void listBikes() const;
};

// Hire class represents a single rental
class Hire {
private:
    int hireID;
    Customer* customer;
    Bike* bike;
    std::string startTime;
    std::string endTime;

public:
    Hire(int id, Customer* c, Bike* b, std::string start); // Create a hire when a bike is rented
    int getHireID() const;
    Customer* getCustomer() const;
    Bike* getBike() const;
    void endHire(std::string end);
    bool isActive() const; // Check if the rental is still active
    int getDuration() const; // Duration logic based on string timestamps
    void printHireInfo() const;
};

// Transaction class handles payment
class Transaction {
private:
    int transactionID;
    int hireID;
    int customerID;
    double amount;
    std::string status; // e.g. "paid", "pending"

public:
    Transaction(int tid, int hid, int cid, double amt, std::string stat);
    void printReceipt() const;
};

// Operator class handles maintenance tasks
class Operator {
private:
    int operatorID;
    std::string name;

public:
    Operator(int id, std::string name);
    void inspectBike(Bike* b); // Check bike condition
    void releaseBike(Bike* b); // Mark bike as available
};

// RepairRequest class for reporting and resolving issues
class RepairRequest {
private:
    int requestID;
    Bike* bike;
    std::string issue;
    std::string status; // e.g. "open", "resolved"

public:
    RepairRequest(int id, Bike* b, std::string prob);
    void markResolved(); // Mark the issue as resolved
    void printRequest() const;
};

#endif // CITYBIKEHIRE_H
