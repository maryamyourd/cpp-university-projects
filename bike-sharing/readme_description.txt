This project models a comprehensive Bike Sharing System designed to simulate the rental and return of bicycles across a smart city. It supports both user interaction and administrative management through a well-structured set of interconnected classes.

Core Components

1. Bike
Each Bike has a unique ID, status (available, rented, maintenance), and current station location. Bikes can change status and be moved between stations. They form the heart of the rental system.

2. User
A User has a unique ID, name, location (address and coordinates), and can rent one bike at a time. They also maintain a history of completed rentals. Users can interact with the system to start and end rentals.

3. Station
A Station stores bikes, has a fixed capacity, and is tied to a geographical Location. It offers bikes to users if available and accepts returned bikes if not full. It manages its own inventory of bikes dynamically.

4. Rental
A Rental object links a User to a Bike for a duration, recording start and end times. It enforces rules such as only one active rental per user and tracks ride details for billing and feedback.

Administrative & Support Classes

5. Admin
An Admin represents system personnel who can mark bikes under maintenance or return them to availability. Admins perform maintenance operations based on reported issues.

6. Payment
Every Rental may have an associated Payment that includes the amount charged, status (paid, pending, failed), and links back to the rental and user. Payments make the rental lifecycle realistic and complete.

7. MaintenanceRequest
When a bike is reported faulty, a MaintenanceRequest is generated with a reason. Admins act on these requests to update the bike’s status and eventually resolve the issue.

8. Feedback
After a rental, users may submit Feedback which includes a comment and a rating (1–5). This allows the system to gather insights about service quality and user satisfaction.

9. Location
Used as a reusable component, Location holds address and coordinates for both Station and User entities, supporting features like geolocation or station proximity.

Interaction Flow

1. A User visits a Station and selects an available Bike.
2. A Rental is created and tied to the user and the bike.
3. The bike is marked as rented and removed from the station.
4. After use, the user ends the rental by returning the bike to any station.
5. A Payment is created based on rental duration.
6. Optionally, the user submits Feedback.
7. If a bike has an issue, a MaintenanceRequest is generated and handled by an Admin.

System Constraints

- A user can only have one active rental.
- A station cannot store more bikes than its capacity.
- A bike marked as rented or maintenance cannot be rented.
- Payments must be completed to close the rental.
- Feedback must be tied to completed rentals.
- Maintenance must be resolved before a bike is made available again.
