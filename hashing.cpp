#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define TABLE_SIZE 10

class Student {
public:
    int roll_no;
    string name;
    int marks;
    bool occupied;

    Student() : occupied(false) {}  // Default constructor to set occupied to false
    Student(int r, string n, int m, bool o) : roll_no(r), name(n), marks(m), occupied(o) {}  // Parameterized constructor
};

class HashTable {
private:
    Student table[TABLE_SIZE];

    int hashFunction(int roll_no) {
        return roll_no % TABLE_SIZE;
    }

    void saveToFile() {
        ofstream file("student_data.dat", ios::binary);
        file.write((char*)table, sizeof(table));
        file.close();
    }

    void loadFromFile() {
        ifstream file("student_data.dat", ios::binary);
        if (file) {
            file.read((char*)table, sizeof(table));
            file.close();
        }
    }

public:
    HashTable() {
        loadFromFile();
    }

    void insertWithReplacement(int roll_no, string name, int marks) {
        int index = hashFunction(roll_no);
        if (!table[index].occupied) {
            table[index] = {roll_no, name, marks, true};
        } else {
            if (hashFunction(table[index].roll_no) != index) {
                Student temp = table[index];
                table[index] = {roll_no, name, marks, true};
                insertWithReplacement(temp.roll_no, temp.name, temp.marks);  // Recursive insertion for displaced entry
            } else {
                int i = (index + 1) % TABLE_SIZE;
                while (table[i].occupied) {
                    i = (i + 1) % TABLE_SIZE;
                }
                table[i] = {roll_no, name, marks, true};
            }
        }
        saveToFile();
    }

    void insertWithoutReplacement(int roll_no, string name, int marks) {
        int index = hashFunction(roll_no);
        while (table[index].occupied) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index] = {roll_no, name, marks, true};
        saveToFile();
    }

    void display() {
        cout << "Index\tRoll No\tName\tMarks\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].occupied)
                cout << i << "\t" << table[i].roll_no << "\t" << table[i].name << "\t" << table[i].marks << "\n";
            else
                cout << i << "\t--\t--\t--\n";
        }
    }

    void search(int roll_no) {
        int index = hashFunction(roll_no);
        int start = index;
        while (table[index].occupied) {
            if (table[index].roll_no == roll_no) {
                cout << "Found: Roll No: " << table[index].roll_no << ", Name: " << table[index].name << ", Marks: " << table[index].marks << "\n";
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == start) break;
        }
        cout << "Record not found!\n";
    }

    void modify(int roll_no, int new_marks) {
        int index = hashFunction(roll_no);
        int start = index;
        while (table[index].occupied) {
            if (table[index].roll_no == roll_no) {
                table[index].marks = new_marks;
                cout << "Record updated successfully!\n";
                saveToFile();
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == start) break;
        }
        cout << "Record not found!\n";
    }
};

int main() {
    HashTable ht;
    int choice, roll_no, marks;
    string name;

    do {
        cout << "\n1. Insert With Replacement\n2. Insert Without Replacement\n3. Display\n4. Search\n5. Modify\n6. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter Roll No, Name, Marks: ";
                cin >> roll_no >> name >> marks;
                ht.insertWithReplacement(roll_no, name, marks);
                break;
            case 2:
                cout << "Enter Roll No, Name, Marks: ";
                cin >> roll_no >> name >> marks;
                ht.insertWithoutReplacement(roll_no, name, marks);
                break;
            case 3:
                ht.display();
                break;
            case 4:
                cout << "Enter Roll No to search: ";
                cin >> roll_no;
                ht.search(roll_no);
                break;
            case 5:
                cout << "Enter Roll No and new Marks: ";
                cin >> roll_no >> marks;
                ht.modify(roll_no, marks);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}