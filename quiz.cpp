#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cstring>
#include<string>
#include<fstream>
#include "conio2.h"
#include"quiz.h"
using namespace std;


void Admin::create_admin(string userid,string password,string username){
        fstream fobj("c:\\Quiz App\\Admin.bin",ios::in|ios::binary);
        if(!fobj){
                fobj.open("c:\\Quiz App\\Admin.bin",ios::out|ios::binary);
                Admin adminObj;
                adminObj.setUserDetails(userid,password,username);
                fobj.write((char*)&adminObj,sizeof(Admin));
        }
        fobj.close();
}

void User::setUserDetails(string userid,string pwd,string username){
        strcpy(this->userid,userid.c_str());
        strcpy(this->pwd,pwd.c_str());
        strcpy(this->username,username.c_str());

}
//**************************************Validating user type (Admen/student)***************************
int User ::input(){
        clrscr();
        gotoxy(1,1);
        textcolor(LIGHTGREEN);
        for(int i=1;i<=80;i++)
                    cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
                    cout<<"*";
        gotoxy(57,4);
        textcolor(WHITE);
        cout<<"Press 0 to exit/GoBack";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APPLICATION";
        gotoxy(1,8);
        textcolor(YELLOW);
        for(int i=1;i<=80;i++)
                    cout<<"*";
        gotoxy(1,17);
        for(int i=1;i<=80;i++)
                    cout<<"*";
        gotoxy(28,11);
        cout<<"Enter UserID:";
        textcolor(WHITE);
        cin.getline(userid,20);
        if(strcmp(userid,"0")==0)
                    return 0;
        char ch;
        int i=0;
        textcolor(YELLOW);
        gotoxy(28,12);
        cout<<"Enter Password:";
        textcolor(WHITE);
        while(true){
                    ch=getch();
                    if(ch==13)  //ascii of enter
                            break;
                    if(ch==8){  // ascii of backspace
                            if(i==0)  //if backspace entered as 1st character of password
                                    continue;
                            cout<<"\b \b";
                            i--;
                            continue;
                    }
                    cout<<ch;
                    delay(200);
                    cout<<"\b*";
                    pwd[i]=ch;
                    i++;
        }
        pwd[i]='\0';
        if(strcmp(pwd,"0")==0)
                    return 0;
        return 1;
}
//****************************************Checking user Exist or not*******************************************
int User::checkUserExists(string usertype){
        if(strcmp(userid,"")==0 || strcmp(pwd,"")==0){
                gotoxy(28,20);
                textcolor(LIGHTRED);
                cout<<"BOTH THE FIELDS ARE MANDATORY";
                getch();
                return 0;
        }
        ifstream fin;
        User *uptr;
        if(usertype=="admin"){
                fin.open("c:\\Quiz App\\Admin.bin",ios::in|ios::binary);
                uptr=new Admin;
        }
        else if(usertype=="student"){
                fin.open("c:\\Quiz App\\Student.bin",ios::in|ios::binary);
                uptr=new Student;
        }

        bool useridfound=0,pwdfound=0;
        while(1){
                fin.read((char*)uptr,sizeof(*uptr));
                if(fin.eof())
                        break;
                if(strcmp(userid,uptr->userid)==0){
                        if(strcmp(pwd,uptr->pwd)==0){
                                useridfound=pwdfound=1;
                                break;
                       }
                       useridfound=1;
                }
        }
        bool result=0;
        if(useridfound==0){
                gotoxy(28,18);
                textcolor(LIGHTRED);
                cout<<"No such user exists!";
                getch();
        }
        else if(pwdfound==0){
                gotoxy(28,18);
                textcolor(LIGHTRED);
                cout<<"Invalid password!";
                getch();
        }
        else{
                result=1;
                strcpy(username,uptr->username);  //for welcome by name when login accepted.
        }
        fin.close();
        return result;
}
string User::getName(){
        string USERNAME(username);  //converting char array to string using string constructor
        return USERNAME;
}
//************************************ADDING QUESTION *************************************
void Admin::addQuestion(){
        Question quesObj;
        quesObj.add();
        clrscr();
}
void Question::add(){
        quesid=0;
        fstream fobj("c:\\Quiz App\\Question.bin",ios::app|ios::in|ios::binary);
        if(!fobj){
                gotoxy(32,18);
                textcolor(LIGHTRED);
                cout<<"Sorry ! File can not be opened.";
                getch();
                return;
        }
        fobj.seekg(0,ios::end);
        if(fobj.tellg()!=0){
                int x=sizeof(*this);          // sometimes direct calculation did't works
                fobj.seekg(-x,ios::end);
                fobj.read((char*)this,sizeof(*this));
        }
        char uchoice,valid;
        do{
                clrscr();
                textcolor(WHITE);
                gotoxy(57,4);
                cout<<"press 0* to Exit/Go Back";
                textcolor(LIGHTGREEN);
                gotoxy(1,1);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                gotoxy(1,3);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                gotoxy(32,2);
                textcolor(LIGHTRED);
                cout<<"QUIZ APPLICATION";
                textcolor(WHITE);
                gotoxy(24,5);
                cout<<"***** ADD QUESTION DETAILS *****";
                gotoxy(1,8);
                textcolor(YELLOW);
                string str;
                cout<<"Enter question:";
                textcolor(WHITE);
                getline(cin,str,'*');         //use of * to handle multiple line.line will end by *
                if(strcmp(str.c_str(),"0")==0){
                        gotoxy(1,22);
                        textcolor(LIGHTRED);
                        cout<<"Closing Add Question!";
                        getch();
                        fobj.close();
                        return;
                }
                strncpy(ques,str.c_str(),999);     //question can be up to 999 character only
                textcolor(LIGHTGREEN);
                cout<<endl<<"Carries marks:";
                textcolor(YELLOW);
                cin>>tot_marks;
                textcolor(LIGHTGREEN);
                cout<<endl<<"OPTIONS"<<endl<<endl;

                textcolor(YELLOW);
                cout<<"(a)";
                cin.ignore();
                textcolor(WHITE);
                getline(cin,str);
                strncpy(op1,str.c_str(),99);

                textcolor(YELLOW);
                cout<<"(b)";
                textcolor(WHITE);
                getline(cin,str);
                strncpy(op2,str.c_str(),99);

                textcolor(YELLOW);
                cout<<"(c)";
                textcolor(WHITE);
                getline(cin,str);
                strncpy(op3,str.c_str(),99);

                textcolor(YELLOW);
                cout<<"(d)";
                textcolor(WHITE);
                getline(cin,str);
                strncpy(op4,str.c_str(),99);
                do{
                        gotoxy(1,19);
                        textcolor(YELLOW);
                        cout<<endl<<"Enter correct ans(a/b/c/d):  \b";
                        cin>>ans;
                        if(ans>='a' && ans <= 'd')
                                valid=true;
                        else{
                                gotoxy(24,22);
                                textcolor(LIGHTRED);
                                cout<<"Invalid choice. Please try again";
                                getch();
                                valid=false;
                        }
                }while(valid==false);
                quesid++;
                fobj.write((char*)this,sizeof(*this));   //this has the address of current object
                gotoxy(24,22);
                printf("\t\t\t\t\t\t\t");
                gotoxy(34,22);
                textcolor(LIGHTGREEN);
                cout<<"QUESTION ADDED SUCCESSFULLY!";
                getch();
                gotoxy(1,24);
                textcolor(MAGENTA);
                cout<<endl<<"Do you want to add more questions (Y/y/N/n):";
                textcolor(WHITE);
                cin>>uchoice;
        }while(uchoice=='y' || uchoice=='Y');
        cin.ignore();//just
        fobj.close();
}
//******************************************SHOWING QUESTION*************************************
void Admin::viewQuestion(){
        Question quesObj;
        quesObj.viewQuestion();
        clrscr();
}
void Question::viewQuestion(){
        ifstream fin("c:\\Quiz App\\Question.bin",ios::in|ios::binary);
        if(!fin){
                gotoxy(1,10);
                textcolor(LIGHTRED);
                cout<<"No questions have been added yet!";
                getch();
                return;
        }
        fin.seekg(0,ios::end);
        if(fin.tellg()==0){
                gotoxy(1,10);
                textcolor(LIGHTRED);
                cout<<"No questions present in the file!";
                getch();
                fin.close();
                return;
        }
        clrscr();
        fin.seekg(0);
        while(1){
                textcolor(LIGHTGREEN);
                gotoxy(1,1);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                gotoxy(1,3);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                gotoxy(32,2);
                textcolor(LIGHTRED);
                cout<<"QUIZ APPLICATION";
                textcolor(WHITE);
                gotoxy(25,5);
                cout<<"***** SHOW QUESTION DETAILS *****";
                gotoxy(1,7);
                textcolor(YELLOW);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                fin.read((char*)this,sizeof(*this));
                if(fin.eof()){
                        cout<<endl;
                        textcolor(LIGHTRED);
                        gotoxy(35,10);
                        cout<<"NO MORE QUESTIONS PRESENT !";
                        getch();
                        break;
                }
                else{
                        show();         //<--- calling obj of show()  will be same who call the viewQuestion().
                        getch();
                        clrscr();
                }
        }
       fin.close();
}
void Question::show(){
        cout<<endl;
        textcolor(YELLOW);
        cout<<"Q."<<quesid<<" ";
        cout<<ques<<endl;
        cout<<"Carries Marks: "<<tot_marks<<endl;
        cout<<"a. "<<op1<<endl;
        cout<<"b. "<<op2<<endl;
        cout<<"c. "<<op3<<endl;
        cout<<"d. "<<op4<<endl;
        textcolor(LIGHTGREEN);
        cout<<endl<<"Correct Option: "<<ans;
}
//******************************************REMOVING QUESTION*************************
void Admin::removeQuestion(){
        Question quesObj;
        quesObj.Remove();
        clrscr();
}
void Question::Remove(){
         char uuchoice;
         do{
                clrscr();
                textcolor(WHITE);
                gotoxy(57,4);
                cout<<"Press 0 to Exit/Go Back";
                textcolor(LIGHTGREEN);
                gotoxy(1,1);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                gotoxy(1,3);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                gotoxy(32,2);
                textcolor(LIGHTRED);
                cout<<"QUIZ APPLICATION";
                textcolor(WHITE);
                gotoxy(25,5);
                cout<<"***** REMOVE QUESTION DETAILS *****";
                ifstream fin("c:\\Quiz App\\Question.bin",ios::in|ios::binary);
                if(!fin){
                            gotoxy(33,14);
                            textcolor(LIGHTRED);
                            cout<<"Sorry ! File can not be opened.";
                            getch();
                            return;
                }
                fin.seekg(0,ios::end);
                if(fin.tellg()==0){
                            gotoxy(35,10);
                            textcolor(LIGHTRED);
                            cout<<"No questions available for deletion!";
                            getch();
                            fin.close();
                            return;
                }
                gotoxy(1,8);
                textcolor(YELLOW);
                cout<<"Enter question ID:";
                bool found=false,valid;
                int id;
                ofstream fout("c:\\Quiz App\\temp.bin",ios::out|ios::binary);
                if(!fout){
                            gotoxy(33,14);
                            textcolor(LIGHTRED);
                            cout<<"Sorry ! Removal not possible.";
                            getch();
                            fin.close();
                            return;
                }
                fin.seekg(0);
                do{
                            valid=true;
                            cin>>id;
                            if(id==0){
                                        fin.close();
                                        fout.close();
                                        remove("temp.bin");
                                        cin.ignore();//just----------------------------------------------------------------
                                        return;//just-----------------------------------------------------------------------
                            }
                            if(id<0){
                                        valid=false;
                                        gotoxy(1,24);
                                        textcolor(LIGHTRED);
                                        cout<<"\t\t\t\t\t\t\t\t\t\rInvalid Question ID";
                                        getch();
                                        gotoxy(19,8);
                                        cout<<"\t\t\t\t\t\t\t\t\t\t\t\t";
                                        textcolor(WHITE);
                                        gotoxy(19,8);
                            }
                            else{
                                        while(true){
                                                    fin.read((char*)this,sizeof(*this));
                                                    if(fin.eof())
                                                                break;
                                                    if(this->quesid==id ){
                                                                found=true;
                                                                continue;
                                                    }
                                                    else
                                                                fout.write((char*)this,sizeof(*this));
                                        }
                                        fout.close();
                                        fin.close();
                                        if(found){
                                                    textcolor(LIGHTGREEN);
                                                    gotoxy(1,15);
                                                    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\rQuestion Removed Successfully!";
                                                    getch();
                                                    remove("c:\\Quiz App\\Question.bin");
                                                    rename("c:\\Quiz App\\temp.bin","c:\\Quiz App\\Question.bin");
                                        }
                                        else{
                                                    textcolor(LIGHTRED);
                                                    gotoxy(1,15);
                                                    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\rQuestion ID Not Found!"<<endl;
                                                    getch();
                                                    remove("c:\\Quiz App\\temp.bin");
                                        }
                            }
                }while(valid==false);
                textcolor(LIGHTMAGENTA);
                gotoxy(1,22);
                cout<<"Do you want to remove more question(Y/y/N/n):";
                textcolor(WHITE);
                cin>>uuchoice;
        }while(uuchoice=='y' || uuchoice=='Y');
        cin.ignore();
}
//*************************************ADDING STUDENTS**********************************
void Admin::addStudent(){
        Student studobj;
        studobj.add();
}
void Student::add(){
        char uchoice;
        int id;
        char stuid[10];
        string str;
        fstream fobj("c:\\Quiz App\\Student.bin",ios::app|ios::in|ios::binary);
        fobj.seekg(0,ios::end);
        if(fobj.tellg()==0)
                id=1;
        else{
                int x=sizeof(*this);
                fobj.seekg(-x,ios::end);
                fobj.read((char*)this,sizeof(*this));
                char *pos=strchr(userid,'-');
                if(pos!=NULL){
                        id=atoi(pos+1);
                        id++;
                }
        }
        fobj.seekg(0,ios::end);
        do{
                clrscr();
                textcolor(WHITE);
                gotoxy(58,4);
                cout<<"Press 0 to Exit/Go Back";
                gotoxy(37,2);
                textcolor(LIGHTRED);
                cout<<"QUIZ APPLICATION";
                textcolor(LIGHTGREEN);
                gotoxy(1,1);
                for(int i=1;i<=80;i++)
                        cout<<"~";
                gotoxy(1,3);
                for(int i=1;i<=80;i++)
                        cout<<"~";
                textcolor(WHITE);
                gotoxy(25,5);
                cout<<"***** ADD STUDENT DETAILS *****";
                gotoxy(1,8);
                textcolor(YELLOW);
                cout<<"Enter Sudent Name:";
                textcolor(WHITE);
                getline(cin,str);
                strncpy(username,str.c_str(),49);
                if(strcmp(username,"0")==0){
                        gotoxy(1,24);
                        textcolor(LIGHTRED);
                        cout<<"Cancelling Add Student....press any key to exit"<<endl;
                        getch();
                        fobj.close();
                        return;
                }
                textcolor(YELLOW);
                cout<<"Enter Student Password:";
                textcolor(WHITE);
                getline(cin,str);
                strncpy(pwd,str.c_str(),19);                                    // printf()   <-- general printf
                if(strcmp(pwd,"0")==0){                                         //  sprintf() <-- String printf
                        gotoxy(1,24);                                           // fprintf()  <--- File printf
                        textcolor(LIGHTRED);                                    // cprintf()  <-- In Turbo ,color printf
                        cout<<"Cancelling Add Student...."<<endl;
                        getch();
                        fobj.close();
                        return;
                }
                sprintf( stuid,"STU-%d",id);  // <----- convert integer i.e id to string/char.STU will added and store in stuid
                strcpy(userid,stuid);
                fobj.write((char*)this,sizeof(*this));
                gotoxy(30,15);
                textcolor(LIGHTGREEN);
                cout<<"STUDENT ADDED SUCCESSFULLY!";
                cout<<endl<<"STUDENT ID IS :"<<userid;
                getch();
                gotoxy(1,20);
                textcolor(MAGENTA);
                cout<<"Do you want to add more student (Y/y/N/n) ?";
                textcolor(WHITE);
                cin>>uchoice;
               //cin.ignore();
                id++;
        }while(uchoice=='Y' || uchoice=='y');
        cin.ignore();
        fobj.close();
}
//*******************************VIEW STUDENTS************************************
void Admin::viewStudent(){
        Student studObj;
        studObj.showStudentDetails();
        clrscr();
}
void Student::showStudentDetails(){
        clrscr();
        ifstream fin("c:\\Quiz App\\Student.bin",ios::in|ios::binary);
        if(!fin){
                gotoxy(1,10);
                textcolor(LIGHTRED);
                cout<<"No Student have been added yet!";
                getch();
                return;
        }
        fin.seekg(0,ios::end);
        if(fin.tellg()==0){
                gotoxy(1,10);
                textcolor(LIGHTRED);
                cout<<"No Students present in the file!";
                getch();
                fin.close();
                return;
        }
        clrscr();
        fin.seekg(0);
        while(1){
                textcolor(LIGHTGREEN);
                gotoxy(1,1);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                gotoxy(1,3);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                gotoxy(32,2);
                textcolor(LIGHTRED);
                cout<<"QUIZ APPLICATION";
                textcolor(WHITE);
                gotoxy(25,5);
                cout<<"***** SHOW STUDENT DETAILS *****";
                gotoxy(1,7);
                textcolor(YELLOW);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                fin.read((char*)this,sizeof(*this));
                if(fin.eof()){
                        cout<<endl;
                        textcolor(LIGHTRED);
                        gotoxy(35,10);
                        cout<<"NO MORE STUDENTS PRESENT !";
                        getch();
                        break;
                }
                else{
                        show();
                        getch();
                        clrscr();
                }
        }
       fin.close();
}
void User::show(){
        cout<<endl;
        textcolor(YELLOW);
        cout<<"User ID: ";
        textcolor(LIGHTGREEN);
        cout<<userid<<endl;

        textcolor(YELLOW);
        cout<<"User Name: ";
        textcolor(LIGHTGREEN);
        cout<<username<<endl;

        textcolor(YELLOW);
        cout<<"Password: ";
        textcolor(LIGHTGREEN);
        cout<<pwd<<endl;
}
////******************************STUDENT REMOING***************************

