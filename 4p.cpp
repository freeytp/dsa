#include<iostream>
#include<stack>
#include<cctype>
using namespace std;

struct Node{
    char data;
    Node* left;
    Node* right;

    Node(char d) : data(d), left(nullptr) , right(nullptr){}
};

bool isoperator(char c){
    return ( c=='+' || c=='-' || c=='/' || c=='*');
}

Node* ConstructTreeFromPrefix(const string& prefix){
    stack<Node*> st;

    for (int i = prefix.length() - 1; i>=0;i--){
        char c=prefix[i];
        Node* node=new Node(c);

        if (isoperator(c)){
            node->left=st.top();st.pop();
            node->right=st.top();st.pop();
        }
        st.push(node);
    }
    return st.top();
}


void PostOrdernonRec(Node* root ){
    if (!root) return;

    stack<Node*> s1,s2;
    s1.push(root);

    while(!s1.empty()){
        Node* node=s1.top();s1.pop();
        s2.push(node);

        if(node->left) s1.push(node->left);
        if(node->right) s1.push(node->right);
    }

    while(!s2.empty()){
        cout<<s2.top()->data<<"";
        s2.pop();
    }
    cout<<endl;
}

void DeleteTree(Node* root){
    if (!root) return;
    DeleteTree(root->left);
    DeleteTree(root->right);
    cout<<"Deleted node :"<<root->data<<endl;
    delete root;
}

int main (){
    string prefix;
    cout<<"Enter size of expression: ";
    int s;
    cin>>s;

    cout<<"enter each element in prefix expression:\n";
    for (int i=0;i<s;i++){
        char ch;
        cout<<"Element"<<i+1<<":";
        cin>>ch;
        prefix+=ch;
    }

    Node* root=ConstructTreeFromPrefix(prefix);

    cout<<"\n---------------------------postorder traversal-------------------------------\t";
    PostOrdernonRec(root);

    DeleteTree(root);

    return 0;
}

