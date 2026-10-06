#include <iostream>
#include <string>
using namespace std;

struct Photo {
    int id;
    string name;
    string date;
    string location;
    Photo* next;
    Photo* prev;
    Photo(int i, string n, string d, string l) {
        id = i;
        name = n;
        date = d;
        location = l;
        next = this;
        prev = this;
    }
};
class PhotoAlbum {
private:
    Photo* current;
public:
    PhotoAlbum() {
        current = nullptr;
    }
    ~PhotoAlbum() {
        while (current != nullptr) {
            removeCurrent();
        }
    }
    void addPhoto(int id, string name, string date, string location) {
        Photo* newPhoto = new Photo(id, name, date, location);

        if (current == nullptr) {
            current = newPhoto;
            return;
        }
        Photo* last = current->prev;
        newPhoto->next = current;
        newPhoto->prev = last;
        last->next = newPhoto;
        current->prev = newPhoto;
    }
    void insertAfterCurrent(int id, string name, string date, string location) {
        if (current == nullptr) {
            addPhoto(id, name, date, location);
            return;
        }
        Photo* newPhoto = new Photo(id, name, date, location);
        newPhoto->next = current->next;
        newPhoto->prev = current;
        current->next->prev = newPhoto;
        current->next = newPhoto;
    }
    bool removePhoto(int id) {
        if (current == nullptr) {
            return false;
        }

        Photo* temp = current;

        do {
            if (temp->id == id) {
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
    void removeCurrent() {
        if (current == nullptr) {
            return;
        }

        if (current->next == current) {
            delete current;
            current = nullptr;
            return;
        }
        Photo* temp = current;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
        delete temp;
    }
    void moveNext() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }
        current = current->next;
    }
    void movePrevious() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }
        current = current->prev;
    }
    void displayForward() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }
        Photo* temp = current;
        do {
            cout << "ID: " << temp->id
                 << " | Name: " << temp->name
                 << " | Date: " << temp->date
                 << " | Location: " << temp->location << '\n';

            temp = temp->next;
        } while (temp != current);
    }
    void displayBackward() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }
        Photo* temp = current;
        do {
            cout << "ID: " << temp->id
                 << " | Name: " << temp->name
                 << " | Date: " << temp->date
                 << " | Location: " << temp->location << '\n';

            temp = temp->prev;
        } while (temp != current);
    }
    void searchPhoto(int id) {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }
        Photo* temp = current;
        do {
            if (temp->id == id) {
                cout << "\nPhoto Found\n";
                cout << "ID: " << temp->id << '\n';
                cout << "Name: " << temp->name << '\n';
                cout << "Date: " << temp->date << '\n';
                cout << "Location: " << temp->location << '\n';
                return;
            }

            temp = temp->next;
        } while (temp != current);

        cout << "Photo not found.\n";
    }
    void countPhotos() {
        if (current == nullptr) {
            cout << "Total Photos: 0\n";
            return;
        }

        int count = 0;
        Photo* temp = current;

        do {
            count++;
            temp = temp->next;
        } while (temp != current);

        cout << "Total Photos: " << count << '\n';
    }
};
int main() {
    PhotoAlbum album;
    int numberOfPhotos;
    cout << "Enter number of photos: ";
    cin >> numberOfPhotos;
    for (int i = 0; i < numberOfPhotos; i++) {
        int id;
        string name, date, location;

        cout << "\nPhoto " << i + 1 << '\n';

        cout << "Enter Photo ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Photo Name: ";
        getline(cin, name);

        cout << "Enter Date Taken: ";
        getline(cin, date);

        cout << "Enter Location: ";
        getline(cin, location);

        album.addPhoto(id, name, date, location);
    }
    int choice;
        do {
        cout << "\n1. Add Photo\n";
        cout << "2. Insert Photo After Current\n";
        cout << "3. Remove Photo\n";
        cout << "4. Remove Current Photo\n";
        cout << "5. Move Next\n";
        cout << "6. Move Previous\n";
        cout << "7. Display Album Forward\n";
        cout << "8. Display Album Backward\n";
        cout << "9. Search Photo\n";
        cout << "10. Count Photos\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int id;
            string name, date, location;

            cout << "Enter Photo ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Photo Name: ";
            getline(cin, name);

            cout << "Enter Date Taken: ";
            getline(cin, date);

            cout << "Enter Location: ";
            getline(cin, location);

            if (choice == 1) {
                album.addPhoto(id, name, date, location);
            } else {
                album.insertAfterCurrent(id, name, date, location);
            }
        }
        else if (choice == 3) {
            int id;
            cout << "Enter Photo ID: ";
            cin >> id;

            if (album.removePhoto(id)) {
                cout << "Photo removed.\n";
            } else {
                cout << "Photo not found.\n";
            }
        }
        else if (choice == 4) {
            album.removeCurrent();
        }
        else if (choice == 5) {
            album.moveNext();
        }
        else if (choice == 6) {
            album.movePrevious();
        }
        else if (choice == 7) {
            album.displayForward();
        }
        else if (choice == 8) {
            album.displayBackward();
        }
        else if (choice == 9) {
            int id;
            cout << "Enter Photo ID: ";
            cin >> id;
            album.searchPhoto(id);
        }
        else if (choice == 10) {
            album.countPhotos();
        }
        else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}