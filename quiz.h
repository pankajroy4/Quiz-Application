#ifndef QUIZ_H_INCLUDED
#define QUIZ_H_INCLUDED
#include <cstring>
#include <string>
using namespace std;
class User{
protected:
    char userid[20];
    char pwd[20];
    char username[50];
public:
    void setUserDetails(string,string,string);
    string getName(string);  //<-- for displaying name of student when the appear for test
    string getName();
    string getUserID();
    int checkUserExists(string);
    void show();
    int input();
};

class Student:public User{
public:
    void add();
    void Remove();      /*r must be capital*/
    void showStudentDetails();
    void viewPerformance();
    void quiz();
};

class Admin:public User{
public:
    static void create_admin(string,string,string);
    void addStudent();
    void removeStudent();
    void viewStudent();
    void addQuestion();
     void viewPerformance();
    void removeQuestion();
    void viewQuestion();
};

class AdminViewPerformance{
    char stuid[20];
    int marks,tot_marks;
public:
    void viewDetails();
    void removePerformance(string);
};

class Question{
    int quesid;
    int tot_marks;
    char ques[1000],op1[100],op2[100],op3[100],op4[100],ans;
public:
    void add();
    void Remove();
    void setQuestionDetails(int,string,string,string,string,string,char);
    void show();
    void viewQuestion();
    void startQuiz(string);
    int ques_count();
};

class StudentPerformance{
    char stuid[20];
    int marks,tot_marks;
public:
    void setMarksDetails(string,int,int);
    void saveMarksDetails();
    void viewDetails(string);
    void show();
};

#endif // QUIZ_H_INCLUDED
