#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define TABLE_SIZE 10

class record {
public:
    int roll_no;
    string name;
    int marks;
    friend class Student;
};

class HashTable {
    int roll_no,pos;
    public: HashTable(){
        roll_no = -1;
        pos = -1;
    }
    friend class Student;
};
class Student{
    record rec;
    HashTable h[TABLE_SIZE];

    int s,relt;
    public:Student();
    void create_wor();
    void create_wr();
    void display();
    void displayall();
    void retrieve();
    void modify();  

};

Student::Student(){
    s = sizeof(record);
    for (int i = 0; i < TABLE_SIZE; i++) {
        h[i].roll_no = -1;
        h[i].pos = -1;
    }
    relt = 0; 
}

void Student::create_wr(){
    char ans;
    int nloc;
    HashTable temp;
    fstream f;
    f.open("student.txt", ios::binary | ios::out);
    int loc;
    do{
        cout<<"\n Enter the Details of the Student: \n";
        cout<<"Roll No: ";
        cin>>rec.roll_no;
        cout<<"Name: ";
        cin>>rec.name;
        cout<<"Marks: ";
        cin>>rec.marks;
        loc = rec.roll_no % TABLE_SIZE;

        if(h[loc].roll_no == -1){
            h[loc].roll_no = rec.roll_no;
            h[loc].pos = relt;
            f.write((char*)&rec, s);
            relt = relt + 1;
        }
        else{
            temp.roll_no = rec.roll_no;
            temp.pos = relt;
            f.write((char*)&rec, s);
            relt = relt + 1;

            if(loc!=(h[loc].roll_no % TABLE_SIZE)){
                temp.roll_no = h[loc].roll_no;
                temp.pos = h[loc].pos;
                h[loc].roll_no = rec.roll_no;
                h[loc].pos = relt-1;
          }
            nloc = (loc+1)%TABLE_SIZE;
            
            while(nloc!=loc){
                if(h[nloc].roll_no == -1){
                    h[nloc].roll_no = temp.roll_no;
                    h[nloc].pos = temp.pos;
                    break;
                }
                nloc = (nloc+1)%TABLE_SIZE;
            }
        }
        cout<<"Do you want to add more records? (y/n): ";
        cin>>ans;
    }while(ans == 'y' || ans == 'Y');
    f.close();
}

void Student::create_wor() {
    char ans;
    fstream f;
    f.open("student.txt", ios::binary | ios::out);
    int loc;
    
    do {
        cout << "\n Enter the Details of the Student: \n";
        cout << "Roll No: ";
        cin >> rec.roll_no;
        cout << "Name: ";
        cin >> rec.name;
        cout << "Marks: ";
        cin >> rec.marks;
        
        loc = rec.roll_no % TABLE_SIZE;
        
        while (h[loc].roll_no != -1) {
            loc = (loc + 1) % TABLE_SIZE;
        }
        
        h[loc].roll_no = rec.roll_no;
        h[loc].pos = relt;
        
        f.write((char*)&rec, s);
        relt = relt + 1;
        
        cout << "Do you want to add more records? (y/n): ";
        cin >> ans;
    } while(ans == 'y' || ans == 'Y');
    
    f.close();
}

void Student::display(){
    cout<<rec.roll_no<<"\t"<<rec.name<<"\t"<<rec.marks<<endl;
}

void Student::displayall() {
    cout << "\n Displaying HashTable: \n";
    cout << "Index\tRoll No\tPosition in File\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << "\t" << h[i].roll_no << "\t" << h[i].pos << endl;
    }
    
    int positions[TABLE_SIZE];
    int indices[TABLE_SIZE];
    int count = 0;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (h[i].roll_no != -1) {
            positions[count] = h[i].pos;
            indices[count] = i;
            count++;
        }
    }
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (positions[j] > positions[j + 1]) {
                int temp = positions[j];
                positions[j] = positions[j + 1];
                positions[j + 1] = temp;
                
                temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
    
    cout << "\nStudent Records (in order of file position):\n";
    cout << "Roll No\tName\tMarks\n";
    fstream f;
    f.open("student.txt", ios::binary | ios::in);
    
    // Display records in the order of positions
    for (int i = 0; i < count; i++) {
        int idx = indices[i];
        int p = h[idx].pos * s;
        f.seekg(p, ios::beg);
        f.read((char*)&rec, s);
        display();
    }
    f.close();
}

void Student ::retrieve(){
    fstream f;
    f.open("student.txt", ios::binary | ios::in);
    cout<<"Enter the Roll No of the Student to be retrieved: ";
    cin>>rec.roll_no;
    int loc = rec.roll_no % TABLE_SIZE , i;
    for(i=0; i<TABLE_SIZE; i++){
        if(h[loc].roll_no == rec.roll_no){
            int p = h[loc].pos * s;
            f.seekg(p, ios::beg);
            f.read((char*)&rec, s);
            display();
            break;
        }
        else{
            loc = (loc+1)%TABLE_SIZE;
        }
    }
    if(i > TABLE_SIZE){
        cout<<"Record not found!\n";
    }
    f.close();
}

void Student :: modify(){
    fstream f;
    f.open("student.txt", ios::binary | ios::in | ios::out);
    cout<<"Enter the Roll No of the Student to be modified: ";
    cin>>rec.roll_no;
    int loc = rec.roll_no % TABLE_SIZE , i;
    for(i=0; i<TABLE_SIZE; i++){
        if(h[loc].roll_no == rec.roll_no){
            int p = h[loc].pos * s;
            f.seekg(p, ios::beg);
            f.read((char*)&rec, s);
            cout<<"Enter the new Name: ";
            cin>>rec.name;
            cout<<"Enter the new Marks: ";
            cin>>rec.marks;
            p = h[loc].pos * s;
            f.seekp(p, ios::beg);
            f.write((char*)&rec, s);
            break;
        }
        else{
            loc = (loc+1)%TABLE_SIZE;
        }
    }
    if(i > TABLE_SIZE){
        cout<<"Record not found!\n";
    }
    f.close();
}

int main() {
    Student s;
    int choice, roll_no, marks;
    string name;

    do {
        cout << "\n1. Insert Without Replacement\n2. Insert With Replacement\n3. Display\n4. Retrieve\n5. Modify\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                s.create_wor();
                break;
            case 2:
                s.create_wr();
                break;
            case 3:
                cout << "\nDisplaying all records:\n";
                s.displayall();
                break;
            case 4:
                s.retrieve();
                break;
            case 5:
                s.modify();
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