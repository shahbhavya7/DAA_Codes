#include <bits/stdc++.h>
using namespace std;

class avl_node {
public:
    char word[50];
    char meaning[50];
    avl_node *left;
    avl_node *right;
};

class avl_tree {
public:
    avl_node* create(const char[], const char[]);
    avl_node* insert(avl_node *, const char[], const char[]);
    void inorder(avl_node *);
};

avl_node* avl_tree::create(const char word[], const char meaning[]) {
    avl_node *root = new avl_node;
    strcpy(root->word, word);
    strcpy(root->meaning, meaning);
    root->left = NULL;
    root->right = NULL;
    return root;
}

avl_node* avl_tree::insert(avl_node *root, const char word[], const char meaning[]) {
    if (root == NULL) {
        root = new avl_node;
        strcpy(root->word, word);
        strcpy(root->meaning, meaning);
        root->left = NULL;
        root->right = NULL;
    } else {
        if (strcmp(word, root->word) < 0) {
            root->left = insert(root->left, word, meaning);
        } else if (strcmp(word, root->word) > 0) {
            root->right = insert(root->right, word, meaning);
        } else {
            strcpy(root->meaning, meaning);
        }
    }
    return root;
}

void avl_tree::inorder(avl_node *tree) {
    if (tree == NULL) {
        return;
    }
    inorder(tree->left);
    cout << tree->word << " : " << tree->meaning << endl;
    inorder(tree->right);
}

int main() {
    avl_tree avl;
    avl_node *root = NULL;
    int choice;
    char word[50], meaning[50];

    while (1) {
        cout << "1. Create the first node" << endl;
        cout << "2. Insert Element into the tree" << endl;
        cout << "3. Inorder" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                if (root != NULL) {
                    cout << "The tree already has a root node." << endl;
                    break;
                }
                cout << "Enter word for the first node: ";
                cin >> word;
                cout << "Enter meaning: ";
                cin >> meaning;
                root = avl.create(word, meaning);
                break;
            case 2:
                if (root == NULL) {
                    cout << "The tree does not have a root node. Please create the first node first." << endl;
                    break;
                }
                cout << "Enter word to be inserted: ";
                cin >> word;
                cout << "Enter meaning: ";
                cin >> meaning;
                root = avl.insert(root, word, meaning);
                break;
            case 3:
                if (root == NULL) {
                    cout << "Tree is Empty" << endl;
                    continue;
                }
                cout << "Inorder Traversal of AVL tree is: " << endl;
                avl.inorder(root);
                cout << endl;
                break;
            case 4:
                exit(0);
                break;
            default:
                cout << "Wrong Choice" << endl;
        }
    }
    return 0;
}