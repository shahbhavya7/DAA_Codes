#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int id;
    string name;
    Node *next;
    friend class graph;
};

class graph {
    Node *arr[8]; // Array of pointers to the vertices (i.e. each is the head of a linked list)
    unordered_map<int, bool> visited;
    int n;
    
public:
    graph() {
        cout << "Enter the number of vertices: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            arr[i] = new Node;
            cout << "Enter the ID for vertex " << i << ": ";
            cin >> arr[i]->id;
            cout << "Enter the name for vertex " << i << ": ";
            cin >> arr[i]->name;
            arr[i]->next = NULL;
        }
    }
    
    // a. Create the Graph using Adjacency List (Friend name, ID)
    void create() {
        char ch;
        for (int i = 0; i < n; i++) {
            Node *temp = arr[i]; // Head of the list for vertex i
            while (true) {
                cout << "\nIs there any friend connected to " << arr[i]->name
                     << " (ID: " << arr[i]->id << ")? (y/n): ";
                cin >> ch;
                if (ch == 'y') {
                    Node *curr = new Node;
                    cout << "Enter the connected friend's ID: ";
                    cin >> curr->id;
                    cout << "Enter the connected friend's name: ";
                    cin >> curr->name;
                    curr->next = NULL;
                    temp->next = curr;
                    temp = curr;
                } else {
                    break;
                }
            }
        }
    }
    
    // b. Display the Graph
    void display() {
        cout << "\nGraph Representation:\n";
        for (int i = 0; i < n; i++) {
            cout << "Vertex " << arr[i]->id << " (" << arr[i]->name << ") -> ";
            Node *temp = arr[i]->next;
            while (temp != NULL) {
                cout << "(" << temp->id << ", " << temp->name << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    
    // c. Perform the non-recursive DFS Traversal (using ID) without using vector for neighbors.
    void DFT() {
        stack<int> s;
        int id;
        cout << "Enter the ID to start non-recursive DFS: ";
        cin >> id;
        
        // Initialize all vertices as not visited.
        for (int i = 0; i < n; i++) {
            visited[arr[i]->id] = false;
        }
        visited[id] = true;
        s.push(id);
        
        cout << "\nNon-Recursive DFS Traversal (by ID):\n";
        while (!s.empty()) {
            id = s.top();
            s.pop();
            int index = getIndex(id);
            if (index == -1) {
                cout << "Error: Vertex with ID " << id << " not found.\n";
                continue;
            }
            cout << id << " (" << arr[index]->name << ")\n";
            
            // Directly traverse the adjacency list and push unvisited neighbors.
            Node *temp = arr[index]->next;
            while (temp != NULL) {
                if (!visited[temp->id]) {
                    visited[temp->id] = true;
                    s.push(temp->id);
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }
    
    // c. Perform the recursive DFS Traversal (using ID)
    void DFS_recursive() {
        int id;
        cout << "Enter the ID to start recursive DFS: ";
        cin >> id;
        
        unordered_map<int, bool> visitedRec;
        for (int i = 0; i < n; i++) {
            visitedRec[arr[i]->id] = false;
        }
        cout << "\nRecursive DFS Traversal (by ID):\n";
        DFS_recursive_helper(id, visitedRec);
        cout << endl;
    }
    
    // d. Perform the non-recursive BFS Traversal (using ID)
    void BFT() {
        queue<int> q;
        int id;
        cout << "Enter the ID to start BFS: ";
        cin >> id;
        
        // Initialize all vertices as not visited.
        for (int i = 0; i < n; i++) {
            visited[arr[i]->id] = false;
        }
        visited[id] = true;
        q.push(id);
        
        cout << "\nBFS Traversal (by ID):\n";
        while (!q.empty()) {
            id = q.front();
            q.pop();
            int index = getIndex(id);
            if (index == -1) {
                cout << "Error: Vertex with ID " << id << " not found.\n";
                continue;
            }
            cout << id << " (" << arr[index]->name << ")\n";
            Node *temp = arr[index]->next;
            while (temp != NULL) {
                if (!visited[temp->id]) {
                    visited[temp->id] = true;
                    q.push(temp->id);
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }
    
private:
    // Helper function to return the index of the vertex with the given ID.
    int getIndex(int id) {
        for (int i = 0; i < n; i++) {
            if (arr[i]->id == id)
                return i;
        }
        return -1; // Not found
    }
    
    // Helper function for recursive DFS.
    void DFS_recursive_helper(int id, unordered_map<int, bool>& visitedRec) {
        int index = getIndex(id);
        if (index == -1) {
            cout << "Error: Vertex with ID " << id << " not found.\n";
            return;
        }
        cout << id << " (" << arr[index]->name << ")\n";
        visitedRec[id] = true;
        Node *temp = arr[index]->next;
        while (temp != NULL) {
            if (!visitedRec[temp->id])
                DFS_recursive_helper(temp->id, visitedRec);
            temp = temp->next;
        }
    }
};

int main() {
    graph g;
    cout << "\n--- Creation of Graph ---" << endl;
    g.create();
    g.display();
    
    // Non-recursive DFS Traversal
    g.DFT();
    
    // Recursive DFS Traversal
    g.DFS_recursive();
    
    // BFS Traversal
    g.BFT();
    
    return 0;
}