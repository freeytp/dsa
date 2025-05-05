#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    bool rightThread; 
};

Node* newNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    node->rightThread = false;
    return node;
}

void inorderTraversal(Node* root) {
    Node* curr = root;
    while (curr != nullptr) {
       
        if (curr->left == nullptr) {
            cout << curr->data << " ";
            if (curr->rightThread) {
                curr = curr->right;
            } else {
                curr = curr->right;
            }
        } else {
        
            Node* pred = curr->left;
            while (pred->right != nullptr && !pred->rightThread) {
                pred = pred->right;
            }
            
         
            if (pred->right == nullptr) {
                pred->right = curr;
                pred->rightThread = true;
                curr = curr->left; 
            } else {
               
                cout << curr->data << " ";
                pred->right = nullptr;
                pred->rightThread = false;
                curr = curr->right; 
            }
        }
    }
}


void convertToThreaded(Node* root) {
    Node* curr = root;
    Node* prev = nullptr;
    
  
    while (curr != nullptr) {
       
        if (curr->left == nullptr) {
            if (prev != nullptr) {
                prev->right = curr;
                prev->rightThread = true;
            }
            prev = curr;
            curr = curr->right;
        } else {
          
            Node* pred = curr->left;
            while (pred->right != nullptr && !pred->rightThread) {
                pred = pred->right;
            }
            
           
            if (pred->right == nullptr) {
                pred->right = curr;
                pred->rightThread = true;
                curr = curr->left;
            } else {
            
                if (prev != nullptr) {
                    prev->right = curr;
                    prev->rightThread = true;
                }
                prev = curr;
                pred->right = nullptr;
                pred->rightThread = false;
                curr = curr->right;
            }
        }
    }
}

int main() {

    Node* root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(20);
    root->left->left = newNode(3);
    root->left->right = newNode(7);
    root->right->left = newNode(15);
    root->right->right = newNode(25);
    
 
    convertToThreaded(root);
    
   
    cout << "In-order traversal of threaded binary tree: ";
    inorderTraversal(root);
    
    return 0;
}
