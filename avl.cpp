#include<bits/stdc++.h>
using namespace std;

class avl_node{
    public:
    char word[50];
    char meaning[50];
    avl_node *left;
    avl_node *right;

};

class avl_tree{
    public:
    avl_node* insert(avl_node *,  avl_node *);
    avl_node* balance(avl_node *);
    int height(avl_node *);
    int balance_factor(avl_node *);
    int diff(avl_node *);
    avl_node* ll_rotation(avl_node *);
    avl_node* rr_rotation(avl_node *);
    avl_node* lr_rotation(avl_node *);
    avl_node* rl_rotation(avl_node *);
    void inorder(avl_node *);
    avl_node *root = NULL; 

    void insert() {
        char ch;
        do {
            avl_node *temp = new avl_node;
            cout << "Enter word and its meaning: ";
            cin >> temp->word >> temp->meaning;
            root = insert(root, temp);
            cout << "Do you want to insert another node? (Y/N): ";
            cin >> ch;
        } while (ch == 'Y' || ch == 'y');
    }   
};

// avl_node* avl_tree::insert(avl_node *root, char word[], char meaning[]){
//     if (root == NULL) {
//         root = new avl_node;
//         strcpy(root->word, word);
//         strcpy(root->meaning, meaning);
//         root->left = NULL;
//         root->right = NULL;
//     } else {
//         if (strcmp(word, root->word) < 0) { 
//             root->left = insert(root->left, word, meaning);
//         } else if (strcmp(word, root->word) > 0) {
//             root->right = insert(root->right, word, meaning);
//         } else {
//             strcpy(root->meaning, meaning);
//         }
//     }
//     return root;
// }

avl_node* avl_tree::insert(avl_node *root, avl_node *temp) {
    if (root == NULL) {
        root = new avl_node;
        strcpy(root->word, temp->word);
        strcpy(root->meaning, temp->meaning);
        root->left = NULL;
        root->right = NULL;
        return root;
    } else if (strcmp(temp->word, root->word) < 0) {
        root->left = insert(root->left, temp);
        root = balance(root);
    } else if (strcmp(temp->word, root->word) >= 0) {
        root->right = insert(root->right, temp);
        root = balance(root);
    }
    return root;
}
void avl_tree::inorder(avl_node *tree){
    if (tree == NULL) {
        return;
    }
    inorder(tree->left);
    cout << tree->word << " : " << tree->meaning << endl;
    inorder(tree->right);
}

int avl_tree::height(avl_node *root){
    int h = 0;
    if (root != NULL) {
        int l_height = height(root->left);
        int r_height = height(root->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

int avl_tree::diff(avl_node *root){
    int l_height = height(root->left);
    int r_height = height(root->right);
    int b_factor = l_height - r_height;
    return b_factor;
}

avl_node* avl_tree::balance(avl_node *root){
    int bal_factor = diff(root);
    if (bal_factor > 1) {
        if (diff(root->left) > 0) {
            root = ll_rotation(root);
        } else {
            root = lr_rotation(root);
        }
    } else if (bal_factor < -1) {
        if (diff(root->right) > 0) {
            root = rl_rotation(root);
        } else {
            root = rr_rotation(root);
        }
    }
    return root;
}

avl_node* avl_tree::ll_rotation(avl_node *parent){
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

avl_node* avl_tree::rr_rotation(avl_node *parent){
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avl_node* avl_tree::lr_rotation(avl_node *parent){
    avl_node *temp;
    temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}

avl_node* avl_tree::rl_rotation(avl_node *parent){
    avl_node *temp;
    temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
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