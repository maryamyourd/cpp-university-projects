#ifndef BIKESHARING_H
#define BIKESHARING_H

#include <string>
#include <vector>

class Location 
{
public:
    std::string address;
    double latitude, longitude;

    Location(std::string addr = "", double lat = 0.0, double lon = 0.0);
    void printLocation() const;
};

class Bike 
{
private:
    int bikeID;
    std::string status;
    int stationID;

public:
    Bike(int id, int station);
    int getID() const;
    std::string getStatus() const;
    int getStationID() const;
    void setStatus(const std::string& newStatus);
    void updateStation(int newStationID);
    bool isAvailable() const;
    void printInfo() const;
};

class Rental; // Forward declaration

class User 
{
private:
    int userID;
    std::string name;
    Location location;
    Rental* activeRental;
    std::vector<Rental*> rentalHistory;

public:
    User(int id, std::string username, Location loc = {});
    int getID() const;
    std::string getName() const;
    bool canRent() const;
    void startRental(Rental* r);
    void endRental(std::string endTime);
    Rental* getActiveRental() const;
    void showRentalHistory() const;
    void printInfo() const;
};

class Station 
{
private:
    int stationID;
    std::string name;
    Location location;
    int capacity;
    std::vector<Bike*> bikesAtStation;

public:
    Station(int id, std::string n, int cap, Location loc = {});
    int getID() const;
    std::string getName() const;
    int getCapacity() const;
    int availableSlots() const;
    bool hasSpace() const;
    void addBike(Bike* b);
    bool removeBike(int bikeID);
    std::vector<Bike*> getAvailableBikes() const;
    void printBikes() const;
};

class Rental 
{
private:
    int rentalID;
    User* user;
    Bike* bike;
    std::string startTime;
    std::string endTime;

public:
    Rental(int id, User* u, Bike* b, std::string start);
    int getRentalID() const;
    User* getUser() const;
    Bike* getBike() const;
    void endRental(std::string end);
    bool isActive() const;
    int getDuration() const;
    void printInfo() const;
};

class Payment {
private:
    int paymentID;
    int rentalID;
    int userID;
    double amount;
    std::string status;

public:
    Payment(int pid, int rid, int uid, double amt, std::string stat);
    void printReceipt() const;
};

class Admin 
{
private:
    int adminID;
    std::string name;

public:
    Admin(int id, std::string n);
    void performMaintenance(Bike* b);
    void releaseBike(Bike* b);
};

class MaintenanceRequest 
{
private:
    int requestID;
    Bike* bike;
    std::string reason;
    std::string status;

public:
    MaintenanceRequest(int rid, Bike* b, std::string r);
    void resolve();
    void printRequest() const;
};

class Feedback 
{
private:
    int feedbackID;
    int userID;
    std::string comment;
    int rating;

public:
    Feedback(int fid, int uid, std::string comm, int rate);
    void printFeedback() const;
};

#endif // BIKESHARING_H
