//OOP project : Student Report Management System by Kritana Dahal & Pritika Sharma.
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class student //creating class
{
    int id;
    char name[50];
    int oop_marks, chem_marks, ect_marks, math_marks, micro_marks;
    double per;
    char grade;
public:
    void input();
    void display() const;
    void calculate();
    int retid() const;
};

void student::calculate() //function to claculate percentage & grade
{
    per = (oop_marks+chem_marks+ect_marks+math_marks+micro_marks)/5.0;
    if(per>=75)
        grade = 'A';
    else if(per>=60)
        grade = 'B';
    else if(per>=50)
        grade = 'C';
    else
        grade = 'F';
}

void student::input() //function to accept data form user
{
    cout<<"Enter the id of a student ";
    cin>>id;
    cout<<"\n\nEnter name ";
    cin.ignore();
    cin.getline(name, 50);
    cout<<"\nEnter marks obtained in Object Oriented Programming ";
    cin>>oop_marks;
    cout<<"\nEnter marks obtained in Engineering chemistry ";
    cin>>chem_marks;
    cout<<"\nEnter marks obtained in Electric Circuit Theory & Machine ";
    cin>>ect_marks;
    cout<<"\nEnter marks obtained in Engineering Mathematics ";
    cin>>math_marks;
    cout<<"\nEnter marks obtained in Microprocessor ";
    cin>>micro_marks;
    calculate();
}

void student::display() const //function to display the data
{
    cout<<"\nID - "<<id;
    cout<<"\nName - "<<name;
    cout<<"\nObject Oriented Programming = "<<oop_marks;
    cout<<"\nEngineering Chemistry = "<<chem_marks;
    cout<<"\nElectric Circuit Theory & Machine = "<<ect_marks;
    cout<<"\nEngineering Mathematics = "<<math_marks;
    cout<<"\nMicroprocessor = "<<micro_marks;
    cout<<"\nPercentage = "<<per;
    cout<<"\nGrade achieved is "<<grade;
}

int student::retid() const
{
    return id;
}

void create_record();            //to create record
void display_record(int);           //to display certain record
void display_all();              //to display all record
void delete_record(int);            //to delete any record
void modify_record(int);            // to modify any record

int main()
{
    char ch;
    cout<<setprecision(2);
    do
    {
        char ch;
        int num;
        system("cls");
        cout<<"\n\n\n\tSTUDENT REPORT MANAGEMENT SYSTEM";
        cout<<"\n\n\t1. Create Student Record";
        cout<<"\n\n\t2. Search Student Record";
        cout<<"\n\n\t3. Display All Students Records";
        cout<<"\n\n\t4. Delete Student Record";
        cout<<"\n\n\t5. Modify Student Record";
        cout<<"\n\n\t6.Exit";
        cout<<"\n\nEnter any Number(1-6)-";
        cin>>ch;
        system("cls");
        switch(ch)
        {
            case '1': create_record();
                     break;
            case '2': cout<<"\n\n\tEnter id number ";
                     cin>>num;
                     display_record(num);
                     break;
            case '3': display_all();
                     break;
            case '4': cout<<"\n\n\tEnter id number ";
                     cin>>num;
                     delete_record(num);
                     break;
            case '5': cout<<"\n\n\tEnter id number ";
                     cin>>num;
                     modify_record(num);
                     break;
            case '6': cout<<"Thank You!";exit(0);
        }
    }while(ch!='6');
    return 0;
}

void create_record() //writing details of student to file
{
    student s;
    ofstream outf;
    outf.open("student.dat",ios::binary|ios::app);
    s.input();
    outf.write(reinterpret_cast<char *> (&s), sizeof(student));
    outf.close();
    cout<<"\n\nStudent record has been created!";
    cin.ignore();
    cin.get();
}

void display_record(int n) //read certain record according to id
{
    student s;
    ifstream inf;
    inf.open("student.dat",ios::binary);
    if(!inf)
    {
        cout<<"File could not be opened... Press any key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag=false;
    while(inf.read(reinterpret_cast<char *> (&s), sizeof(student)))
    {
        if(s.retid()==n)
        {
            s.display();
        flag=true;
        }
    }
    inf.close();
    if(flag==false)
    cout<<"\n\nRecord does not exist!";
    cin.ignore();
    cin.get();
}

void display_all() //read all data from the file
{
    student s;
    ifstream inf;
    inf.open("student.dat",ios::binary);
    if(!inf)
    {
        cout<<"File could not be opened... Press any key to exit.";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\n\t\tAll Student Records\n\n";
    while(inf.read(reinterpret_cast<char* > (&s), sizeof(student)))
    {
        s.display();
        cout<<"\n\n-----------------------------------------\n";
    }
    inf.close();
    cin.ignore();
    cin.get();
}

void modify_record(int n) //modifying certain record of specific id
{
    bool found=false;
    student s;
    fstream f1;
    f1.open("student.dat",ios::binary|ios::in|ios::out);
    if(!f1)
    {
        cout<<"File could not be opened... Press any key to exit.";
        cin.ignore();
        cin.get();
        return ;
    }
    while(!f1.eof() && found==false)
    {
        f1.read(reinterpret_cast<char *> (&s), sizeof(student));
        if(s.retid()==n)
        {
            s.display();
            cout<<"\nEnter new student details:\n";
            s.input();
            int pos=(-1)*static_cast<int>(sizeof(s));
            f1.seekp(pos,ios::cur);
            f1.write(reinterpret_cast<char  *> (&s), sizeof(student));
            cout<<"\n\n\tRecord Updated!";
            found=true;
        }
    }
    f1.close();
    if(found==false)
    cout<<"\n\nRecord not found!";
    cin.ignore();
    cin.get();
}

void delete_record(int n) //delete certain record based on id
{
    student s;
    ifstream inf;
    inf.open("student.dat",ios::binary);
    if(!inf)
    {
        cout<<"File could not be opened... Press any key to exit.";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outf;
    outf.open("temp.dat",ios::out);
    inf.seekg(0, ios::beg);
    while(inf.read(reinterpret_cast<char *> (&s), sizeof(student)))
    {
        if(s.retid()!=n)
        {
            outf.write(reinterpret_cast<char *> (&s), sizeof(student));
        }
    }
    outf.close();
    inf.close();
    remove("student.dat");
    rename("temp.dat","student.dat");
    cout<<"\n\n\tRecord Deleted!";
    cin.ignore();
    cin.get();
}