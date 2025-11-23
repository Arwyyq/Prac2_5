#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct StudentNode {
    string name;
    double avgScore;    // Середній бал (тепер у межах 1-12)
    StudentNode* next;
};

// Функція додавання (без змін)
void push(StudentNode*& head, string newName, double newScore) {
    StudentNode* newNode = new StudentNode();
    newNode->name = newName;
    newNode->avgScore = newScore;
    newNode->next = head;
    head = newNode;
}

// Функція сортування (без змін - алгоритм працює для будь-яких чисел)
void sortList(StudentNode* head) {
    if (head == nullptr) return;

    bool swapped;
    StudentNode* ptr;
    StudentNode* lptr = nullptr;

    do {
        swapped = false;
        ptr = head;

        while (ptr->next != lptr) {
            // Сортуємо за спаданням (від 12 до 1)
            if (ptr->avgScore < ptr->next->avgScore) {
                swap(ptr->avgScore, ptr->next->avgScore);
                swap(ptr->name, ptr->next->name);
                swapped = true;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
}

void printList(StudentNode* node) {
    cout << "--- Список учнів (12-бальна шкала) ---" << endl;
    while (node != nullptr) {
        cout << left << setw(15) << node->name
             << " | Бал: " << node->avgScore << endl;
        node = node->next;
    }
    cout << "--------------------------------------" << endl;
}

// Функція для виводу учнів з "Високим рівнем" знань
void printTopStudents(StudentNode* node, double threshold) {
    cout << "=== ВІДМІННИКИ (Бал >= " << threshold << ") ===" << endl;
    bool found = false;
    while (node != nullptr) {
        if (node->avgScore >= threshold) {
            cout << "★ " << left << setw(15) << node->name
                 << " | Бал: " << node->avgScore << endl;
            found = true;
        }
        node = node->next;
    }
    if (!found) cout << "Немає учнів з таким високим балом." << endl;
    cout << "========================================" << endl;
}

int main() {
    StudentNode* head = nullptr;

    // Оновлені дані для 12-бальної шкали
    push(head, "Петренко", 7.5);  // Достатній рівень
    push(head, "Іваненко", 11.0); // Високий рівень
    push(head, "Сидоренко", 9.2); // Достатній/Високий
    push(head, "Щербина повєлітєль С++", 12.0);   // Максимум
    push(head, "Бондар", 10.5);   // Високий рівень
    push(head, "Лазебник", 5.0);    // Середній рівень

    cout << "До сортування:" << endl;
    printList(head);

    // Сортуємо
    sortList(head);

    cout << "Після сортування (від 12 до 1):" << endl;
    printList(head);

    // Виводимо тих, у кого бал 10 і вище (Високий рівень)
    printTopStudents(head, 10.0);

    return 0;
}