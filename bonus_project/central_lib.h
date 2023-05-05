#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <conio.h>

using namespace std;
struct Date
{
	int day;
	int month;
	int year;
	string week_day;
};
struct student
{
	int no;
	string student_ID;
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
	int max_number = 50;
	string week_day;
	string session[4];
	course* prev;
	course* next;
};
struct list_course
{
	course* head;
	course* tail;
	int size;
};
struct Class {
	string class_name;
	Class* prev;
	Class* next;
};
struct list_class
{
	Class* head;
	Class* tail;
	int size;
};
void gotoxy(int x, int y);
void drawbox(int col, int row, int width, int height);
