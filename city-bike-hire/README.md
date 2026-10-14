This project simulates a straightforward bike rental system in a modern city. The system allows users to rent bikes from different stations scattered around the city. The core class of the project is the Bike class, which stores key details like bike ID, current status (available, rented, or under maintenance), and the station where the bike is currently located.

Bikes are placed in designated spots called Docks. Each dock has a fixed capacity, meaning it can only store a limited number of bikes at a time. Customers can rent bikes as long as one is available and there is space in the dock.

Once a customer rents a bike, a Hire object is created, which stores information about the rental, such as the start time, the bike, and the customer. After the rental is completed, the system calculates the rental duration and processes the payment using the Transaction class.

If a bike encounters an issue, customers can report it using the RepairRequest class. An Operator will inspect and fix the bike, making it available for rent again.

The system operates under a few basic rules:

A customer can only rent one bike at a time.

Bikes under repair cannot be rented.

Docks cannot hold more bikes than their capacity.

Bikes must be returned to an official dock, not a random location.

This system efficiently organizes interactions between bikes, docks, customers, and support staff. It functions as a simplified version of real-world bike-sharing services used in many cities today.
