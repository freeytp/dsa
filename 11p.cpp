#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct student {
    int roll;
    string name,division,address;
};

void addstudent(){
    student s;
    ofstream file("student.txt", ios::app);
    cout<<"Enter roll,name,division,address(press enter after each)\n";
    cin>>s.roll>>s.name>>s.division>>s.address;
    file<<s.roll<<" "<<s.name<<" "<<s.division<<" "<<s.address<<"\n";
    file.close();
    cout<<"Student Added successfully !\n";
}

void displaystudent(){
    ifstream file("student.txt");
    int roll;
    bool found=false;
    cout<<"enter roll number to search : ";
    cin>>roll;

    student s;
    while(file >> s.roll >> s.name >> s.division >> s.address){
        if (s.roll==roll){
            cout<<"\nstudent with roll no. "<<roll<<"found \n";
            cout<<"Roll no. :"<<s.roll<<"\tName :"<<s.name<<"\tDivision :"<<s.division<<"\tAddress :"<<s.address<<"\n"<<endl;
            found=true;
            break;
        }
    }
    file.close();
    if (!found){
        cout<<"student with roll no. "<<roll<<" not found !!!\n";
    }
}

void deletestudent(){
    ifstream infile("student.txt");
    ofstream outfile("temp.txt");

    int roll;
    bool found=false;
    cout<<"Enter roll to delete :";
    cin>>roll;

    student s;
    while (infile >> s.roll >> s.name >> s.division >> s.address){
        if (s.roll==roll){
            found=true;
            continue;
        }
        outfile<<s.roll<<" "<<s.name<<" "<<s.division<<" "<<s.address<<"\n";
    }
    infile.close();
    outfile.close();
    remove("student.txt");
    rename("temp.txt","student.txt");

    if (found){
        cout<<"student deleted successfully!!!"<<endl;
    }else{
        cout<<"student with roll "<<roll<<" not found !\n";
    }
}

int main(){
    int choice;
    while(true){
        cout<<"--------Student info system----------- "<<endl;
        cout<<"1.Add student \n2.Delete student \n3.Display sttudent \n4.Exit \n";
        cout<<"----------------------------------------"<<endl;
        cout<<"enter your choice : ";
        cin>>choice;

        switch(choice){
            case 1:addstudent();break;
            case 2:deletestudent();break;
            case 3:displaystudent();break;
            case  4:return 0;
            default : cout<<"Invalid option\n ";
        }
    }
}