void Admin::removeStudent(){
        Student studobj;
        studobj.Remove();
        clrscr();
}
void Student::Remove(){
        char uuchoice;
        do{
                clrscr();
                textcolor(WHITE);
                gotoxy(58,4);
                cout<<"Press 0 to Exit/Go Back";
                textcolor(LIGHTGREEN);
                gotoxy(1,1);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                gotoxy(1,3);
                for(int i=1;i<=80;i++)
                        cout<<"*";
                gotoxy(32,2);
                textcolor(LIGHTRED);
                cout<<"QUIZ APPLICATION";
                textcolor(WHITE);
                gotoxy(25,5);
                cout<<"***** REMOVE STUDENT DETAILS *****";
                ifstream fin("c:\\Quiz App\\Student.bin",ios::in|ios::binary);
                if(!fin){
                        gotoxy(35,10);
                        textcolor(LIGHTRED);
                        cout<<"Sorry! File cannot open!";
                        getch();
                        return;
                }
                fin.seekg(0,ios::end);
                if(fin.tellg()==0){
                        gotoxy(35,10);
                        textcolor(LIGHTRED);
                        cout<<"No student available for deletion!";
                        getch();
                        fin.close();
                        return;
                }
                gotoxy(1,8);
                textcolor(YELLOW);
                cout<<"Enter Student ID: STU-";
                bool found=false,valid;
                int id,k;
                ofstream fout("c:\\Quiz App\\temp.bin",ios::out|ios::binary);
                if(!fout){
                        gotoxy(35,10);
                        textcolor(LIGHTRED);
                        cout<<"Sorry! removal not possible!";
                        getch();
                        fin.close();
                        return;
                }
                fin.seekg(0);
                do{
                        valid=true;
                        cin>>id;
                        if(id==0){
                                fin.close();
                                fout.close();
                                remove("c:\\Quiz App\\temp.bin");
                                return;
                        }
                        if(id<0){
                                valid=false;
                                gotoxy(1,24);
                                textcolor(LIGHTRED);
                                cout<<"\t\t\t\t\t\t\t\t\t\tInvalid Student ID";
                                getch();
                                gotoxy(19,8);
                                cout<<"'\t\t\t\t\t\\t\t";
                                gotoxy(19,8);
                                textcolor(WHITE);
                        }
                        else{
                                AdminViewPerformance obj;
                                while(true){
                                            fin.read((char*)this,sizeof(*this));
                                            if(fin.eof())
                                                    break;
                                            char*pos=strchr(userid,'-');
                                            if(pos!=NULL)
                                                    k=atoi(pos+1);
                                            if(k==id){
                                                    found=true;
                                                    string id=userid;
                                                    obj.removePerformance(id);
                                                    continue;
                                            }
                                            else
                                                    fout.write((char*)this,sizeof(*this));
                                }
                        fout.close();
                        fin.close();
                        if(found){
                                textcolor(LIGHTGREEN);
                                gotoxy(1,15);
                                cout<<"\t\t\t\t\t\t\t\t\t\tStudent Removed Successfully!";
                                remove ("c:\\Quiz App\\Student.bin");
                                rename("c:\\Quiz App\\temp.bin","c:\\Quiz App\\Student.bin");
                        }
                        else{
                                textcolor(LIGHTRED);
                                gotoxy(1,15);
                                cout<<"\t\t\t\t\t\t\rStudent Id Not Found!";
                                getch();
                                remove("c:\\Quiz App\\temp.bin");
                        }
                    }
                }while(valid==false);
                textcolor(MAGENTA);
                gotoxy(1,22);
                cout<<"Do you want to remove more student(Y/y/N/n):";
                textcolor(WHITE);
                cin>>uuchoice;
        }while(uuchoice=='y' || uuchoice=='Y');
        cin.ignore();
}



