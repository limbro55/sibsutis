#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Catalog {
    long phone;
    string name;
    string surname;
    string club;
};

bool lesss(struct Catalog x, struct Catalog y) {
    if (x.name < y.name) {
        return true;
    } else if (x.name == y.name) {
        return x.surname < y.surname;
    }
    return false;
}

bool lesssC(struct Catalog x, struct Catalog y) {
    if (x.club > y.club) {
        return true;
    } else if (x.club == y.club) {
        return x.surname > y.surname;
    }
    return false;
}

void SelectSort(struct Catalog contacts[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int mini = i;
        for (int j = i + 1; j < n; ++j) {
            if (lesss(contacts[j], contacts[mini])) {
                mini = j;
            }
        }
        struct Catalog temp;
        temp = contacts[mini];
        contacts[mini] = contacts[i];
        contacts[i] = temp;
    }
}

void SelectSortB(struct Catalog contacts[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int mini = i;
        for (int j = i + 1; j < n; ++j) {
            if (lesss(contacts[j], contacts[mini]) == 0) {
                mini = j;
            }
        }
        struct Catalog temp;
        temp = contacts[mini];
        contacts[mini] = contacts[i];
        contacts[i] = temp;
    }
}

void SelectSortC(struct Catalog contacts[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int mini = i;
        for (int j = i + 1; j < n; ++j) {
            if (lesssC(contacts[j], contacts[mini]) == 0) {
                mini = j;
            }
        }
        struct Catalog temp;
        temp = contacts[mini];
        contacts[mini] = contacts[i];
        contacts[i] = temp;
    }
}

void SelectSortD(struct Catalog contacts[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int maxi = i;
        for (int j = i + 1; j < n; ++j) {
            if (lesss(contacts[j], contacts[maxi])) {
                maxi = j;
            }
        }
        struct Catalog temp;
        temp = contacts[maxi];
        contacts[maxi] = contacts[i];
        contacts[i] = temp;
    }
}

void PrintMas(Catalog a[], int b[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[b[i]].name << " " << a[b[i]].surname << " " << a[b[i]].phone << " " << a[b[i]].club << endl;
    }
    cout << endl;
}

int main() {
    int n = 5;
    Catalog catalog[] = {
        {89619207846, "Danil", "Safonov", "Alecsandrovich"},
        {89699222795, "Nicolay", "Ivanovich", "Spartak"},
        {89159084663, "Denis", "Krilov", "Igorevich"},
        {89192736469, "Nikita", "Korotkov", "Sibiria"},
        {89299268512, "Vladimir", "Vladimirovich", "Putin"}
    };

    int b[n];
    for (int i = 0; i < n; i++) {
        b[i] = i;
    }

    int check;
    PrintMas(catalog, b, n);
    cout << "By what parameters are we sorting:\n1) First Name+Last Name\n2) First Name+Last Name(decreasing)\n3) Club+Surname\n4) Club+Surname(decreasing)\n";
    cin >> check;
    cout << endl;

    switch (check) {
        case 1:
            SelectSort(catalog, n);
            PrintMas(catalog, b, n);
            break;
        
        case 2:
            SelectSortB(catalog, n);
            PrintMas(catalog, b, n);
            break;
        
        case 3:
            SelectSortC(catalog, n);
            PrintMas(catalog, b, n);
            break;
            
        case 4:
            SelectSortD(catalog, n);
            PrintMas(catalog, b, n);
            break;
            
            
        default:
            cout << "ERROR\n";
            break;
    }

    return 0;
}
