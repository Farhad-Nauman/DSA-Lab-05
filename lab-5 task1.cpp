#include <iostream>
#include <string>
using namespace std;

struct Tab {
    int id;
    string title;
    string url;
    Tab* next;
    Tab* prev;

    Tab(int i, string t, string u) {
        id = i;
        title = t;
        url = u;
        next = this;
        prev = this;
    }
};
class BrowserTabs {
private:
    Tab* current;
public:
    BrowserTabs() {
        current = nullptr;
    }
    ~BrowserTabs() {
        while (current != nullptr) {
            closeCurrent();
        }
    }
    void openTab(int id, string title, string url) {
        Tab* newTab = new Tab(id, title, url);
        if (current == nullptr) {
            current = newTab;
            return;
        }
        newTab->next = current->next;
        newTab->prev = current;
        current->next->prev = newTab;
        current->next = newTab;
    }
    void closeCurrent() {
        if (current == nullptr) {
            cout << "No tabs are open.\n";
            return;
        }
        if (current->next == current) {
            delete current;
            current = nullptr;
            return;
        }
        Tab* temp = current;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
        delete temp;
    }
    void moveNext() {
        if (current == nullptr) {
            cout << "No tabs are open.\n";
            return;
        }
        current = current->next;
    }
    void movePrevious() {
        if (current == nullptr) {
            cout << "No tabs are open.\n";
            return;
        }
        current = current->prev;
    }
    void displayCurrent() {
        if (current == nullptr) {
            cout << "No tabs are open.\n";
            return;
        }
        cout << "\nCurrent Tab\n";
        cout << "ID: " << current->id << '\n';
        cout << "Title: " << current->title << '\n';
        cout << "URL: " << current->url << '\n';
    }
    void displayForward() {
        if (current == nullptr) {
            cout << "No tabs are open.\n";
            return;
        }
        Tab* temp = current;
        do {
            cout << "ID: " << temp->id
                 << " | Title: " << temp->title
                 << " | URL: " << temp->url << '\n';

            temp = temp->next;
        } while (temp != current);
    }
    void displayBackward() {
        if (current == nullptr) {
            cout << "No tabs are open.\n";
            return;
        }
        Tab* temp = current;
        do {
            cout << "ID: " << temp->id
                 << " | Title: " << temp->title
                 << " | URL: " << temp->url << '\n';

            temp = temp->prev;
        } while (temp != current);
    }
    void searchTab(int id) {
        if (current == nullptr) {
            cout << "No tabs are open.\n";
            return;
        }
        Tab* temp = current;

        do {
            if (temp->id == id) {
                cout << "\nTab Found\n";
                cout << "ID: " << temp->id << '\n';
                cout << "Title: " << temp->title << '\n';
                cout << "URL: " << temp->url << '\n';
                return;
            }

            temp = temp->next;
        } while (temp != current);

        cout << "Tab not found.\n";
    }
};
int main() {
    BrowserTabs browser;
    int choice;

    do {
        cout << "\n1. Open New Tab\n";
        cout << "2. Close Current Tab\n";
        cout << "3. Move Next\n";
        cout << "4. Move Previous\n";
        cout << "5. Display Current Tab\n";
        cout << "6. Display All Tabs Forward\n";
        cout << "7. Display All Tabs Backward\n";
        cout << "8. Search Tab\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string title, url;

            cout << "Enter Tab ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Website Title: ";
            getline(cin, title);

            cout << "Enter URL: ";
            getline(cin, url);

            browser.openTab(id, title, url);
        }
        else if (choice == 2) {
            browser.closeCurrent();
        }
        else if (choice == 3) {
            browser.moveNext();
        }
        else if (choice == 4) {
            browser.movePrevious();
        }
        else if (choice == 5) {
            browser.displayCurrent();
        }
        else if (choice == 6) {
            browser.displayForward();
        }
        else if (choice == 7) {
            browser.displayBackward();
        }
        else if (choice == 8) {
            int id;
            cout << "Enter Tab ID: ";
            cin >> id;
            browser.searchTab(id);
        }
        else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}