//************************************************REMOVE PERFORMANCE*********************************************



void AdminViewPerformance::removePerformance(string user_id){
      fstream fin("c:\\Quiz App\\Performance.bin",ios::in|ios::binary);
        if(!fin)
                return;

        fin.read((char*)this,sizeof(*this));
        if(fin.eof()){
                fin.close();
                return;
        }
        ofstream fout("c:\\Quiz App\\temp2.bin",ios::out|ios::binary);
                if(!fout){
                        gotoxy(35,10);
                        textcolor(LIGHTRED);
                        cout<<"Sorry! removal not possible!";
                        getch();
                        fin.close();
                        return;
                }

        fin.seekg(0);
        int found;
        while(true){
                fin.read((char*)this,sizeof(*this));
                if(fin.eof())
                        break;
                if(strcmp(stuid,user_id.c_str())==0){
                        found=1;
                       continue;
                }
                else
                       fout.write((char*)this,sizeof(*this));
        }
        fout.close();
        fin.close();
        if(found){
                remove ("c:\\Quiz App\\Performance.bin");
                rename("c:\\Quiz App\\temp2.bin","c:\\Quiz App\\Performance.bin");
        }
        else
                remove("c:\\Quiz App\\temp2.bin");
}


//******************************STUDENT RELATED FUNCTIONS************************

