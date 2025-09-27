#include <cmath>
#include <iostream>

typedef struct {
    std::string name;
    std::string surname;
    std::string age;
    std::string city;
} phone_book;

bool less(phone_book human_1, phone_book human_2, std::string field)
{
    if (field == "name")
        return human_1.name < human_2.name;
    else if (field == "age")
        return human_1.age < human_2.age;
}

void create_array_index(
        phone_book arr[], int index[], int size, std::string field)
{
    int i, j, temp;
    for (i = 0; i < size; i++)
        index[i] = i;

    for (i = 1; i < size; i++) {
        temp = index[i];
        j = i - 1;
        while (j >= 0 && less(arr[temp], arr[index[j]], field)) {
            index[j + 1] = index[j];
            j--;
        }
        index[j + 1] = temp;
    }
}

void binary_search(
        phone_book arr[],
        int index[],
        int size,
        std::string key,
        std::string field)
{
    int left = 0, right = size - 1;
    bool found = false;

    if (field == "name") {
        while (left < right) {
            int middle = floor((left + right) / 2);
            if (arr[index[middle]].name < key)
                left = middle + 1;
            else
                right = middle;
        }
        if (arr[index[right]].name == key) {
            found = true;
            std::cout << "Found abonent: " << arr[index[right]].name << " "
                      << arr[index[right]].surname << ", "
                      << arr[index[right]].age << " year, "
                      << arr[index[right]].city << std::endl;
            int i1 = right - 1;
            while (i1 >= 0 && arr[index[i1]].name == key) {
                std::cout << "Found abonent: " << arr[index[i1]].name << " "
                          << arr[index[i1]].surname << ", "
                          << arr[index[i1]].age << " year, "
                          << arr[index[i1]].city << std::endl;
                i1--;
            }
            int i2 = right + 1;
            while (i2 < size && arr[index[i2]].name == key) {
                std::cout << "Found abonent: " << arr[index[i2]].name << " "
                          << arr[index[i2]].surname << ", "
                          << arr[index[i2]].age << " year, "
                          << arr[index[i2]].city << std::endl;
                i2++;
            }
        }
    }

    if (field == "age") {
        while (left < right) {
            int middle = floor((left + right) / 2);
            if (arr[index[middle]].age < key)
                left = middle + 1;
            else
                right = middle;
        }
        if (arr[index[right]].age == key) {
            found = true;
            std::cout << "Found abonent: " << arr[index[right]].name << " "
                      << arr[index[right]].surname << ", "
                      << arr[index[right]].age << " year, "
                      << arr[index[right]].city << std::endl;
            int i1 = right - 1;
            while (i1 >= 0 && arr[index[i1]].age == key) {
                std::cout << "Found abonent: " << arr[index[i1]].name << " "
                          << arr[index[i1]].surname << ", "
                          << arr[index[i1]].age << " year, "
                          << arr[index[i1]].city << std::endl;
                i1--;
            }
            int i2 = right + 1;
            while (i2 < size && arr[index[i2]].age == key) {
                std::cout << "Found abonent: " << arr[index[i2]].name << " "
                          << arr[index[i2]].surname << ", "
                          << arr[index[i2]].age << " year, "
                          << arr[index[i2]].city << std::endl;
                i2++;
            }
        }
    }
    if (!found)
        std::cout << "Not found abonent!" << std::endl;
}

void output_structure(phone_book arr[], int size)
{
    for (int i = 0; i < size; i++)
        std::cout << i + 1 << ". " << arr[i].name << " " << arr[i].surname
                  << ", " << arr[i].age << " year, " << arr[i].city << std::endl;
}

void output_sort_structure(phone_book arr[], int index[], int size)
{
    for (int i = 0; i < size; i++)
        std::cout << index[i] + 1 << ". " << arr[index[i]].name << " "
                  << arr[index[i]].surname << ", " << arr[index[i]].age
                  << " year, " << arr[index[i]].city << std::endl;
    std::cout << std::endl;
}

int main()
{
    int size = 4;
    int index_name[size];
    int index_age[size];
    std::string name, age;

    phone_book arr[]
            = {{"Danil", "Safonov", "18", "Iskitim"},
               {"Andrey", "Safonov", "19", "Kemerovo"},
               {"Vladimir", "Putin", "21", "Kurundus"},
               {"Alexsey", "Ivanov", "20", "Novosibirsk"}};

    create_array_index(arr, index_name, size, "name");
    create_array_index(arr, index_age, size, "age");

    std::cout << "do sort:" << std::endl;
    output_structure(arr, size);

    std::cout << "\nsort last name:" << std::endl;
    output_sort_structure(arr, index_name, size);

    std::cout << "sort year:" << std::endl;
    output_sort_structure(arr, index_age, size);

    std::cout << "Write Name: ";
    std::cin >> name;
    binary_search(arr, index_name, size, name, "name");

    std::cout << "Write year: ";
    std::cin >> age;
    binary_search(arr, index_age, size, age, "age");

    return 0;
}
