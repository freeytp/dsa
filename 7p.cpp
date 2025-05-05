#include<iostream>
#include<stack>
#include<set>
#include<unordered_map>
#include<string>
#include<vector>
using namespace std;

class graph{
    unordered_map<string, vector<pair<string, int>>> adj;

public:
    void addflight(string from,string to,int cost){
        adj[from].push_back({to, cost});
        adj[to].push_back({from, cost});
    }

    void display(){
        cout<<"flight path adjecency list :\n";
        for (auto& city:adj){
            cout<<city.first<<"->";
            for (auto& dest:city.second){
                cout<<"\t("<<dest.first<<", cost :"<<dest.second<<")\t";
            }cout<<endl;
        }
    }

    bool isconnected(){
        if (adj.empty()) return true;

        set<string> visited;
        stack<string> s;
        auto start=adj.begin()->first;
        s.push(start);

        while(!s.empty()){
            string city=s.top();s.pop();
            if (visited.find(city)==visited.end()){
                visited.insert(city);
                for (auto& neighbour : adj[city]){
                    if(visited.find(neighbour.first)==visited.end()){
                        s.push(neighbour.first);
                    }
                }
            }
        }return visited.size() == adj.size();
    }
};

int main(){
    graph g;

    g.addflight("new delhi","pune",7);
    g.addflight("pune","mumbai",2);
    g.addflight("mumbai","kolhapur",1);
    g.addflight("kolhapur","goa",3);

    g.display();

    if(g.isconnected()){
        cout<<"\n The flight network is connected . \n";
    }else{
        cout<<"\n The flight network is not connected . \n";
    }

    return 0;
}
