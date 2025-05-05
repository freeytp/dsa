#include<iostream>
#include<queue>
#include<vector>
using namespace std;

void FindMaxMin(const vector<int>& marks){
    priority_queue<int> maxheap(marks.begin(),marks.end());
    priority_queue<int , vector<int>,greater<int>> minheap(marks.begin(),marks.end());

    cout<<"Maximum Marks : "<<maxheap.top()<<endl;
    cout<<"Minimum Marks : "<<minheap.top()<<endl;

}

int main(){
    int n,mark;
    cout<<"Enter no. of students : ";
    cin>>n;

    vector<int> marks;
    for (int i=0 ; i<n ; i++){
        cout<<"Enter marks of student "<<i+1<<" :";
        cin>>mark;
        marks.push_back(mark);
    }

    FindMaxMin(marks);


    return 0;
}