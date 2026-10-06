#include <iostream>
#include <string>
using namespace std;

struct Coach {
    int number;
    string type;
    int capacity;
    int passengers;
    Coach* next;
    Coach* prev;
    Coach(int n, string t, int c, int p) {
        number = n;
        type = t;
        capacity = c;
        passengers = p;
        next = this;
        prev = this;
    }
};
class Train {
private:
    Coach* current;
public:
    Train() {
        current = nullptr;
    }
    ~Train() {
        while (current != nullptr) {
            removeCoach(current->number);
        }
    }
    void addCoach(int number, string type, int capacity, int passengers) {
        Coach* newCoach = new Coach(number, type, capacity, passengers);
        if (current == nullptr) {
            current = newCoach;
            return;
        }
        Coach* last = current->prev;
        newCoach->next = current;
        newCoach->prev = last;
        last->next = newCoach;
        current->prev = newCoach;
    }
    bool insertCoach(int afterNumber, int number, string type,
                     int capacity, int passengers) {
        if (current == nullptr) {
            return false;
        }
        Coach* temp = current;
        do {
            if (temp->number == afterNumber) {
                Coach* newCoach = new Coach(
                    number, type, capacity, passengers
                );

                newCoach->next = temp->next;
                newCoach->prev = temp;
                temp->next->prev = newCoach;
                temp->next = newCoach;
                return true;
            }
            temp = temp->next;
        } while (temp != current);

        return false;
    }
    bool removeCoach(int number) {
        if (current == nullptr) {
            return false;
        }
        Coach* temp = current;
        do {
            if (temp->number == number) {
                if (temp->next == temp) {
                    delete temp;
                    current = nullptr;
                    return true;
                }

                if (temp == current) {
                    current = current->next;
                }

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                delete temp;
                return true;
            }
            temp = temp->next;
        } while (temp != current);

        return false;
    }
    void moveForward() {
        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        current = current->next;
    }
    void moveBackward() {
        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }
        current = current->prev;
    }
    void displayClockwise() {
        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        Coach* temp = current;

        do {
            cout << "Coach: " << temp->number
                 << " | Type: " << temp->type
                 << " | Capacity: " << temp->capacity
                 << " | Passengers: " << temp->passengers
                 << " | Available: "
                 << temp->capacity - temp->passengers << '\n';

            temp = temp->next;
        } while (temp != current);
    }
    void displayAntiClockwise() {
        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }
        Coach* temp = current;

        do {
            cout << "Coach: " << temp->number
                 << " | Type: " << temp->type
                 << " | Capacity: " << temp->capacity
                 << " | Passengers: " << temp->passengers
                 << " | Available: "
                 << temp->capacity - temp->passengers << '\n';

            temp = temp->prev;
        } while (temp != current);
    }

    void searchCoach(int number) {
        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }
        Coach* temp = current;

        do {
            if (temp->number == number) {
                cout << "\nCoach Found\n";
                cout << "Coach Number: " << temp->number << '\n';
                cout << "Coach Type: " << temp->type << '\n';
                cout << "Passenger Capacity: " << temp->capacity << '\n';
                cout << "Current Passengers: " << temp->passengers << '\n';
                cout << "Available Seats: "
                     << temp->capacity - temp->passengers << '\n';
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "Coach not found.\n";
    }
    void maximumAvailableCapacity() {
        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        Coach* temp = current;
        Coach* best = current;
        do {
            int available = temp->capacity - temp->passengers;
            int bestAvailable = best->capacity - best->passengers;

            if (available > bestAvailable) {
                best = temp;
            }

            temp = temp->next;
        } while (temp != current);
        cout << "\nCoach With Maximum Available Capacity\n";
        cout << "Coach Number: " << best->number << '\n';
        cout << "Coach Type: " << best->type << '\n';
        cout << "Passenger Capacity: " << best->capacity << '\n';
        cout << "Current Passengers: " << best->passengers << '\n';
        cout << "Available Seats: "
             << best->capacity - best->passengers << '\n';
    }
    void displayCurrent() {
        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }
        cout << "\nCurrent Coach\n";
        cout << "Coach Number: " << current->number << '\n';
        cout << "Coach Type: " << current->type << '\n';
        cout << "Passenger Capacity: " << current->capacity << '\n';
        cout << "Current Passengers: " << current->passengers << '\n';
        cout << "Available Seats: "
             << current->capacity - current->passengers << '\n';
    }
    void reverseTrain() {
        if (current == nullptr || current->next == current) {
            return;
        }
        Coach* temp = current;

        do {
            Coach* nextNode = temp->next;
            temp->next = temp->prev;
            temp->prev = nextNode;
            temp = nextNode;
        } while (temp != current);

        current = current->next;
    }
};
int main() {
    Train train;
    int numberOfCoaches;

    cout << "Enter number of coaches: ";
    cin >> numberOfCoaches;

    for (int i = 0; i < numberOfCoaches; i++) {
        int number, capacity, passengers;
        string type;
        cout << "\nCoach " << i + 1 << '\n';
        cout << "Enter Coach Number: ";
        cin >> number;
        cin.ignore();

        cout << "Enter Coach Type: ";
        getline(cin, type);
        cout << "Enter Passenger Capacity: ";
        cin >> capacity;
        cout << "Enter Current Passengers: ";
        cin >> passengers;
        train.addCoach(number, type, capacity, passengers);
    }
    int choice;
    do {
        cout << "\n1. Add Coach\n";
        cout << "2. Insert Coach\n";
        cout << "3. Remove Coach\n";
        cout << "4. Move Forward\n";
        cout << "5. Move Backward\n";
        cout << "6. Display Train Clockwise\n";
        cout << "7. Display Train Anti-clockwise\n";
        cout << "8. Search Coach\n";
        cout << "9. Find Maximum Available Capacity\n";
        cout << "10. Display Current Coach\n";
        cout << "11. Reverse Train Direction\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int number, capacity, passengers;
            string type;

            if (choice == 2) {
                int afterNumber;
                cout << "Insert after Coach Number: ";
                cin >> afterNumber;

                cout << "Enter Coach Number: ";
                cin >> number;
                cin.ignore();

                cout << "Enter Coach Type: ";
                getline(cin, type);

                cout << "Enter Passenger Capacity: ";
                cin >> capacity;

                cout << "Enter Current Passengers: ";
                cin >> passengers;

                if (!train.insertCoach(
                        afterNumber,
                        number,
                        type,
                        capacity,
                        passengers)) {
                    cout << "Coach not found.\n";
                }
            }
            else {
                cout << "Enter Coach Number: ";
                cin >> number;
                cin.ignore();

                cout << "Enter Coach Type: ";
                getline(cin, type);

                cout << "Enter Passenger Capacity: ";
                cin >> capacity;

                cout << "Enter Current Passengers: ";
                cin >> passengers;

                train.addCoach(
                    number,
                    type,
                    capacity,
                    passengers
                );
            }
        }
        else if (choice == 3) {
            int number;

            cout << "Enter Coach Number: ";
            cin >> number;

            if (train.removeCoach(number)) {
                cout << "Coach removed.\n";
            } else {
                cout << "Coach not found.\n";
            }
        }
        else if (choice == 4) {
            train.moveForward();
        }
        else if (choice == 5) {
            train.moveBackward();
        }
        else if (choice == 6) {
            train.displayClockwise();
        }
        else if (choice == 7) {
            train.displayAntiClockwise();
        }
        else if (choice == 8) {
            int number;

            cout << "Enter Coach Number: ";
            cin >> number;

            train.searchCoach(number);
        }
        else if (choice == 9) {
            train.maximumAvailableCapacity();
        }
        else if (choice == 10) {
            train.displayCurrent();
        }
        else if (choice == 11) {
            train.reverseTrain();
            cout << "Train direction reversed.\n";
        }
        else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}