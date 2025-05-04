#include<iostream>
#include<string>
#include<list>
using namespace std ;

const int Table_Size=10;

class HashNode {
    public:
    string key;
    string value;

    HashNode(string k,string v): key(k),value(v){}
};

class HashTable{
    private:
    list<HashNode> table[Table_Size];

    int HashFunction(string key){
        int hash =0;
        for (char ch :key){
            hash=(hash + int (ch))% Table_Size;
        }
        return hash;
    }

    public:

    void insert(string key, string value){
        int index=HashFunction(key);

        for (auto& node :table[index]){
            if (node.key==key){
                node.value=value;
                cout << "value updated successfully ! \n";
                return;
            }
        }

        table[index].push_back(HashNode(key,value));
        cout<<"inserted("<< key << ","<<value<<") At index :"<< index <<"\n";
    }

    void find(string key){
        int index=HashFunction(key);
        for (auto& node : table[index]){
            if (node.key ==key){
                cout<<"Found : "<<node.key <<"=>"<<node.value<<"\n";
                return;
            }
        }
        cout<< " Key not found ! \n";
    }

    void remove(string key){
        int index=HashFunction(key);
        for (auto it=table[index].begin();it!=table[index].end();++it){
            if (it->key==key){
                table[index].erase(it);
                cout<<"Deleted key :"<<key<<"\n";
                return;
            }
        }
        cout<<"Key:"<<key<< "\tnot found to delete !\n";
    }

    void display(){
        cout<<"\n-----HASTABLE-----\n";
        for(int i=0;i<Table_Size;i++){
            cout<<"["<<i<<"]:";
            for (auto& node:table[i]){
                cout<<"("<<node.key<<","<<node.value<<")->";
            }
            cout<<"NULL\n";
        }
        cout<<"------------------\n\n";
    }

};

int main(){
    HashTable dict;
    dict.insert("car","vehicle");
    dict.insert("bat","equipment");
    dict.insert("apple","fruit");
    dict.insert("ball","toy");
    
    dict.display();
    
    dict.find("bat");

    dict.remove("Ball");
    dict.remove("ball");

    dict.display();

    

    return 0;
}