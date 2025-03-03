#include <iostream>
using namespace std;

class Mobileuser {
public:
    string mobile_no;
    string name;
    float amount;
};

class Record {
    Mobileuser u[3];

    void adjust(int n, int i) {
        while (2 * i + 1 <= n) {
            int j = 2 * i + 1;
            if (j + 1 <= n && u[j].amount < u[j + 1].amount) {
                j++;
            }
            if (u[i].amount >= u[j].amount) {
                break;
            } else {
                swap(u[i], u[j]);
                i = j;
            }
        }
    }

public:
    void display() {
        for (int i = 0; i < 3; i++) {
            cout << "Mobile \t \t Name \t \t Amount" << endl;
            cout << u[i].mobile_no << "\t" << u[i].name << "\t \t " << u[i].amount << endl;
        }
    }

    void accept() {
        for (int i = 0; i < 3; i++) {
            cout << "Enter mobile no: ";
            cin >> u[i].mobile_no;
            cout << "Enter name: ";
            cin >> u[i].name;
            cout << "Enter amount: ";
            cin >> u[i].amount;
        }
    }

    void heapsort() {
        int n = 3;
        for (int i = n / 2 - 1; i >= 0; i--) {
            adjust(n - 1, i);
        }

        while (n > 0) {
            swap(u[0], u[n - 1]);
            n--;
            adjust(n - 1, 0);
        }
    }

    void heapdisplay() {
        for (int i = 0; i < 3; i++) {
            cout << "Mobile \t \t Name \t \t Amount" << endl;
            cout << u[i].mobile_no << "\t" << u[i].name << "\t \t " << u[i].amount << endl;
        }
    }
    void linearsearch() {
        string key;
        cout << "Enter mobile number to search: ";
        cin >> key;
        for (int i = 0; i < 3; i++) {
            if (u[i].mobile_no == key) {
                cout << "Mobile \t \t Name \t \t Amount" << endl;
                cout << u[i].mobile_no << "\t" << u[i].name << "\t \t " << u[i].amount << endl;
                return;
            }
        }
        cout << "Record not found" << endl;
    }
    void recursivebinarysearch(int l, int h, string key) {
        if (l > h) {
            cout << "Record not found" << endl;
            return;
        }
        int mid = (l + h) / 2;
        if (u[mid].mobile_no == key) {
            cout << "Mobile \t \t Name \t \t Amount" << endl;
            cout << u[mid].mobile_no << "\t" << u[mid].name << "\t \t " << u[mid].amount << endl;
            return;
        } else if (u[mid].mobile_no < key) {
            recursivebinarysearch(mid + 1, h, key);
        } else {
            recursivebinarysearch(l, mid - 1, key);
        }
    }
    void binarysearch() {
        string key;
        cout << "Enter mobile number to search: ";
        cin >> key;
        int l = 0;
        int h = 3;
        while (l <= h) {
            int mid = (l + h) / 2;
            if (u[mid].mobile_no == key) {
                cout << "Mobile \t \t Name \t \t Amount" << endl;
                cout << u[mid].mobile_no << "\t" << u[mid].name << "\t \t " << u[mid].amount << endl;
                return;
            } else if (u[mid].mobile_no < key) {
                l = mid + 1;
            } else {
                h = mid - 1;
            }
        }
        cout << "Record not found" << endl;
    }
    void quicksort(int l, int h) {
        if (l < h) {
            int j = partition(l, h);
            quicksort(l, j - 1);
            quicksort(j + 1, h);
        }
    }
    int partition(int l, int h) {
        string pivot = u[l].mobile_no;
        int i = l;
        int j = h;
        while (i < j) {
            while(i <= h && u[i].mobile_no <= pivot) {
                i++;
            }
            while(j >= l && u[j].mobile_no > pivot) {
                j--;
            }
            if (i < j) {
                swap(u[i], u[j]);
            }
    }
    swap(u[l], u[j]);
    return j;
    }
};

int main() {
    Record r;
    r.accept();
    cout<<endl;
    r.display();
    cout<<endl;
    cout << "After sorting" << endl;
    r.quicksort(0, 2);
    r.display();
    cout<<endl;
    // r.heapsort();
    // r.heapdisplay();
    // cout<<endl;
    // cout << "Linear search" << endl;
    // r.linearsearch();
    // cout<<endl;
    // cout << "Binary search" << endl;
    // r.binarysearch();
    // cout<<endl;
    // cout<<"Recursive Binary search"<<endl;
    // r.recursivebinarysearch(0, 2, "9834968193");
    // cout<<endl;
    return 0;
}