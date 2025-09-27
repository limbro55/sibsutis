#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <limits>
#include<algorithm>
#include<unordered_map>
#include <conio.h>
#include <iomanip>
#include<cmath>


#ifdef _WIN32
#include <windows.h>
#endif

int VR = 1, HR = 1;

using namespace std;


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

    short getPages() const {
        return pages;
    }
};


struct tLE {
    const Record* record;
    tLE* next;
};


class CustomQueue {
private:
    tLE* head;
    tLE* tail;

public:
    CustomQueue() : head(nullptr), tail(nullptr) {}

    ~CustomQueue() {
        while (!empty()) {
            pop();
        }
    }

    void push(const Record* record) {
        tLE* newNode = new tLE;
        newNode->record = record;
        newNode->next = nullptr;
        if (tail != nullptr) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }
        tail = newNode;
    }

    bool empty() const {
        return head == nullptr;
    }

    const Record* front() const {
        if (!empty()) {
            return head->record;
        }
        return nullptr;
    }

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

    void queue_clear() {
        while (!empty()) {
            pop();
        }
    }
};

void mySwap(Record*& a, Record*& b) {
    Record* temp = a;
    a = b;
    b = temp;
}


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
            records.push_back(record); 
        }
    }

    file.close();
    return records;
}


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
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyPointers(record_ptrs, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        mySwap(record_ptrs[0], record_ptrs[i]);
        heapifyPointers(record_ptrs, i, 0);
    }
}

int binarySearchLeftmost(const vector<Record*>& records, short year) {
    if (records.empty()) return -1;

    size_t left = 0;
    size_t right = records.size() - 1;

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

    if (records[right]->getYear() == year) {
        return static_cast<int>(right);
    }
    else {
        return -1;
    }
}

CustomQueue binarySearchYearAll(const vector<Record*>& records, short year) {
    CustomQueue result;
    int index = binarySearchLeftmost(records, year);

    if (index == -1) {
        return result; 
    }

    result.push(records[index]);

    size_t i = static_cast<size_t>(index) + 1;
    while (i < records.size() && records[i]->getYear() == year) {
        result.push(records[i]);
        i++;
    }

    return result;
}

void printQueue(CustomQueue& record_queue) {
    int count = 1;
    while (!record_queue.empty()) {
        const Record* record = record_queue.front();
        if (record != nullptr) {
            cout << count++ << ". ";
            record->print();
        }
        record_queue.pop();
    }
}

struct Vertex {
    const Record* data;
    Vertex* left;
    Vertex* right;
    Vertex* next;
    int balance;

    Vertex(const Record* record)
        : data(record), left(nullptr), right(nullptr), next(nullptr), balance(0) {}
};

void B2INSERT(const Record* data, Vertex*& p) {
    if (p == nullptr) {
        p = new Vertex(data);
        VR = 1;
    }
    else if (data->getPages() < p->data->getPages()) {
        B2INSERT(data, p->left);
        if (VR == 1) {
            if (p->balance == 0) {
                Vertex* q = p->left;
                p->left = q->right;
                q->right = p;
                p = q;
                q->balance = 1;
                VR = 0;
                HR = 1;
            }
            else {
                p->balance = 0;
                VR = 1;
                HR = 0;
            }
        }
        else {
            HR = 0;
        }
    }
    else if (data->getPages() > p->data->getPages()) { 
        B2INSERT(data, p->right);
        if (VR == 1) {
            p->balance = 1;
            HR = 1;
            VR = 0;
        }
        else if (HR == 1) {
            if (p->balance == 1) {
                Vertex* q = p->right;
                p->balance = 0;
                q->balance = 0;
                p->right = q->left;
                q->left = p;
                p = q;
                VR = 1;
                HR = 0;
            }
            else {
                HR = 0;
            }
        }
    }
    else { 
        Vertex* current = p;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Vertex(data);
    }
}


Vertex* buildBalancedTreeFromQueue(CustomQueue& recordQueue) {
    Vertex* root = nullptr;
    while (!recordQueue.empty()) {
        B2INSERT(recordQueue.front(), root);
        recordQueue.pop();
    }
    return root;
}


