#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <limits> // Для std::numeric_limits

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Структура записи
struct Record {
    char author[12];
    char title[32];
    char publisher[16];
    short year;
    short pages;

    void print() const {
        cout << "Author: " << author
            << ", Title: " << title
            << ", Publisher: " << publisher
            << ", Year: " << year
            << ", Pages: " << pages << endl;
    }

    short getYear() const {
        return year;
    }
};

// Структура элемента для связного списка (очереди)
struct tLE {
    const Record* record;
    tLE* next;
};

// Класс собственной очереди на основе связного списка
class CustomQueue {
private:
    tLE* head;
    tLE* tail;

public:
    // Конструктор
    CustomQueue() : head(nullptr), tail(nullptr) {}

    // Деструктор 
    ~CustomQueue() {
        while (!empty()) {
            pop();
        }
    }

    // Добавление элемента в конец очереди
    void push(const Record* record) {
        tLE* newNode = new tLE;
        newNode->record = record; // Связывание с конкретной записью
        newNode->next = nullptr;
        if (tail != nullptr) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }
        tail = newNode;
    }

    // Проверка, пуста ли очередь
    bool empty() const {
        return head == nullptr;
    }

    // Получение первого элемента без удаления
    const Record* front() const {
        if (!empty()) {
            return head->record;
        }
        return nullptr;
    }

    // Удаление первого элемента
    void pop() {
        if (!empty()) {
            tLE* temp = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
        }
    }

    // Очистка всей очереди
    void queue_clear() {
        while (!empty()) {
            pop();
        }
    }
};

// Собственная функция swap для указателей на Record
void mySwap(Record*& a, Record*& b) {
    Record* temp = a;
    a = b;
    b = temp;
}

// Функция загрузки базы данных из файла
vector<Record> loadDatabase(const string& filename) {
    vector<Record> records;
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return records;
    }

    while (file) {
        Record record;
        file.read(reinterpret_cast<char*>(&record), sizeof(Record));
        if (file) {
            records.push_back(record); // Загрузка записи в вектор 
        }
    }

    file.close();
    return records;
}

// Функция постраничного вывода данных через указатели
void paginatePointers(const vector<Record*>& record_ptrs, int page_size = 20) {
    setlocale(LC_ALL, "866");

    int total_pages = (record_ptrs.size() + page_size - 1) / page_size;
    for (int i = 0; i < total_pages; ++i) {
        cout << "Pages " << (i + 1) << "/" << total_pages << endl;
        for (int j = i * page_size; j < (i + 1) * page_size && j < record_ptrs.size(); ++j) {
            record_ptrs[j]->print();
        }
        cout << "Press Enter to continue or 'q' to exit: ";
        string input;
        getline(cin, input);
        if (input == "q") break;
    }
}

// Функция пирамидальной сортировки указателей по году издания
void heapifyPointers(vector<Record*>& record_ptrs, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && record_ptrs[left]->getYear() > record_ptrs[largest]->getYear())
        largest = left;

    if (right < n && record_ptrs[right]->getYear() > record_ptrs[largest]->getYear())
        largest = right;

    if (largest != i) {
        mySwap(record_ptrs[i], record_ptrs[largest]);
        heapifyPointers(record_ptrs, n, largest);
    }
}

void heapsortPointers(vector<Record*>& record_ptrs) {
    int n = record_ptrs.size();
    // Построение кучи (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyPointers(record_ptrs, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        mySwap(record_ptrs[0], record_ptrs[i]);
        heapifyPointers(record_ptrs, i, 0);
    }
}

// Исправленная функция бинарного поиска согласно предоставленному псевдокоду
int binarySearchLeftmost(const vector<Record*>& records, short year) {
    if (records.empty()) return -1;

    size_t left = 0; // В C++ индексация начинается с 0
    size_t right = records.size() - 1;

    // Выполняем поиск, пока left < right
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        short midYear = records[mid]->getYear();

        if (midYear < year) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    // После завершения цикла left и right указывают на возможную позицию
    if (records[right]->getYear() == year) {
        return static_cast<int>(right); // Приведение к int, если необходимо
    }
    else {
        return -1; // Элемент не найден
    }
}

// Исправленная функция бинарного поиска для нахождения всех записей с заданным годом
CustomQueue binarySearchYearAll(const vector<Record*>& records, short year) {
    CustomQueue result;
    int index = binarySearchLeftmost(records, year);

    if (index == -1) {
        return result; // Возвращаем пустую очередь, если записи не найдены
    }

    // Добавляем найденную запись
    result.push(records[index]);

    // Ищем все записи с тем же годом справа от найденного индекса
    size_t i = static_cast<size_t>(index) + 1;
    while (i < records.size() && records[i]->getYear() == year) {
        result.push(records[i]);
        i++;
    }

    return result;
}


// Функция вывода очереди найденных записей
void printQueue(CustomQueue& record_queue) {
    while (!record_queue.empty()) {
        const Record* record = record_queue.front();
        if (record != nullptr) {
            record->print();
        }
        record_queue.pop();
    }
}

int main() {
    // Установка локали для корректного отображения символов
    setlocale(LC_ALL, "866");

    string filename = "testBase1.dat";

    // 1. Загрузка базы данных
    vector<Record> records = loadDatabase(filename);

    if (records.empty()) {
        cerr << "The database is empty or has not been loaded." << endl;
        return 1;
    }

    // 2. Создание индексного массива указателей на записи
    vector<Record*> record_ptrs;
    for (size_t i = 0; i < records.size(); ++i) {
        record_ptrs.push_back(&records[i]);
    }

    // 3. Постраничный вывод данных из исходного массива записей
    cout << "The database is loaded. Output of 20 entries per page from original records:" << endl;
    paginatePointers(record_ptrs);

    // 4. Пирамидальная сортировка указателей по году издания
    cout << "Data ordering by year ..." << endl;
    heapsortPointers(record_ptrs);

    // 5. Постраничный вывод данных из отсортированного массива указателей
    cout << "Output of 20 entries per page from sorted pointer array:" << endl;
    paginatePointers(record_ptrs);

    // 6. Поиск по году издания через указатели с использованием бинарного поиска
    short year;
    cout << "Enter the year of publication to search for: ";

    // Проверка корректности ввода года
    while (!(cin >> year)) {
        cin.clear();
        cout << "Invalid input. Please enter a valid year: ";
    }
    cin.ignore();

    CustomQueue result_queue = binarySearchYearAll(record_ptrs, year);

    if (!result_queue.empty()) {
        cout << "Records with the year of publication '" << year << "' have been found:" << endl;
        printQueue(result_queue);  // Выводим записи из очереди
    }
    else {
        cout << "Records with the year of publication '" << year << "' not found." << endl;
    }

    return 0;
}
