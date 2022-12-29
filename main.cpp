/*

DTU University
Written by Abdullah Reda Bendary
Written by Abdulrahman Yasser
Date : 28/12/2022


*/


#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include <sstream>
#include <cstdlib>
using namespace std;
#define N 50
typedef struct student_info{
    int IDnumber;
    float gpa ;
    int year;
    std :: string firstname;
    std :: string lastname;
    std :: string department;

} student_info;

void addstudent(student_info student []);
void displaydata(student_info student []);
void menu();
void trash(student_info student []);
void deleterecord(student_info student []);
int Eindex(student_info student []);
int Edindex(student_info student []);
int Lindex(int idnum,student_info student []);
bool Sindex(int idno, student_info student []);
void modify(student_info student []);
void search(student_info student []);
bool id_checker(int idno);
void clearing();
void clean(student_info student []);
bool depa_check(char depa);
void print(student_info student []);
void pstat(int all,  int it,int  meca,int  autot, int po, int cooling , student_info student []);
 void stat(student_info student []);
void top(student_info student []);

int main()
{   
student_info student [N] ;
clean(student);
int choose;
do{
    clearing();
    cout<<"\n\nDelta University Student Management System  ";
    cout << "\n\nPlease choose one of the below options:   \n";
    cout << "______________________________\n";
    cout << "|                            |\n";
    cout << "|    1.ADD student           |\n";
    cout << "|    2.Modify student        |\n";
    cout << "|    3.Delete student        |\n";
    cout << "|    4.List                  |\n";
    cout << "|    5.Search for students   |\n";
    cout << "|    6.Trash                 |\n";
    cout << "|    7.Statistics            |\n";
    cout << "|    8.Top 5 in college      |\n";
    cout << "|    9.exit                  |\n";
    cout << "|____________________________|\n";

    cout << "\n>>" ;
    cin>>choose;
    clearing();

        switch(choose){
        case 1: addstudent(student);
            break;
        case 2: modify(student);
            break;
        case 3: deleterecord(student);
            break;
        case 4: displaydata(student);
            break;
        case 5: search(student);
            break;
        case 6: trash(student);
            break;
        case 7: stat(student);
            break;
        case 8: top(student);
            break;
        case 9: cout<<"\n\n\n\n\n\n\t\t                 GOOD BYE.....";
            break;
        default : cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }while(choose!=9);

    return 0;
}



void addstudent(student_info student [])
{
    string fn, ln;
    char depa;
    int year ;
    float gpa ;
    clearing();
    char try_again;
    do{
         // check if there space in the array
        int label=Eindex(student);
        if (label==-1){
            cout<<"\n\t\tno avialable space for new student\n";    return;
        }
        system("python ex.py SELECT_ID") ;
        int idno;
        bool exist  = false;
        clearing();
    do{ cout<<"\nStudent's ID: ";
            cin>>idno;
            if (idno == 0) 
            {   
                clearing();
                cout << "\nStudent ID can not be 0, TRY AGAIN";
            }
            exist = id_checker(idno);
            if (exist) 
            {   clearing();
                cout << "\nThe Student ID is Already EXIST, TRY AGAIN \n";  
            }
        }while(exist || idno==0);

        cout<<"\nFirst name: ";
        cin>>fn;
        cout<<"\nLast name: ";
        cin>>ln;

        enter_year_again :
        cout<<"\nYear (1, 2, 3, 4): ";
        cin>>year;
        if(year > 4 || year < 1) 

        {       clearing();
                cout << "year should be in range (1:4) try again\n";
                goto enter_year_again ;
        }
        enter_depa_again :
        // cout << "Meca(M) Auto(A) IT(I) Renewable energy(R) Cooling and air conditioning(C)" ;
        cout<<"\nDepartment(M, A, I, C, R): ";
        cin>>depa;
        depa = toupper(depa);
        if (!depa_check(depa)) 
        {   clearing();
            cout << "please enter a vaild department such as Meca(M) Auto(A) IT(I) Renewable energy(R) Cooling and air conditioning(C)\n" ;
            goto enter_depa_again ;
        }
        enter_gpa_again :
        cout<<"\nGPA: ";
        cin>>gpa;
        if (gpa > 5 || gpa < 0)
        {
            clearing();
            cout << "The GPA should be in range (0:5) try again\n";
            goto enter_gpa_again ;
        }
        student[label].IDnumber=idno;
        student[label].firstname=fn;
        student[label].lastname=ln;
        student[label].department=depa;
        student[label].year=year;
        student[label].gpa=gpa;
        string mess = "python ex.py INSERT ";
        mess.append(to_string(idno)) ;
        mess = mess + " " + fn + " "+ ln + " " + depa + " " ;
        mess.append(to_string(year)) ;
        mess = mess + " " + to_string(gpa) ;        
        system(mess.c_str()) ;   
        cout<<"\n\n\nAdd One More Student? (Y/N):  ";
        cin>>try_again;
    }while(try_again=='Y' || try_again=='y');
    
    clearing();
    cout << "\nTHE RECORD IS SUCCESSFULY CREATED..";      
}


  
bool Sindex(int idno , student_info student [])                // RETURN TRUE IF THE ID EXIST//
{
    for(int i=0; i < N; i++)
    {
        if (student[i].IDnumber==0)
            return false;
        if (student[i].IDnumber==idno)
            return true;
    }
    return false;
}


int Eindex(student_info student [])                   
{
    // SEARCH  EMPTY INDEX IN ARRAY//
    for(int i=0; i < N ;i++)
    {
        if (student[i].IDnumber==0)
            return i;
    }
    return -1;
}


int Lindex(int idnum ,student_info student [])            // SEARCH THE student INDEX IN ARRAY//
{
    for(int i=0; i < N ;i++)
    {
        if (student[i].IDnumber==0)
            return -1;
        if (student[i].IDnumber==idnum)
            return i;
    }
    return -1;
}


void menu()
{
    cout<<"\n\n TO UPDATE.. CHOOSE FROM THE MENUE";
    cout<<"\n   __________________________________";
    cout<<"\n   |                                |";
    cout<<"\n   |    1. UPDATE The STUDENT'S ID  |";
    cout<<"\n   |    2. UPDATE The FIRST Name    |";
    cout<<"\n   |    3. UPDATE The LAST NAME     |";
    cout<<"\n   |    4. UPDATE The YEAR NUMBER   |";    
    cout<<"\n   |    5. UPDATE The GPA           |";    
    cout<<"\n   |    6. UPDATE The DEPARTMENT    |";    
    // cout<<"\n   |       |";
    cout<<"\n   |________________________________|";
    cout << "\n\nPLEASE ENTER YOUR CHOICE:" ;
}

void modify(student_info student [])                        //   UPDATE student INFORMATION
{
        string fn , ln;
        char depa ;
        float gpa ;
        int year ;
        clean(student);

    clearing();
        cout<<"Modify Student\n";
        system("python ex.py SELECT_ID") ;
        int idno;
        bool exist  = true;
        // clearing();
        do{ cout<<"\nID NUMBER: ";
            cin>>idno;
            if (idno == 0) 
            
            {   clearing();
                cout << "\nStudent ID can not be 0, TRY AGAIN\n";
            }
            exist = id_checker(idno);
            if (!exist) 
            {   clearing();
                cout << "\nThe Student ID isn't EXIST, TRY AGAIN \n";  
            }
        }while(!exist || idno==0);  
    
    int upt;
    char try_again ;
    do{clearing();
        menu();
        cin>>upt;
        string mess = "python ex.py UPDATE " ; // keyword
        mess.append(to_string(idno));        // the id 
        switch(upt){
        case 1:
            mess.append(" stu_id ");    // which 
            std :: cout<<"\nNew ID: ";
            cin>>idno;
            mess.append(to_string(idno)); // the updation
            system(mess.c_str()) ;
            // std :: cout<<"\n\nTHANK YOU";
            break;
        case 2:
            mess.append(" fname ");    // which 
            cout<<"\n\nNew fname:  ";
            cin>>fn;
            mess.append(fn);    // the updation
            system(mess.c_str()) ;
            // cout<<"\n\nTHANK YOU ";
            break;
        case 3:

            mess.append(" lname ");    // which 
            cout<<"\n\nNew lname:  ";
            cin>>ln;
            mess.append(ln);    // the updation
            system(mess.c_str()) ;
            // cout<<"\n\nTHANK YOU";
            break;
        case 4:

            mess.append(" year ");    // which 
            cout<<"\n\nNew Phone Number:  ";
            cin>>year;
            mess.append(to_string(year));    // the updation
            system(mess.c_str()) ;
            // cout<<"\n\nTHANK YOU";
            break;
        case 5:

            mess.append(" gpa ");    // which 
            cout<<"\n\nNew GPA:  ";
            cin>>gpa;
            mess.append(to_string( gpa));    // the updation
            system(mess.c_str()) ;
            // cout<<"\n\nTHANK YOU";
            break;
        case 6:

            mess.append(" depa ");    // which 
            cout<<"\n\nNew Department:  ";
            cin>>gpa;
            mess.append(to_string( depa));    // the updation
            system(mess.c_str()) ;
            // cout<<"\n\nTHANK YOU";
            break;
        
        default:

        clearing();
        cout<<"\n\nINVALID ENTERY ... TRY AGAIN ";
        break;
        }
        cout<<"\n\nUpdate Another Info ?(Y/N): ";
        cin>>try_again;
    }while(try_again=='Y' || try_again=='y');

    clearing();
    cout<<"\nTHE student FILE HAS BEEN UPDATED..";
}


void displaydata(student_info student []){
    
    system("python ex.py DISPLAY");
    ifstream file ;
    file.open("temp.csv") ;
      string line ; 
      for (int i=0; !file.eof(); i++){
        getline(file, line);
        string temp;
        stringstream inputLine(line);
        getline(inputLine, temp , ',');
        student[i].IDnumber = atoi( temp.c_str() );
        getline(inputLine, student[i].firstname, ',');
        getline(inputLine, student[i].lastname, ',');
        getline(inputLine, student[i].department, ',');

        getline(inputLine, temp, ',');
        student[i].year = atoi(temp.c_str());
        getline(inputLine, temp, ',');
        student[i].gpa = atof(temp.c_str());

        // getline(file,line);
        }
  
    file.close();
   print(student);



}

void deleterecord(student_info student []){
    
    clearing();
    int idno;
    char try_again ;
    do{     
        
        short time = 0 ;
        system("python ex.py SELECT_ID") ;
        bool exist  = false;
        clearing();
        // cout<<"\t\t\t\tDelete Page\n\n";

        do{ 
                  
            cout<<"\nStudent ID : ";
            cin>>idno;
            if (idno == 0) 
            {
                 time++;
                if (time == 3) 
                {
                    clearing();
                cout << "\n\nYou Enterd Three Wrong Entry , Please Check Your List First And Come Latter :) ";
                return ;
                }
                    clearing();

                cout << "Student ID can not be 0, TRY AGAIN";
            }

            exist = id_checker(idno);
            if (!exist) 
            {
                time++;
                if (time == 3) 
                {
                     clearing();

                cout << "\n\nYou Enterd Three Wrong Entry , Please Check Your List First And Come Latter :) ";
                return ;
                }
                 clearing();

                cout << "The Student ID Isn't EXIST, TRY AGAIN";  
            }
            

        }while(!exist || idno==0);

            string mess = "python ex.py DEL ";
            mess.append(to_string(idno));
            system(mess.c_str());
            clean(student) ;
            cout<<"Delete One More Student? (Y/N)";
            cin >> try_again ; 
            // cout<<"\n DONE The Students Is Deleted... ";
     }while(try_again=='Y' || try_again=='y');
     clearing();
     cout<<"'\nStudent cleared successfully ....";
     return ;
}

int Edindex(student_info student [])                    // SEARCH  EMPTY INDEX IN ARRAY
{
    for(int i=0; i < N;i++)
    {
        if (student[i].IDnumber==0)
            return i;
    }
    return -1;
}



void trash(student_info student [])
{
    system("python ex.py TRASH");
    ifstream file ;
    clean(student);

    file.open("temp.csv") ;
    while (!file.eof()){
      string line ; 
      for (int i=0; getline(file, line); i++){
        string temp;
        stringstream inputLine(line);
        getline(inputLine, temp , ',');
        student[i].IDnumber = atoi( temp.c_str() );
        getline(inputLine, student[i].firstname, ',');
        getline(inputLine, student[i].lastname, ',');
        getline(inputLine, student[i].department, ',');
        getline(inputLine, temp, ',');
        student[i].year = atoi(temp.c_str());
        getline(inputLine, temp, ',');
        student[i].gpa = atof(temp.c_str());
        // getline(file,line);
        }
  }
    file.close();

    print(student) ;


}

void search(student_info student []){
    
    // clearing();
    string fn;
    ifstream file ;
    char try_again ;
    do { 
        short time = 0;
        clearing();
    do { 
    clean(student);
        file.open("temp.csv") ;
        // cout << "\t\t\tThe Search Page\n\n" ;
        cout<<"Student's Name:";
        cin>>fn;
        string mess = "python ex.py SEARCH ";
        mess.append(fn);
        system(mess.c_str()) ;
        if (file.peek() == std::ifstream::traits_type::eof())
        {    // dont ask about that condition 
            time++;
                file.close() ;
            if (time == 3) 
            {
                clearing();

            cout << "\n\nYou Enterd Three Wrong Entry , Please Check Your List First And Come Latter :) ";
            return ;
            }
            clearing();
            cout<<"Not found\n";
        }
    }while(file.peek() == std::ifstream::traits_type::eof());
      string line ; 
      for (int i=0; !file.eof(); i++){
        getline(file, line);
        string temp;
        stringstream inputLine(line);
         getline(inputLine, temp , ',');
        student[i].IDnumber = atoi( temp.c_str() );
        getline(inputLine, student[i].firstname, ',');
        getline(inputLine, student[i].lastname, ',');
        getline(inputLine, student[i].department, ',');
        getline(inputLine, temp, ',');
        student[i].year = atoi(temp.c_str());
        getline(inputLine, temp, ',');
        student[i].gpa = atof(temp.c_str());
        // getline(file,line);
        }
        file.close() ;
    
       print(student);
        cout << "\n\nSearch One More? (Y/N) : ";
        cin >> try_again ;
    }while(try_again == 'y' || try_again == 'Y');
    

        
 }



 void stat(student_info student []){
    
    string mess = "python ex.py STA" ;
    system(mess.c_str());
   ifstream file ;
   int all , it, meca , autot, po, cooling ;
    file.open("temp.csv");
    string temp ;
    while(!file.eof()){
    getline(file, temp);
    all = atoi(temp.c_str());
    
    getline(file, temp);
    it = atoi(temp.c_str());
    
    getline(file, temp);
    meca = atoi(temp.c_str());
    
    getline(file, temp);
    autot = atoi(temp.c_str());
    
    getline(file, temp);
    po = atoi(temp.c_str());
    
    getline(file, temp);
    cooling = atoi(temp.c_str());
        
        getline(file, temp);
  
        }
        file.close();
    

    pstat(all, it, meca, autot, po, cooling , student);
    
        // getline(file,line);
 }  
  
 



bool id_checker(int idno){
    ifstream file ;
    file.open("temp.csv");
    while(!file.eof()){
    string id ;
    getline(file, id);
    if (idno == atoi(id.c_str())) {
        file.close();
        return true ;
        }
    }
    file.close();
    return false;

}

void clearing()
{
   system("cls");
//    cout << "clear" << endl;
}

void clean(student_info student []){
    
    for (int i=0;i<N;i++){
    student[i].IDnumber = 0;
    student[i].firstname = '\0' ;
    student[i].lastname = '\0';
    student[i].department = '\0';
    student[i].year = '\0';
    student[i].gpa= '\0';
    }
}

bool depa_check(char depa){

   if (depa=='A' || depa=='I' || depa=='M' ||depa=='C'|| depa=='R' ) return true;
   return false ;
}



 string TAP = "\t\t\t";


void print(student_info student [])
{
  for (int i = 0 ; i<N ; i++)
  {   
    if (student[i].IDnumber == 0) break;
    if (i == 0)
    {
   cout<<"________________________________________________________________________________________\n\n";
//    cout<<"                                                                                   |\n";
   cout<<"ID"<<TAP<<"fname"<<TAP<<"lname"<<TAP<<"Department"<<TAP<<"year"<< TAP<< "GPA"<< endl;
    }
    // cout<<"___________________________________________________________________________________\n";
    cout<<"\n"<<student[i].IDnumber<<TAP<<student[i].firstname<<TAP<<student[i].lastname<<TAP<< "\t"<<student[i].department<<TAP<<student[i].year<< TAP<< student[i].gpa << endl;
  }   cout<<"________________________________________________________________________________________\n\n";
}




void top(student_info student [])
{
    clean(student);
    system("python ex.py top");
    ifstream file ;
    file.open("temp.csv") ;
      string line ; 
      for (int i=0; !file.eof(); i++){
        getline(file, line);
        string temp;
        stringstream inputLine(line);
        getline(inputLine, temp , ',');
        student[i].IDnumber = atoi( temp.c_str() );
        getline(inputLine, student[i].firstname, ',');
        getline(inputLine, student[i].lastname, ',');
        getline(inputLine, student[i].department, ',');

        getline(inputLine, temp, ',');
        student[i].year = atoi(temp.c_str());
        getline(inputLine, temp, ',');
        student[i].gpa = atof(temp.c_str());

        // getline(file,line);
        }
    
    file.close();
   print(student);

}

void pstat(int all,  int it,int  meca,int  autot, int po, int cooling, student_info student []){
cout<<"DTU Universty has ( " << all <<" )  students"<<endl;
    cout<<"IT Department has ( " << it <<" ) students"<<endl;
    cout<<"Meca Department has ( " << meca<<" ) student"s<<endl;
    cout<<"AUTO Department has ( " <<  autot<<" ) students"<<endl;
    cout<<"Energy Department has ( "<< po <<" ) students"<<endl;
    cout<<"Cooling Department has ( " << cooling <<" )students"<<endl;



    
}