void printDBD(const Vertex* root, int& count) {
    if (root == nullptr) return;

    printDBD(root->left, count);
    const Vertex* current = root;
    while (current != nullptr) {
        cout << count++ << ". ";
        current->data->print();
        current = current->next;
    }

    printDBD(root->right, count);
}

const Vertex* searchInDBD(const Vertex* root, short pages) {
    if (root == nullptr) return nullptr;

    if (root->data->getPages() == pages) return root;
    if (pages < root->data->getPages())
        return searchInDBD(root->left, pages);
    else
        return searchInDBD(root->right, pages);
}

void printRecordsWithSamePages(const Vertex* node) {
    if (node == nullptr) {
        cout << "Запись с указанным количеством страниц не найдена." << endl;
        return;
    }

    const Vertex* current = node;
    int count = 1;
    while (current != nullptr) {
        cout << count++ << ". ";
        current->data->print();
        current = current->next;
    }
}


void deleteDBD(Vertex* root) {
    if (root == nullptr) return;

    deleteDBD(root->left);
    deleteDBD(root->right);

    Vertex* current = root;
    while (current != nullptr) {
        Vertex* temp = current;
        current = current->next;
        delete temp;
    }
}

struct Encoding {
    char character = 0;
    float probability = 0;
    int length = 0;
    string codeword;
};

void calculate_probabilities(
    const string& filename, vector<Encoding>& symbols)
{
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "The binary file could not opened for reading!"
            << endl;
        return;
    }

    unordered_map<char, float> frequency;
    int message_size = 0;
    char ch;
    while (file.get(ch)) {
        frequency[ch]++;
        message_size++;
    }

    for (const auto& pair : frequency) {
        Encoding symbol;
        symbol.character = pair.first;
        symbol.probability = (float)(pair.second) / message_size;
        symbols.push_back(symbol);
    }

    file.close();
}

