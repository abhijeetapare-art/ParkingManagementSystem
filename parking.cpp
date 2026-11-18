#include <iostream>
#include <string>
using namespace std;

class ParkingSystem {
    struct Vehicle {
        string number, owner;
        int hours;
        bool occupied;
    };

    Vehicle bike[5], car[5];
    int totalEarnings = 0;
    const int bikeRate = 20, carRate = 40;

public:
    ParkingSystem() {
        for (int i = 0; i < 5; i++) {
            bike[i].occupied = false;
            car[i].occupied = false;
        }
    }

    void line() {
        cout << "\n========================================\n";
    }

    void header() {
        line();
        cout << "       PARKING MANAGEMENT SYSTEM";
        line();
    }

    void adminPanel() {
        int password;
        cout << "\nEnter Admin Password: ";
        cin >> password;

        if (password != 1234) {
            cout << "\nInvalid Password!\n";
            return;
        }

        int choice;
        do {
            header();
            cout << "\nADMIN PANEL\n1. View All Parked Vehicles\n2. View Parking Status\n3. View Total Earnings\n4. Back to Main Menu\n";
            cout << "\nEnter Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: viewVehicles(); break;
                case 2: parkingStatus(); break;
                case 3: cout << "\nTotal Earnings: Rs. " << totalEarnings << endl; break;
                case 4: cout << "\nReturning to Main Menu...\n"; break;
                default: cout << "\nInvalid Choice!\n";
            }
            if (choice != 4) pauseScreen();
        } while (choice != 4);
    }

    void customerPanel() {
        int choice;
        do {
            header();
            cout << "\nCUSTOMER PANEL\n1. Park a Vehicle\n2. Remove a Vehicle\n3. View Available Slots\n4. Back to Main Menu\n";
            cout << "\nEnter Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: parkVehicle(); break;
                case 2: removeVehicle(); break;
                case 3: parkingStatus(); break;
                case 4: cout << "\nReturning to Main Menu...\n"; break;
                default: cout << "\nInvalid Choice!\n";
            }
            if (choice != 4) pauseScreen();
        } while (choice != 4);
    }

    void parkVehicle() {
        int type;
        header();
        cout << "\nVEHICLE PARKING\n1. Two Wheeler (Rs. 20/hour)\n2. Four Wheeler (Rs. 40/hour)\n";
        cout << "\nSelect Vehicle Type: ";
        cin >> type;

        Vehicle *slots;
        int rate;

        switch (type) {
            case 1: slots = bike; rate = bikeRate; break;
            case 2: slots = car; rate = carRate; break;
            default: cout << "\nInvalid Vehicle Type!\n"; return;
        }

        string number, owner;
        cout << "\nEnter Vehicle Number: ";
        cin >> number;

        for (int i = 0; i < 5; i++) {
            if ((bike[i].occupied && bike[i].number == number) ||
                (car[i].occupied && car[i].number == number)) {
                cout << "\nVehicle is already parked!\n";
                return;
            }
        }

        cout << "Enter Owner Name: ";
        cin >> ws;
        getline(cin, owner);

        for (int i = 0; i < 5; i++) {
            if (!slots[i].occupied) {
                slots[i].number = number;
                slots[i].owner = owner;
                slots[i].hours = rate;
                slots[i].occupied = true;

                cout << "\n";
                line();
                cout << "VEHICLE PARKED SUCCESSFULLY!";
                line();
                cout << "\nOwner Name : " << owner;
                cout << "\nVehicle No : " << number;
                cout << "\nSlot No    : " << (type == 1 ? "B" : "C") << i + 1;
                cout << "\nHourly Rate: Rs. " << rate << "\n";
                return;
            }
        }
        cout << "\nSorry! No Parking Slots Available.\n";
    }

    void removeVehicle() {
        string number;
        header();
        cout << "\nVEHICLE EXIT\nEnter Vehicle Number: ";
        cin >> number;

        for (int i = 0; i < 5; i++) {
            if (bike[i].occupied && bike[i].number == number) {
                int hours;
                cout << "\nEnter Parking Duration (hours): ";
                cin >> hours;
                if (hours <= 0) {
                    cout << "\nInvalid Duration!\n";
                    return;
                }

                int bill = hours * bikeRate;
                totalEarnings += bill;

                cout << "\n";
                line();
                cout << "PARKING BILL";
                line();
                cout << "\nVehicle Number : " << number;
                cout << "\nVehicle Type   : Two Wheeler";
                cout << "\nParking Hours  : " << hours;
                cout << "\nRate Per Hour  : Rs. " << bikeRate;
                cout << "\nTotal Amount   : Rs. " << bill;

                bike[i].occupied = false;
                cout << "\n\nThank You! Visit Again.\n";
                return;
            }

            if (car[i].occupied && car[i].number == number) {
                int hours;
                cout << "\nEnter Parking Duration (hours): ";
                cin >> hours;
                if (hours <= 0) {
                    cout << "\nInvalid Duration!\n";
                    return;
                }

                int bill = hours * carRate;
                totalEarnings += bill;

                cout << "\n";
                line();
                cout << "PARKING BILL";
                line();
                cout << "\nVehicle Number : " << number;
                cout << "\nVehicle Type   : Four Wheeler";
                cout << "\nParking Hours  : " << hours;
                cout << "\nRate Per Hour  : Rs. " << carRate;
                cout << "\nTotal Amount   : Rs. " << bill;

                car[i].occupied = false;
                cout << "\n\nThank You! Visit Again.\n";
                return;
            }
        }
        cout << "\nVehicle Not Found!\n";
    }

    void parkingStatus() {
        int bikeOccupied = 0, carOccupied = 0;

        for (int i = 0; i < 5; i++) {
            if (bike[i].occupied) bikeOccupied++;
            if (car[i].occupied) carOccupied++;
        }

        header();
        cout << "\nPARKING STATUS\n";
        cout << "\nTwo Wheeler Slots\nTotal Slots     : 5";
        cout << "\nOccupied Slots  : " << bikeOccupied;
        cout << "\nAvailable Slots : " << 5 - bikeOccupied;
        cout << "\n\nFour Wheeler Slots\nTotal Slots     : 5";
        cout << "\nOccupied Slots  : " << carOccupied;
        cout << "\nAvailable Slots : " << 5 - carOccupied;
        cout << "\n\nTotal Capacity  : 10";
        cout << "\nTotal Occupied  : " << bikeOccupied + carOccupied;
        cout << "\nTotal Available : " << 10 - bikeOccupied - carOccupied << endl;
    }

    void viewVehicles() {
        header();
        cout << "\nPARKED VEHICLES\nTWO WHEELERS\n";
        bool found = false;

        for (int i = 0; i < 5; i++) {
            if (bike[i].occupied) {
                cout << "\nSlot B" << i + 1 << " | Number: " << bike[i].number << " | Owner: " << bike[i].owner;
                found = true;
            }
        }
        if (!found) cout << "\nNo Two Wheelers Parked.";

        cout << "\n\nFOUR WHEELERS\n";
        found = false;

        for (int i = 0; i < 5; i++) {
            if (car[i].occupied) {
                cout << "\nSlot C" << i + 1 << " | Number: " << car[i].number << " | Owner: " << car[i].owner;
                found = true;
            }
        }
        if (!found) cout << "\nNo Four Wheelers Parked.";
        cout << endl;
    }

    void pauseScreen() {
        cout << "\n\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    void run() {
        int choice;
        do {
            header();
            cout << "\nMAIN MENU\n1. Admin Panel\n2. Customer Panel\n3. Exit\n";
            cout << "\nEnter Your Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: adminPanel(); break;
                case 2: customerPanel(); break;
                case 3:
                    line();
                    cout << "THANK YOU FOR VISITING!\nSYSTEM EXITED SUCCESSFULLY";
                    line();
                    break;
                default: cout << "\nInvalid Choice! Try Again.\n";
            }
            if (choice < 1 || choice > 3) pauseScreen();
        } while (choice != 3);
    }
};

int main() {
    ParkingSystem p;
    p.run();
    return 0;
}