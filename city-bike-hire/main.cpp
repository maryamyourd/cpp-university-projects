#include <iostream>
#include "CityBikeHire.h"

int main() {
    // --- Setup ---
    Location loc1("Tehran", 35.6892, 51.3890);
    Location loc2("Shiraz", 29.5918, 52.5836);

    Dock dock1(1, "Azadi Square", 2, loc1);
    Dock dock2(2, "Shiraz Station", 2, loc2);

    Bike bike1(1001, 1);
    Bike bike2(1002, 1);
    Bike bike3(1003, 2);

    dock1.addBike(&bike1);
    dock1.addBike(&bike2);
    dock2.addBike(&bike3);

    Customer customer1(1, "Maryam Yourdkhani ", loc1);
    Operator operator1(101, "Maintenance Guy");

    // --- Successful Hire ---
    if (customer1.canHire() && bike1.isAvailable()) {
        Hire* hire1 = new Hire(1, &customer1, &bike1, "08:00");
        customer1.startHire(hire1);
        bike1.setStatus("rented");
        dock1.removeBike(bike1.getID());
        std::cout << "\n[INFO] Maryam rented Bike1001.\n";
    }

    // --- Ending the Hire ---
    if (customer1.getCurrentHire()) {
        customer1.endHire("08:30");
        bike1.setStatus("available");
        bike1.moveToDock(dock2.getID());
        dock2.addBike(&bike1);

        Transaction t1(201, 1, customer1.getID(), 3.0, "paid");
        t1.printReceipt();
    }

    // --- Trying to rent again while already renting (should fail) ---
    Hire* hire2 = new Hire(2, &customer1, &bike2, "09:00");
    if (!customer1.canHire()) {
        std::cout << "\n[ERROR] Customer already has active hire.\n";
        delete hire2;
    }

    // --- Maintenance Request ---
    RepairRequest r1(301, &bike3, "Broken chain");
    r1.printRequest();
    operator1.inspectBike(&bike3);
    r1.markResolved();
    operator1.releaseBike(&bike3);
    r1.printRequest();

    // --- Bike under maintenance test ---
    bike3.setStatus("maintenance");
    if (!bike3.isAvailable()) {
        std::cout << "\n[ERROR] Bike1003 is under maintenance.\n";
    }

    // --- Station full test ---
    Bike bike4(1004, 2);
    dock2.addBike(&bike4); // should succeed

    if (!dock2.hasSpace()) {
        std::cout << "\n[ERROR] Dock2 is full. Cannot add more bikes.\n";
    }

    // --- Final Info ---
    std::cout << "\nDock1 Bikes:\n";
    dock1.listBikes();

    std::cout << "\nDock2 Bikes:\n";
    dock2.listBikes();

    std::cout << "\nCustomer History:\n";
    customer1.showHistory();

    return 0;
}
