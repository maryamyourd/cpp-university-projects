#include <iostream>
#include "bike_sharing.h"

int main() 
{
    // --- Setup ---
    Location locA("Plac Politechniki", 52.219377, 21.011844);
    Location locB("Westfield Arkadia", 52.231764, 20.994511);

    Station stationA(1, "Plac Politechniki", 3, locA);
    Station stationB(2, "Westfield Arkadia", 2, locB);

    Bike bike1(101, 1), bike2(102, 1), bike3(103, 2);
    stationA.addBike(&bike1);
    stationA.addBike(&bike2);
    stationB.addBike(&bike3);

    User user1(1, "Zenda", locB);
    User user2(2, "Vansh", locA);
    Admin admin1(101, "SystemAdmin");

    // --- Valid Rental Scenario ---
    if (user1.canRent() && bike1.isAvailable()) 
    {
        Rental* rental1 = new Rental(1, &user1, &bike1, "10:00");
        user1.startRental(rental1);
        bike1.setStatus("rented");
        stationA.removeBike(bike1.getID());
        std::cout << "\n Zenda rented Bike101.\n";
    }

    // --- Ending Rental ---
    if (user1.getActiveRental()) 
    {
        user1.endRental("10:30");
        bike1.setStatus("available");
        bike1.updateStation(stationB.getID());
        stationB.addBike(&bike1);

        // Payment
        Payment payment1(201, 1, user1.getID(), 2.5, "paid");
        payment1.printReceipt();

        // Feedback
        Feedback feedback1(301, user1.getID(), "Smooth ride!", 5);
        feedback1.printFeedback();
    }

    // --- Invalid Scenario: Renting while already renting ---
    Rental* rental2 = new Rental(2, &user1, &bike2, "11:00");
    if (!user1.canRent()) 
    {
        std::cout << "\n ERROR: Zenda already has an active rental.\n";
        delete rental2;
    }

    // --- Maintenance Issue ---
    MaintenanceRequest request1(401, &bike3, "Flat tire");
    request1.printRequest();
    admin1.performMaintenance(&bike3);
    request1.resolve();
    request1.printRequest();

    // --- Invalid: Trying to rent a bike under maintenance ---
    if (!bike3.isAvailable()) 
    {
        std::cout << "\n ERROR: Bike103 is under maintenance and cannot be rented.\n";
    }

    // --- Full Station Test ---
    Bike bike4(104, 2);
    Bike bike5(105, 2);
    stationB.addBike(&bike4);  // OK
    if (!stationB.hasSpace()) 
    {
        std::cout << "\n ERROR: StationB is full. Can't add more bikes.\n";
    }

    // --- View All Info ---
    std::cout << "\nStation A Bikes:\n";
    stationA.printBikes();

    std::cout << "\nStation B Bikes:\n";
    stationB.printBikes();

    std::cout << "\nZenda's Rental History:\n";
    user1.showRentalHistory();

    return 0;
}
