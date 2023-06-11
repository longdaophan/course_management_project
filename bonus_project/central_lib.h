#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <direct.h>
#include <errno.h>



using namespace std;
//using namespace std::filesystem;
struct Date
{
	int day;
	int month;
	int year;
};
struct student
{
	int no;
	string student_ID;
	string password;
	string first_name;
	string last_name;
	string gender;
	Date date_of_birth;
	string social_ID;
	student* prev;
	student* next;
};
struct list_student
{
	student* head;
	student* tail;
	int size;
};
struct staff
{
	int no;
	string staff_ID;
	string password;
	string first_name;
	string last_name;
	string gender;
	Date date_of_birth;
	string social_ID;
	staff* prev;
	staff* next;
};
struct list_staff
{
	staff* head;
	staff* tail;
	int size;
};
struct semester
{
	int no;
	Date start;
	Date end;
};
struct course
{
	string course_id;
	string course_name;
	string class_name;
	string teacher_name;
	int number_of_credit;
	int max_number=50;
	int number_of_enroller;
	string week_day;
	string session;
	course* prev;
	course* next;
};
struct scoreboard
{
	int no;
	string student_id;
	string student_full_name;
	float midterm_mark;
	float final_mark;
	float total_mark;
	string other_mark;
	scoreboard* prev;
	scoreboard* next;
};
struct list_scoreboard
{
	scoreboard* head;
	scoreboard* tail;
};
struct list_course
{
	course* head;
	course* tail;
	int size;
};
struct Class {
	string class_name;
	student* list_of_student;
	Class* prev;
	Class* next;
};
struct list_class
{
	Class* head;
	Class* tail;
	int size;
};
void gotoxy(short x, short y);
void drawbox(int col, int row, int width, int height);
void init_list_student(list_student &lstudent);
void init_list_staff(list_staff &lstaff);
void init_list_course(list_course &lcourse);
void init_list_class(list_class& lclass);
void init_list_scoreboard(list_scoreboard& lscoreboard);
bool get_file_student(list_student& lstudent, string path);
bool get_file_staff(list_staff& lstaff, string path);
bool get_file_course(list_course& lcourse, string path, string &length_of_course);
student* enter_infor_for_student(int &pos);
void add_student(list_student& lstudent, student* add);
void del_student(list_student& lstudent, student* del);
void add_staff(list_staff& lstaff, staff* add);
void del_staff(list_staff& lstaff, staff* del);
bool save_student_to_file(list_student lstudent, string path);
bool update_student_to_file(list_student lstudent, string path);
bool update_course_to_file(list_course lcourse, string path, string duration);
void update_course_for_each_student(string courseID, string path, course* crs);
void delete_course_for_each_student(string courseID, string path);
bool save_staff_to_file(list_staff lstaff, string path);
bool save_course_to_file(list_course lcourse, string path, string duration);
void add_course(list_course& lcourse, course* add);
void del_course(list_course& lcourse, course* del);
course* enter_infor_for_course(int &pos);
string convert_date_to_str(Date date);
Date convert_str_to_date(string str);
void courses_of_each_student(list_student lstudent, string path, list_course course, string duration);
void display_student(list_student lstudent);
void display_course(list_course lcourse);
bool check_day_of_birth(Date date);
void display_scoreboard_of_a_course(list_scoreboard lscoreboard);
bool get_file_scoreboard_of_a_course(string path, list_scoreboard &lscoreboard);
bool save_file_scoreboard(string path, list_scoreboard lscoreboard);
bool update_scoreboard_to_file(scoreboard* temp, string path,course* course);
void add_scoreboard(list_scoreboard& lscoreboard, scoreboard* add);
void enter_scoreboard(scoreboard* temp);
void scoreboard_of_each_student(list_scoreboard lscoreboard,course* course);
bool update_scoreboard_for_a_student(string path, scoreboard* score, string courseID);
void display_scoreboard_of_a_class(list_student lstudent);
