#include <iostream>
#include <string>
#include <cstring>
#include "conio2.h"
#include "quiz.h"
#include <dir.h>
#include <errno.h>

using namespace std;

int main()
{
    int result=mkdir("c:\\Quiz App");
    if(result!=0 && errno!=17){
        printf("Sorry! Application can not run");
        printf("\nError code:%d,",errno);
        perror("Reason");
        return 1;
    }
    int c,choice;
    string uchoice,type;
    textcolor(LIGHTGREEN);
    for(int i=1;i<=80;i++)
            cout<<"*";
    textcolor(LIGHTRED);
    gotoxy(32,2);
    cout<<"QUIZ APPLICATION";
    textcolor(LIGHTGREEN);
    gotoxy(1,3);
    for(int i=1;i<=80;i++)
            cout<<"*";
    gotoxy(20,10);
    textcolor(YELLOW);
    cout<<"WELCOME TO TECH TEST - QUIZ APPLICATION";
    gotoxy(20,14);
    textcolor(LIGHTCYAN);
    cout<<"TEST YOUR SKILLS! IMPROVE YOUR KNOWLWDGE !";
    textbackground(LIGHTCYAN);
    gotoxy(1,20);
    for(int i=1;i<=80;i++)
                    cout<<" ";
    textbackground(BLACK);
    gotoxy(1,22);
    textcolor(WHITE);
    cout<<"Press any key to continue";
    getch();
    Admin::create_admin("admin","abc","Pankaj Roy");

//*****************************landing screen design************************************

    do{
            clrscr();
            textcolor(LIGHTGREEN);
            for(int i=1;i<=80;i++)
                    cout<<"*";
            textcolor(LIGHTRED);
            gotoxy(32,2);
            cout<<"QUIZ APPLICATION";
            textcolor(LIGHTGREEN);
            gotoxy(1,3);
            for(int i=1;i<=80;i++)
                    cout<<"*";
            gotoxy(57,4);
            textcolor(WHITE);
            cout<<"Press 0 to Exit/Go Back";
            gotoxy(1,8);
            textcolor(YELLOW);
            for(int i=1;i<=80;i++)
                    cout<<"*";
            gotoxy(1,17);
            for(int i=1;i<=80;i++)
                    cout<<"*";
            gotoxy(32,10);

//**************************user options**********************************
            cout<<"1. ADMIN";
            gotoxy(32,12);
            cout<<"2. STUDENT";
            textcolor(LIGHTCYAN);
            gotoxy(32,14);
            cout<<"Select your role:";
            textcolor(WHITE);
            getline(cin,type);
            if(type=="0")
                    break;             // <--------if exit from first main screen

                                                          //************Admin screen***************

                                                    //***Admin login verfication****
            if(type=="1"){
                    Admin adminObj;
                    do{
                            c=adminObj.input();
                            if(c==0){
                                    gotoxy(30,14);
                                    textcolor(LIGHTRED);
                                    cout<<"Login Cancelled";
                                    gotoxy(1,20);
                                    cout<<"Press any key to continue";
                                    getch();
                                    break;
                            }
                           c= adminObj.checkUserExists("admin");
                           if(c==1){
                                    gotoxy(28,18);
                                    textcolor(LIGHTGREEN);
                                    cout<<"Login Accepted!";
                                    gotoxy(28,20);
                                    cout<<"Welcome "<<adminObj.getName();
                                    gotoxy(28,22);
                                    textcolor(LIGHTCYAN);
                                    cout<<"Press any key to continue";
                                    getch();
                                    while(1){
                                            clrscr();
                                            textcolor(LIGHTGREEN);
                                            for(int i=1;i<=80;i++){
                                                    cout<<"*";
                                            }
                                            gotoxy(1,3);
                                            for(int i=1;i<=80;i++){
                                                    cout<<"*";
                                            }

                                    //***********Admin functionality**************

                                            gotoxy(32,2);
                                            textcolor(LIGHTRED);
                                            cout<<"QUIZ APPLICATION";
                                            textcolor(LIGHTGREEN);
                                            gotoxy(35,6);
                                            cout<<"ADMIN MENU"<<endl;
                                            textcolor(YELLOW);
                                            for(int i=1;i<=80;i++)
                                                    cout<<"*";
                                            gotoxy(32,8);
                                            cout<<"1. Add Question";
                                            gotoxy(32,9);
                                            cout<<"2. Add Student";
                                            gotoxy(32,10);
                                            cout<<"3. Show Questions";
                                            gotoxy(32,11);
                                            cout<<"4. Show Students";
                                            gotoxy(32,12);
                                            cout<<"5. Remove Question";
                                            gotoxy(32,13);
                                            cout<<"6. Remove Student";
                                            gotoxy(32,14);
                                            cout<<"7. View Student's Performance";
                                            gotoxy(32,15) ;
                                            cout<<"8. Exit";
                                            textbackground(BROWN);
                                            gotoxy(1,20);
                                            for(int i=1;i<=80;i++)
                                                    cout<<" ";
                                            textbackground(BLACK);
                                            gotoxy(32,17);
                                            cout<<"Enter Choice:";
                                            textcolor(WHITE);
                                            getline(cin,uchoice);
                                            if(uchoice.length()>1)
                                                    choice=1;
                                            else
                                                  choice=int(uchoice[0]);
                                            switch(choice){
                                                        case 49:
                                                                    clrscr();
                                                                    adminObj.addQuestion();
                                                                    break;
                                                        case 50:
                                                                    adminObj.addStudent();
                                                                    break;
                                                        case 51:
                                                                    clrscr();
                                                                    adminObj.viewQuestion();
                                                                    break;
                                                        case 52:
                                                                    clrscr();
                                                                    adminObj.viewStudent();
                                                                    break;
                                                        case 53:
                                                                    clrscr();
                                                                    adminObj.removeQuestion();
                                                                    break;
                                                        case 54:
                                                                    clrscr();
                                                                    adminObj.removeStudent();
                                                                    break;
                                                        case 55:
                                                                    clrscr();//
                                                                    adminObj.viewPerformance();//
                                                                    break;
                                                        case 56://
                                                                    break;
                                                        default:
                                                                    textcolor(LIGHTRED);
                                                                    gotoxy(32,22);
                                                                    cout<<"Wrong choice. Try Again !";
                                                                    getch();
                                                                    break;
                                            }
                                            if(choice==56)
                                                    break;
                                    }
                           }
                        }while(c==0);
            }

                            //***********Students  screen****************

            else if(type=="2"){
                    Student studObj;
                    do{
                            c=studObj.input();
                            if(c==0){
                                    gotoxy(30,14);
                                    textcolor(LIGHTRED);
                                    cout<<"Login Cancelled";
                                    gotoxy(1,20);
                                    cout<<"Press any key to continue";
                                    getch();
                                    break;
                            }
                           c= studObj.checkUserExists("student");
                           if(c==1){
                                    gotoxy(28,18);
                                    textcolor(LIGHTGREEN);
                                    cout<<"Login Accepted!";
                                    gotoxy(28,20);
                                    cout<<"Welcome "<<studObj.getName();
                                    gotoxy(28,22);
                                    textcolor(LIGHTCYAN);
                                    cout<<"Press any key to continue";
                                    getch();
                                    while(1){
                                            clrscr();
                                            textcolor(LIGHTGREEN);
                                            for(int i=1;i<=80;i++){
                                                    cout<<"*";
                                            }
                                            gotoxy(1,3);
                                            for(int i=1;i<=80;i++){
                                                    cout<<"*";
                                            }

                                    //***********Student functionality**************

                                            gotoxy(32,2);
                                            textcolor(LIGHTRED);
                                            cout<<"QUIZ APPLICATION";
                                            textcolor(LIGHTGREEN);
                                            gotoxy(34,6);
                                            cout<<"STUDENT MENU"<<endl;
                                            textcolor(YELLOW);
                                            for(int i=1;i<=80;i++)
                                                    cout<<"*";
                                            gotoxy(32,9);
                                            cout<<"1. Start Quiz";
                                            gotoxy(32,10);
                                            cout<<"2. View Performance";
                                            gotoxy(32,11);
                                            cout<<"3. Exit";
                                            textbackground(BROWN);
                                            gotoxy(1,20);
                                            for(int i=1;i<=80;i++)
                                                    cout<<" ";
                                            textbackground(BLACK);
                                            gotoxy(32,13);
                                            cout<<"Enter Choice:";
                                            textcolor(WHITE);
                                            getline(cin,uchoice);

                                            if(uchoice.length()>1)
                                                    choice=1;
                                            else
                                                    choice=int(uchoice[0]);

                                            switch(choice){
                                                        case 49:
                                                                    clrscr();
                                                                    studObj.quiz();
                                                                    break;
                                                        case 50:
                                                                    clrscr();
                                                                    studObj.viewPerformance();
                                                                    break;
                                                        case 51:
                                                                    clrscr();
                                                                    break;
                                                        default:
                                                                    textcolor(LIGHTRED);
                                                                    gotoxy(32,22);
                                                                    cout<<"Wrong choice. Try Again !";
                                                                    getch();
                                                                    break;
                                            }
                                            if(choice==51)
                                                    break;
                                    }
                           }
                        }while(c==0);
            }
            else{
                    gotoxy(30,14);
                    cout<<"\t\t\t\t\t\t\t";
                    gotoxy(30,14);
                    textcolor(LIGHTRED);
                    cout<<"Invalid User Type";
                    getch();
            }
        }while(1);
        textcolor(LIGHTRED);
        cout<<endl<<endl<<endl;
        return 0;
}
