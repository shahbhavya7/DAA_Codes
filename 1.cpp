
#include <iostream>
#include <utility>
#include <cstring>
using namespace std;

class mobileuser {
    long int mobileno;
    string name;
    float amount;

    mobileuser() {
        this->mobileno = 0;
        this->name = "";
        this->amount = 0.0;
    }

    friend class record;
};

class record {
    mobileuser u[5];

public:
    void accept() {
        for (int i = 0; i < 5; i++) {
            cout << "Enter details for user " << i + 1 << endl;
            cout << "Enter mobile number: ";
            cin >> u[i].mobileno;
            cout << "Enter your name: ";
            cin >> u[i].name;
            cout << "Enter amount: ";
            cin >> u[i].amount;
        }
    }

    void display() {
        cout << "Mobile no." << "\t" << "Name" << "\t" << "Amount" << endl;
        for (int i = 0; i < 5; i++) {
            cout << u[i].mobileno << "\t\t" << u[i].name << "\t" << u[i].amount << endl;
        }
    }

    void adjust(int n, int i) {
        while (2 * i + 1 <= n) {
            int j = 2 * i + 1;
            if (j + 1 <= n && u[j].mobileno < u[j + 1].mobileno) {
                j++;
            }
            if (u[i].mobileno >= u[j].mobileno) {
                break;
            } else {
                swap(u[i], u[j]);
                i = j;
            }
        }
    }

    void heapsort() {
        int n = 5;
        for (int i = n / 2 - 1; i >= 0; i--) {
            adjust(n - 1, i);
        }

        while (n > 0) {
            swap(u[0], u[n - 1]);
            n--;
            adjust(n - 1, 0);
        }
    }

    void l_s() {
        int x;
        cout << "What element do you want to search? \n" << endl;
        cin >> x;
        int n = 5;
        for (int i = 0; i < n; i++) {
            if (u[i].mobileno == x) {
                cout << "Element found at index: " << i << endl;
                return;
            }
        }
        cout << "Element not found!" << endl;
    }

    void b_s() {
        int x;
        cout << "What element do you want to search? \n" << endl;
        cin >> x;
        int n = 5;
        int l = 0;
        int h = n - 1;
        while (l <= h) {
            int mid = l + (h - l) / 2;
            if (x == u[mid].mobileno) {
                cout << "Found element at " << mid << endl;
                return;
            }
            else if (x < u[mid].mobileno) {
                h = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        cout << "Element not present! \n" << endl;
    }

    void b_s_r(int l, int h, int x) {
        if (l <= h) {
            int mid = l + (h - l) / 2;
            if (x == u[mid].mobileno) {
                cout << "Found element at " << mid << endl;
                return;
            }
            if (x < u[mid].mobileno) {
                return b_s_r(l, h = mid - 1, x);
            }
            else {
                return b_s_r(l = mid + 1, h, x);
            }
        }
        cout << "Not found" << endl;
    }

    int partition(int l, int h) {
        int pivot = u[h].mobileno;
        int i = l - 1; 
        for (int j = l; j < h; j++) {
            if (u[j].mobileno <= pivot) {
                i++;
                swap(u[i].mobileno, u[j].mobileno); 
                swap(u[i].name, u[j].name);
                swap(u[i].amount, u[j].amount);
            }
        }
        swap(u[i + 1].mobileno, u[h].mobileno);
        swap(u[i + 1].name, u[h].name);
        swap(u[i + 1].amount, u[h].amount);
        return i + 1; 
    }

    void quicksort(int l, int h) {
        if (l < h) {
            int piv_index = partition(l, h);
            quicksort(l, piv_index - 1);
            quicksort(piv_index + 1, h);
        }
    }

    void perform_operations() {
        int choice;
        do {
            cout << "\n1. QuickSort\n2. HeapSort\n3. Binary Search\n4. Linear Search\n5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    quicksort(0, 4);
                    cout << "After Quick Sort:\n";
                    display();
                    break;
                case 2:
                    heapsort();
                    cout << "After Heap Sort:\n";
                    display();
                    break;
                case 3:
                    b_s();
                    break;
                case 4:
                    l_s();
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice, try again.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    record r;
    r.accept();

    r.perform_operations();

    return 0;
}
