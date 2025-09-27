#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Contact {
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
};

bool compareContacts(const Contact& a, const Contact& b) {
    if (a.lastName != b.lastName) {
        return a.lastName < b.lastName;
    } else {
        return a.phoneNumber < b.phoneNumber;
    }
}

void printContacts(const std::vector<Contact>& contacts) {
    std::cout << "Contacts:\n";
    for (const auto& contact : contacts) {
        std::cout << "Name: " << contact.firstName << " " << contact.lastName << "\n";
        std::cout << "Phone number: " << contact.phoneNumber << "\n\n";
    }
}

int main() {
    std::vector<Contact> contacts = {
        {"Safonov", "Danil", "123456"},
        {"Putin", "Vladimir", "987654"},
        {"Ivan", "Ivanov", "456789"},
        {"Safonov","Andrey","462856"}
    };

    std::cout << "Default sorting by last name and phone number:\n";
    std::sort(contacts.begin(), contacts.end(), compareContacts);
    printContacts(contacts);

    char changeKey;
    std::cout << "Do you want to change the sorting key? (y/n): ";
    std::cin >> changeKey;

    if (changeKey == 'y') {
        // Custom sorting keys
        std::cout << "Enter first sorting key (1 - First Name, 2 - Last Name, 3 - Phone Number): ";
        int firstKey;
        std::cin >> firstKey;

        std::cout << "Enter second sorting key (1 - First Name, 2 - Last Name, 3 - Phone Number): ";
        int secondKey;
        std::cin >> secondKey;

        // Update comparison function based on user input
        bool (*customCompare)(const Contact&, const Contact&) = nullptr;
        if (firstKey == 1 && secondKey == 2) {
            customCompare = [](const Contact& a, const Contact& b) {
                if (a.firstName != b.firstName) {
                    return a.firstName < b.firstName;
                } else {
                    return a.lastName < b.lastName;
                }
            };
        } else if (firstKey == 2 && secondKey == 3) {
            customCompare = [](const Contact& a, const Contact& b) {
                if (a.lastName != b.lastName) {
                    return a.lastName < b.lastName;
                } else {
                    return a.phoneNumber < b.phoneNumber;
                }
            };
        } else if (firstKey == 1 && secondKey == 3) {
            customCompare = [](const Contact& a, const Contact& b) {
                if (a.firstName != b.firstName) {
                    return a.firstName < b.firstName;
                } else {
                    return a.phoneNumber < b.phoneNumber;
                }
            };
        }

        if (customCompare) {
            std::sort(contacts.begin(), contacts.end(), customCompare);
            std::cout << "\nContacts after custom sorting:\n";
            printContacts(contacts);
        } else {
            std::cout << "Invalid sorting keys entered.\n";
        }
    }

    return 0;
}
