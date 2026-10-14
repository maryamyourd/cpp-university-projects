#include "CityBikeHire.h"
#include <iostream>

// ----- Location -----
Location::Location(std::string c, double lat, double lon) : city(c), latitude(lat), longitude(lon) {}
void Location::showLocation() const {
    std::cout << city << " (" << latitude << ", " << longitude << ")" << std::endl;
}

// ----- Bike -----
Bike::Bike(int id, int dock) : bikeID(id), dockID(dock), status("available") {}
int Bike::getID() const { return bikeID; }
std::string Bike::getStatus() const { return status; }
int Bike::getDockID() const { return dockID; }
bool Bike::isAvailable() const { return status == "available"; }
void Bike::setStatus(const std::string& newStatus) { status = newStatus; }
void Bike::moveToDock(int newDockID) { dockID = newDockID; }
void Bike::displayInfo() const {
    std::cout << "BikeID: " << bikeID << ", Status: " << status << ", Dock: " << dockID << std::endl;
}

// ----- Customer -----
Customer::Customer(int id, std::string name, Location loc)
    : customerID(id), fullName(name), location(loc), currentHire(nullptr) {}

int Customer::getID() const { return customerID; }
std::string Customer::getName() const { return fullName; }
bool Customer::canHire() const { return currentHire == nullptr; }
void Customer::startHire(Hire* h) { currentHire = h; }
void Customer::endHire(std::string endTime) {
    if (currentHire) {
        currentHire->endHire(endTime);
        history.push_back(currentHire);
        currentHire = nullptr;
    }
}
Hire* Customer::getCurrentHire() const { return currentHire; }
void Customer::showHistory() const {
    for (const auto& h : history) h->printHireInfo();
}
void Customer::printCustomerInfo() const {
    std::cout << "Customer: " << fullName << " (ID: " << customerID << ")" << std::endl;
}

// ----- Dock -----
Dock::Dock(int id, std::string name, int cap, Location loc)
    : dockID(id), dockName(name), capacity(cap), location(loc) {}

int Dock::getID() const { return dockID; }
std::string Dock::getName() const { return dockName; }
int Dock::getCapacity() const { return capacity; }
int Dock::availableSlots() const { return capacity - parkedBikes.size(); }
bool Dock::hasSpace() const { return availableSlots() > 0; }

void Dock::addBike(Bike* b) {
    if (hasSpace()) parkedBikes.push_back(b);
}
bool Dock::removeBike(int bikeID) {
    for (auto it = parkedBikes.begin(); it != parkedBikes.end(); ++it) {
        if ((*it)->getID() == bikeID) {
            parkedBikes.erase(it);
            return true;
        }
    }
    return false;
}
std::vector<Bike*> Dock::getAvailableBikes() const {
    std::vector<Bike*> result;
    for (auto* b : parkedBikes) {
        if (b->isAvailable()) result.push_back(b);
    }
    return result;
}
void Dock::listBikes() const {
    for (auto* b : parkedBikes) b->displayInfo();
}

// ----- Hire -----
Hire::Hire(int id, Customer* c, Bike* b, std::string start)
    : hireID(id), customer(c), bike(b), startTime(start), endTime("") {}

int Hire::getHireID() const { return hireID; }
Customer* Hire::getCustomer() const { return customer; }
Bike* Hire::getBike() const { return bike; }
void Hire::endHire(std::string end) { endTime = end; }
bool Hire::isActive() const { return endTime.empty(); }

int Hire::getDuration() const {
    // Just a mock logic (convert "08:00" -> 800)
    return std::stoi(endTime) - std::stoi(startTime);
}
void Hire::printHireInfo() const {
    std::cout << "Hire #" << hireID << ": " << customer->getName()
              << " hired Bike" << bike->getID()
              << " from " << startTime << " to " << (endTime.empty() ? "in progress" : endTime)
              << std::endl;
}

// ----- Transaction -----
Transaction::Transaction(int tid, int hid, int cid, double amt, std::string stat)
    : transactionID(tid), hireID(hid), customerID(cid), amount(amt), status(stat) {}

void Transaction::printReceipt() const {
    std::cout << "Transaction #" << transactionID
              << " | Hire: " << hireID << " | Customer: " << customerID
              << " | Amount: $" << amount << " | Status: " << status << std::endl;
}

// ----- Operator -----
Operator::Operator(int id, std::string name) : operatorID(id), name(name) {}
void Operator::inspectBike(Bike* b) {
    std::cout << "Inspecting bike " << b->getID() << std::endl;
}
void Operator::releaseBike(Bike* b) {
    b->setStatus("available");
    std::cout << "Bike " << b->getID() << " released for use." << std::endl;
}

// ----- RepairRequest -----
RepairRequest::RepairRequest(int id, Bike* b, std::string prob)
    : requestID(id), bike(b), issue(prob), status("open") {}

void RepairRequest::markResolved() { status = "resolved"; }
void RepairRequest::printRequest() const {
    std::cout << "Request #" << requestID
              << " | Bike: " << bike->getID()
              << " | Issue: " << issue
              << " | Status: " << status << std::endl;
}

