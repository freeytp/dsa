#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);
    return root;
}

int findHeight(Node* root) {
    if (root == NULL) return 0;
    int left = findHeight(root->left);
    int right = findHeight(root->right);
    return max(left, right) + 1;
}

int findMin(Node* root) {
    if (root == NULL) return -1; 
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

void mirror(Node* root) {
    if (root == NULL) return;
    mirror(root->left);
    mirror(root->right);
    swap(root->left, root->right);
}

bool search(Node* root, int key) {
    if (root == NULL) return false;
    if (root->data == key) return true;
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

Node* findMinNode(Node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {

        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}


void bfs(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front(); q.pop();
        cout << temp->data << " ";
        if (temp->left != NULL)
            q.push(temp->left);
        if (temp->right != NULL)
            q.push(temp->right);
    }
}

int main() {
    Node* root = NULL;

   
    int values[] = {50, 30, 20, 40, 70, 60, 80};
    for (int val : values)
        root = insert(root, val);

    root = insert(root, 65);

    cout << "Height (Longest Path): " << findHeight(root) << endl;

    cout << "Minimum Value: " << findMin(root) << endl;


    mirror(root);
    cout << "Inorder after mirror: ";
    inorder(root);
    cout << endl;


    int key = 65;
    cout << "Search " << key << ": " << (search(root, key) ? "Found" : "Not Found") << endl;

  
    root = deleteNode(root, 65);
    cout << "Inorder after deleting 65: ";
    inorder(root);
    cout << endl;

  
    cout << "Inorder: "; inorder(root); cout << endl;
    cout << "Preorder: "; preorder(root); cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;

 
    cout << "BFS: "; bfs(root); cout << endl;

    return 0;
}
