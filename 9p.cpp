#include <iostream>
#include <string>
using namespace std;

struct Node {
    string key, meaning;
    Node *left, *right;
    int height;
};

int height(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}


Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}


Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}


Node* insert(Node* root, string key, string meaning) {
    if (!root) {
        Node* node = new Node{key, meaning, nullptr, nullptr, 1};
        return node;
    }
    if (key < root->key)
        root->left = insert(root->left, key, meaning);
    else if (key > root->key)
        root->right = insert(root->right, key, meaning);
    else {
        cout << "Duplicate key not allowed.\n";
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rotateRight(root);
 
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}


Node* deleteNode(Node* root, string key) {
    if (!root) return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}


bool update(Node* root, string key, string newMeaning) {
    while (root) {
        if (key == root->key) {
            root->meaning = newMeaning;
            return true;
        } else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return false;
}


void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " : " << root->meaning << endl;
    inorder(root->right);
}


void reverseInorder(Node* root) {
    if (!root) return;
    reverseInorder(root->right);
    cout << root->key << " : " << root->meaning << endl;
    reverseInorder(root->left);
}


bool search(Node* root, string key, int& comparisons) {
    while (root) {
        comparisons++;
        if (key == root->key)
            return true;
        else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return false;
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;
    while (true) {
        cout << "\n1.Insert 2.Delete 3.Update 4.Display Asc 5.Display Desc 6.Search 7.Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter keyword and meaning: ";
                cin >> key >> meaning;
                root = insert(root, key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin >> meaning;
                if (update(root, key, meaning))
                    cout << "Updated successfully.\n";
                else
                    cout << "Keyword not found.\n";
                break;
            case 4:
                cout << "Dictionary in Ascending Order:\n";
                inorder(root);
                break;
            case 5:
                cout << "Dictionary in Descending Order:\n";
                reverseInorder(root);
                break;
            case 6: {
                cout << "Enter keyword to search: ";
                cin >> key;
                int cmp = 0;
                if (search(root, key, cmp))
                    cout << "Found in " << cmp << " comparisons.\n";
                else
                    cout << "Not found after " << cmp << " comparisons.\n";
                break;
            }
            case 7:
                return 0;
        }
    }
}
