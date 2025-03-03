#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    char val;
    Node *next;
    friend class graph;
};

class graph {
    Node *arr[8]; // Array of pointers to the vertices (i.e. array of linked lists)
    unordered_map<char, bool> visited;
    int n;
    
public:
    graph() {
        cout << "Enter the number of vertices: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            arr[i] = new Node;
            cout << "Enter the value of the vertex " << i << ": ";
            cin >> arr[i]->val;
            arr[i]->next = NULL;
        }
    }
    void create();
    void DFT();
    void BFT();
    
private:
    // Helper function to return the index of the vertex with the given character value.
    int getIndex(char v) {
        for (int i = 0; i < n; i++) {
            if (arr[i]->val == v)
                return i;
        }
        return -1; // Not found (should not happen if inputs are correct)
    }
};

void graph::create() {
    char ch;
    for (int i = 0; i < n; i++) { // n is the number of vertices 
        Node *temp = arr[i]; //- arr[i] is the first node of the linked list at ith position of the array arr, the value part of array is itself a node and starting node of the linked list
        //- as the array declared is of type Node* so arr[i]  
        while (true) {
            cout << "\nIs there any vertex connected to " << arr[i]->val << "? (y/n): ";
            cin >> ch;
            if (ch == 'y') {
                Node *curr = new Node;
                cout << "Enter the name of the connected vertex: ";
                cin >> curr->val;
                curr->next = NULL;
                temp->next = curr;
                temp = curr;
            } else {
                break;
            }
        }
    }
}

void graph::DFT() {
    stack<char> s;
    char v;
    cout << "Enter the vertex to start DFT: ";
    cin >> v;
    
    // Initialize all vertices as not visited.
    for (int i = 0; i < n; i++) {
        visited[arr[i]->val] = false;
    }
    
    visited[v] = true;
    s.push(v);
    
    while (!s.empty()) {
        v = s.top();
        s.pop();
        cout << " " << v << " " << endl; // Print the current vertex
        
        // Find the index of the current vertex in the array.
        int index = getIndex(v);
        if (index == -1) {
            cout << "Error: Vertex " << v << " not found in the graph.\n";
            continue;
        }
        
        Node *temp = arr[index]->next;
        while (temp != NULL) {
            if (!visited[temp->val]) {
                visited[temp->val] = true;
                s.push(temp->val);
            }
            temp = temp->next;
        }
    }
    cout << endl;
}

void graph::BFT(){
    queue<char> q;  // Using STL queue instead of custom Queuee
    char v;
    cout << "Enter the vertex to start BFT: ";
    cin >> v;
    
    // Initialize all vertices as not visited.
    for (int i = 0; i < n; i++){
        visited[arr[i]->val] = false;
    }
    visited[v] = true;
    
    q.push(v);  // Insert vertex into the queue

    while(!q.empty()){
        v = q.front();  // Get the front element
        q.pop();        // Remove the element from the queue
        cout << " " << v << " "  << endl;
        int index = getIndex(v);
        Node *temp = arr[index]->next;
        while(temp != NULL){
            if(!visited[temp->val]){
                visited[temp->val] = true;
                q.push(temp->val);
            }
            temp = temp->next;
        }
    }
}

int main() {
    graph g;
    cout << "Creation of graph" << endl;
    g.create();
    // cout << "DFT" << endl;
    // g.DFT();
    cout << "BFT" << endl;
    g.BFT();
    return 0;
}