void Student::quiz(){
        Question quesObj;
        quesObj.startQuiz(userid);
}
void Question::startQuiz(string id){
        ifstream fin("c:\\Quiz App\\Question.bin",ios::in|ios::binary);
        if(!fin){
                gotoxy(28,20);
                textcolor(LIGHTRED);
                cout<<"No Question Have Been Added Yet!";
                getch();
                return;
        }
        vector<Question> vecQues;
        while(true){
                fin.read((char*)this,sizeof(*this));
                if(fin.eof())
                        break;
                vecQues.push_back(*this);
        }
        fin.close();
        vector<int> vecRand;
        srand((unsigned int)time(NULL));      //s means seed
        int randno;
        while(1){
                randno=rand()%vecQues.size();
                auto it=find(vecRand.begin(), vecRand.end(), randno);
                if(it!=vecRand.end())
                        continue;
                vecRand.push_back(randno);
                if(vecQues.size()==vecRand.size())
                            break;
        }
        int count=0;
        int local_marks=0;
        int local_tot_marks=0;
        User userObj;
        string name=userObj.getName(id);
        for(unsigned int i=0;i<vecQues.size();i++){
                int index=vecRand.at(i);
                *this=vecQues.at(index);
                clrscr();
                textcolor(GREEN);
                gotoxy(1,1);
                for(int j=1;j<=80;j++)
                        cout<<"*";
                gotoxy(32,2);
                textcolor(LIGHTRED);
                cout<<"QUIZ APPLICATION";
                textcolor(GREEN);
                gotoxy(1,3);
                for(int j=1;j<=80;j++)
                        cout<<"*";
                textcolor(WHITE);
                gotoxy(50,5);
                cout<<name;
                gotoxy(10,5);
                cout<<"TOTAL QUESTION "<<vecQues.size()<<endl;
                gotoxy(1,6);
                textcolor(YELLOW);
                for(int j=1;j<=80;j++)
                        cout<<"*";
                textcolor(GREEN);
                gotoxy(1,8);
                count++;
                cout<<count<<")";
                gotoxy(4,8);
                cout<<this->ques<<endl<<endl;
                textcolor(LIGHTGRAY);
                cout<<"a."<<this->op1<<endl<<endl;
                cout<<"b."<<this->op2<<endl<<endl;
                cout<<"c."<<this->op3<<endl<<endl;
                cout<<"d."<<this->op4<<endl<<endl;
                bool valid;
                char uans;
                do{
                        textcolor(YELLOW);
                        cout<<"Enter your option(a/b/c/d):  \b";
                        cin>>uans;
                        if(uans>='a' && uans<='d')
                                    valid=true;
                        else{
                                    valid=false;
                                    gotoxy(24,22);
                                    textcolor(LIGHTRED);
                                    cout<<"Invalid option entered. Try Again!";
                                    getch();
                                    gotoxy(24,22);
                                    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
                                    gotoxy(1,18);
                        }
                }while(valid==false);
                local_tot_marks+=this->tot_marks;
                if(uans==this->ans)
                        local_marks+=this->tot_marks;
        }
        clrscr();
        textcolor(GREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
                cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APPLICATION";
        textcolor(GREEN);
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
                cout<<"*";
        gotoxy(32,10);
        textcolor(LIGHTRED);
        cout<<"** TEST FINISHED **";
        gotoxy(22,12);
        cout<<"PRESS ANY KEY TO GO BACK TO MAIN MENU";
        getch();
        cin.ignore();
        StudentPerformance sp;
        sp.setMarksDetails(id,local_marks,local_tot_marks);
}
//***************************SAVING SATUDENT PERFORMANCE************************

void StudentPerformance::setMarksDetails(string id,int  marks,int tot_marks){
        strcpy(stuid, id.c_str());
        this->marks=marks;
        this->tot_marks=tot_marks;
        saveMarksDetails();
}
void StudentPerformance::saveMarksDetails(){
        ofstream fout("c:\\Quiz App\\Performance.bin",ios::app|ios::binary);
        if(!fout){
                gotoxy(1,26);
                textcolor(LIGHTRED);
                cout<<"Error in creating/opening file while saving student performance.";
                getch();
                return;
        }
        fout.write((char*)this,sizeof(*this));
        fout.close();
}
string User::getName(string id){
        ifstream fin("c:\\Quiz App\\Student.bin",ios::in|ios::binary);
        if(!fin){
                gotoxy(1,26);
                textcolor(LIGHTRED);
                cout<<"Error in file opening.";
                getch();
                return NULL;
        }
        while(1){
                fin.read((char*)this,sizeof(User));
                if(fin.eof()){
                        cout<<"No match of record find";
                        break;
                }
                int result=strcmp(this->getUserID().c_str(),id.c_str());
                if(result==0){
                        fin.close();
                        return this->username;
                }
        }
        fin.close();
        return NULL;
}
string User::getUserID(){
        string USERID;
        USERID=userid;
        return USERID;
}
//*****************************STUDENT VIEW PERFORMANCE *******************************

void Student::viewPerformance(){
        StudentPerformance stuobj;
        stuobj.viewDetails(userid);
}

void StudentPerformance::viewDetails(string id){
        fstream fin("c:\\Quiz App\\Performance.bin",ios::in|ios::binary);
        if(!fin){
                gotoxy(28,20);
                textcolor(LIGHTRED);
                cout<<"No Record Present Yet!!";
                getch();
                return;
        }
        clrscr();
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
                cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APPLICATION";
        textcolor(LIGHTGREEN);
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
                cout<<"*";
        gotoxy(25,5);
        textcolor(YELLOW);
        cout<<"***** VIEW REPORT CARD *****";
        textcolor(YELLOW);
        gotoxy(1,6);
        for(int i=1;i<=80;i++)
                cout<<"~";
         fin.seekg(0);
         string name="";
        int b=1;
        while(1){
                   fin.read((char*)this,sizeof(*this));
                   if(fin.eof()){
                                gotoxy(1,20);
                                textcolor(LIGHTRED);
                                if(name!=""){
                                            cout<<"NO MORE RECORDS AVAILABLE";
                                            getch();
                                }
                                else
                                            cout<<"YOUR RECORD IS NOT AVAILABLE";
                                fin.close();
                                break;
                   }
                   if(strcmp(stuid,id.c_str())==0){
                                gotoxy(1,14);
                                for(int i=1;i<=80;i++)
                                            cout<<"~";
                                User obj;
                                gotoxy(1,8);
                                cout<<"ID: "<<id;
                                name=obj.getName(id);
                                gotoxy(1,9);
                                cout<<"Name: "<<name;
                                textcolor(LIGHTGREEN);
                                gotoxy(1,11);
                                cout<<"SNO.\t\t\t MARKS OBTAINED \t\t\t TOTAL MARKS";
                                textcolor(YELLOW);
                                gotoxy(1,13);
                                cout<<b<<".";
                                gotoxy(31,13);
                                cout<<marks;
                                gotoxy(70,13);
                                cout<<tot_marks;
                                cout<<endl;
                                b++;
                                getch();
                   }
        }
        if (name==""){
                textcolor(LIGHTRED);
                gotoxy(1,22);
                cout<<"It because you may have not attemped quiz" ;
                getch();
                fin.close();
        }
}

//*************************Admin can also view student performance********************************************


void Admin::viewPerformance(){
        AdminViewPerformance  avObj;
        avObj.viewDetails();
}

void AdminViewPerformance::viewDetails(){
        fstream fin("c:\\Quiz App\\Performance.bin",ios::in|ios::binary);
        if(!fin){
                    gotoxy(28,20);
                    textcolor(LIGHTRED);
                    cout<<"No Record Present Yet!!";
                    getch();
                    return;
        }
        int b=1;
        fin.read((char*)this,sizeof(*this));
        if(fin.eof()){
                    gotoxy(28,20);
                    textcolor(LIGHTRED);
                    cout<<"File is empty";
                    fin.close();
                    getch();
                    return;
        }
        string name;
        User obj;
        fin.seekg(0);
        while(1){
                    clrscr();
                    textcolor(LIGHTGREEN);
                    gotoxy(1,1);
                    for(int i=1;i<=80;i++)
                                cout<<"*";
                    gotoxy(32,2);
                    textcolor(LIGHTRED);
                    cout<<"QUIZ APPLICATION";
                    textcolor(LIGHTGREEN);
                    gotoxy(1,3);
                    for(int i=1;i<=80;i++)
                                cout<<"*";
                    gotoxy(25,6);
                    textcolor(YELLOW);
                    cout<<"***** VIEW REPORT CARD *****";
                    textcolor(YELLOW);
                    gotoxy(1,7);
                    for(int i=1;i<=80;i++)
                                cout<<"~";
                    textcolor(YELLOW);
                    fin.read((char*)this,sizeof(*this));
                    if(fin.eof()){
                                textcolor(LIGHTRED);
                                gotoxy(32,15);
                                cout<<"No more records";
                                fin.close();
                                getch();
                                break;
                    }
                    gotoxy(1,16);
                    for(int i=1;i<=80;i++)
                                cout<<"~";
                    textcolor(LIGHTGREEN);
                    gotoxy(1,12);
                    cout<<"SNO.\t\t\t MARKS OBTAINED \t\t\t TOTAL MARKS";
                    gotoxy(1,9);
                    textcolor(YELLOW);
                    cout<<"ID: "<<stuid;
                    gotoxy(1,10);
                    name=obj.getName(stuid);
                    textcolor(YELLOW);
                    cout<<"Name: "<<name;
                    gotoxy(1,14);
                    cout<<b<<".";
                    gotoxy(31,14);
                    cout<<marks;
                    gotoxy(70,14);
                    cout<<tot_marks;
                    b++;
                    cout<<endl<<endl;
                    getch();
        }
}
