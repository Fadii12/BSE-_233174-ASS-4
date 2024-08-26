#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Item {
protected:
    int itemID;
    string title;
    bool availability;

public:
    Item(int id, string t, bool avail) {
        itemID = id;
        title = t;
        availability = avail;
    }

    virtual void getItemDetails() const = 0;
    virtual bool checkAvailability() const {
        return availability;
    }
    virtual void checkOut() = 0;
    virtual void checkIn() = 0;
};

class Book : public Item {
private:
    string author;
    string ISBN;

public:
    Book(int id, string t, bool avail, string a, string isbn)
        : Item(id, t, avail) {
        author = a;
        ISBN = isbn;
    }

    void getItemDetails() const override {
        cout << "Book ID: " << itemID << "Title: " << title << " Author: " << author << " ISBN: " << ISBN << " Available: " << (availability ? "Yes" : "No") << endl;
    }

    void checkOut() override {
        if (availability) {
            availability = false;
            cout << "Book checked out successfully." << endl;
        }
        else {
            cout << "Book is not available." << endl;
        }
    }

    void checkIn() override {
        availability = true;
        cout << "Book checked in successfully." << endl;
    }
};

class Journal : public Item {
private:
    string publisher;
    int issueNumber;

public:
    Journal(int id, string t, bool avail, string p, int issue)
        : Item(id, t, avail) {

        publisher = p;
        issueNumber = issue;
    }

    void getItemDetails() const override {
        cout << "Journal ID: " << itemID << " Title: " << title << " Publisher: " << publisher << " Issue Number: " << issueNumber << " Available: " << (availability ? "Yes" : "No") << endl;
    }

    void checkOut() override {
        if (availability) {
            availability = false;
            cout << "Journal checked out successfully." << endl;
        }
        else {
            cout << "Journal is not available." << endl;
        }
    }

    void checkIn() override {
        availability = true;
        cout << "Journal checked in successfully." << endl;
    }
};

class Member {
private:
    int memberID;
    string name;
    string contactInformation;
    int loanLimit;
    vector<int> loanedItems;

public:
    Member(int id, string n, string contact, int limit)
        : memberID(id), name(n) {

        contactInformation = contact;
        loanLimit = limit;
    }

    void borrowItem(int itemID) {
        if (loanedItems.size() < loanLimit) {
            loanedItems.push_back(itemID);
            cout << name << " borrowed item with ID: " << itemID << endl;
        }
        else {
            cout << "Loan limit reached!" << endl;
        }
    }

    void returnItem(int itemID) {
        auto it = find(loanedItems.begin(), loanedItems.end(), itemID);
        if (it != loanedItems.end()) {
            loanedItems.erase(it);
            cout << name << " returned item with ID: " << itemID << endl;
        }
        else {
            cout << "Item not found in loaned items." << endl;
        }
    }

    void getLoanHistory() const {
        cout << name << "'s Loaned Items: ";
        for (int id : loanedItems) {
            cout << id << " ";
        }
        cout << endl;
    }
};

class Loan {
private:
    int loanID;
    Item* item;
    Member* member;
    string dueDate;
    string actualReturnDate;

public:
    Loan(int id, Item* it, Member* mem, string due)
    {

        loanID = id;
        item = it;
        member = mem;
        dueDate = due;
    }

    void calculateFine() const {
        cout << "Calculating fine based on overdue days." << endl;
    }
};

int main() {

    Book book1(1, "The C++ Programming Language", true, "ALIAN Asmo", "1234567890");
    Journal journal1(2, "Computer Science Journal", true, "Tech Publication ", 101);

    Member member1(1, "John Doe", "johndoe@example.com", 3);

    book1.getItemDetails();
    journal1.getItemDetails();

    member1.borrowItem(book1.checkAvailability() ? 1 : 0);
    book1.checkOut();
    member1.getLoanHistory();

    member1.returnItem(1);
    book1.checkIn();
    member1.getLoanHistory();

    return 0;
}