void qsort(vector<Encoding>& symbols, int left, int right)
{
    Encoding x = symbols[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (symbols[i].probability > x.probability) {
            i++;
        }
        while (symbols[j].probability < x.probability) {
            j--;
        }

        if (i <= j) {
            Encoding temp = symbols[i];
            symbols[i] = symbols[j];
            symbols[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        qsort(symbols, left, j);
    }
    if (i < right) {
        qsort(symbols, i, right);
    }
}

int up(float*& P, int n, float q)
{
    int j = 0;

    for (int i = n - 2; i > 0; i--) {
        if (P[i - 1] <= q) {
            P[i] = P[i - 1];
        }
        else {
            j = i;
            break;
        }
    }

    P[j] = q;
    return j;
}

void down(Encoding*& symbols, int n, int j)
{
    string S = symbols[j].codeword;
    int L = symbols[j].length;

    for (int i = j; i <= n - 2; i++) {
        symbols[i].codeword = symbols[i + 1].codeword;
        symbols[i].length = symbols[i + 1].length;
    }

    symbols[n - 1].length = L + 1;

    symbols[n - 2].codeword = S + "0";

    symbols[n - 1].codeword = S + "1";
    symbols[n - 2].length = symbols[n - 1].length = L + 1;
}

void huffman_code(Encoding*& symbols, float*& P, int n)
{
    if (n == 2) {
        symbols[0].codeword = "0";
        symbols[0].length = 1;

        symbols[1].codeword = "1";
        symbols[1].length = 1;
    }
    else {
        float q = P[n - 2] + P[n - 1];
        int j = up(P, n, q);
        huffman_code(symbols, P, n - 1);
        down(symbols, n - 1, j);
    }
}

Encoding* huffman(Encoding* symbols, int alphabet_size)
{
    Encoding* code = new Encoding[alphabet_size];
    float* P = new float[alphabet_size];

    for (int i = 0; i < alphabet_size; i++) {
        code[i].character = symbols[i].character;
        code[i].probability = P[i] = symbols[i].probability;
    }

    huffman_code(code, P, alphabet_size);

    delete[] P;
    return code;
}

void print_codeword_table(Encoding* code, int alphabet_size)
{
    cout << left << setw(10) << "Symbol"
        << setw(15) << "Probability"
        << setw(15) << "Codeword"
        << setw(15) << "Length" << endl;

    for (int i = 0; i < alphabet_size; i++) {
        cout << left << setw(10) << code[i].character
            << setw(15) << code[i].probability
            << setw(15) << code[i].codeword
            << setw(15) << code[i].length << endl;
    }
}

float entropy(Encoding* code, int alphabet_size)
{
    float answer = 0;

    for (int i = 0; i < alphabet_size; i++) {
        answer += (code[i].probability * log2(code[i].probability));
    }

    return -answer;
}

float average_codeword_length(Encoding* code, int alphabet_size)
{
    float answer = 0;

    for (int i = 0; i < alphabet_size; i++) {
        answer += code[i].length * code[i].probability;
    }

    return answer;
}

float code_redundancy(Encoding* code, int alphabet_size)
{
    return average_codeword_length(code, alphabet_size)
        - entropy(code, alphabet_size);
}

bool craft_inequality(Encoding* code, int alphabet_size)
{
    float sum = 0;

    for (int i = 0; i < alphabet_size; i++) {
        sum += pow(2, -code[i].length);
    }

    return sum <= 1;
}

int main() {
    setlocale(LC_ALL, "866");
    string filename = "testBase1.dat";

    vector<Record> records = loadDatabase(filename);

    if (records.empty()) {
        cerr << "The database is empty or has not been loaded." << endl;
        return 1;
    }

    vector<Record*> record_ptrs;
    for (size_t i = 0; i < records.size(); ++i) {
        record_ptrs.push_back(&records[i]);
    }

    cout << "The database is loaded. Output of 20 entries per page from original records:" << endl;
    paginatePointers(record_ptrs);

    cout << "Data ordering by year ..." << endl;
    heapsortPointers(record_ptrs);

    cout << "Output of 20 entries per page from sorted pointer array:" << endl;
    paginatePointers(record_ptrs);

    short year;
    cout << "Enter the year of publication to search for: ";

    while (!(cin >> year)) {
        cin.clear();
        cout << "Invalid input. Please enter a valid year: ";
    }
    cin.ignore();

    CustomQueue result_queue = binarySearchYearAll(record_ptrs, year);

    if (!result_queue.empty()) {
        cout << "Records with the year of publication '" << year << "' have been found:" << endl;
        printQueue(result_queue);
    }
    else {
        cout << "Records with the year of publication '" << year << "' not found." << endl;
    }

    CustomQueue result_queue1 = binarySearchYearAll(record_ptrs, year);

    if (!result_queue1.empty()) {
        cout << "Records with the year of publication '" << year << "' have been found." << endl;

        Vertex* root_DBD = buildBalancedTreeFromQueue(result_queue1);

        cout << "Displaying records in the balanced DBD sorted by pages:" << endl;
        int count = 1;
        printDBD(root_DBD, count);

        short pages;
        cout << "Enter the number of pages to search in the balanced DBD: ";
        while (!(cin >> pages)) {
            cin.clear();
            cout << "Invalid input. Please enter a valid page count: ";
        }

        const Vertex* foundNode = searchInDBD(root_DBD, pages);
        if (foundNode) {
            cout << "Records found with " << pages << " pages:" << endl;
            printRecordsWithSamePages(foundNode);
        }
        else {
            cout << "No record found with " << pages << " pages." << endl;
        }

        deleteDBD(root_DBD);
    }
    else {
        cout << "Records with the year of publication '" << year << "' not found." << endl;
    }
    cout<<endl<<endl;

    cout << "Haffmen code" << endl;
    vector<Encoding> symbols;
    calculate_probabilities(filename, symbols);
    qsort(symbols, 0, symbols.size() - 1);

    Encoding* encoded_symbols = symbols.data();
    Encoding* code = huffman(encoded_symbols, symbols.size());

    print_codeword_table(code, symbols.size());
    cout << endl;
    cout << "Craft inequality: "
        << craft_inequality(code, symbols.size()) << endl;
    cout << "Entropy: "
        << entropy(encoded_symbols, symbols.size()) << endl;
    cout << "Average codeword length: "
        << average_codeword_length(code, symbols.size()) << endl;
    cout << "Code redundancy: "
        << code_redundancy(code, symbols.size()) << endl;

    delete[] code;
    return 0;
}