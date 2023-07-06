#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>// thu vien de dung gotoxy
#include <string>
#include <stdio.h>
#include <conio.h>
#include <direct.h>
#include <errno.h>// thu vien de thong bao loi



using namespace std;
//using namespace std::filesystem;
struct Date// Ngay thang nam
{
	int day;
	int month;
	int year;
};
struct student// Hoc sinh
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
struct staff// Nhan vien
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
struct semester// Hoc ky
{
	int no;
	Date start;
	Date end;
};
struct course// Khoa hoc
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
struct scoreboard// Bang diem
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
void gotoxy(short x, short y);// Ham nay copy hoan toan tren mang
void drawbox(int col, int row, int width, int height);// Ham ve khung
void init_list_student(list_student &lstudent);// khoi tao danh sach hoc sinh
void init_list_staff(list_staff &lstaff);// khoi tao danh sach nhan vien
void init_list_course(list_course &lcourse);// khoi tao danh sach khoa hoc
void init_list_class(list_class& lclass);// khoi tao danh sach lop hoc
void init_list_scoreboard(list_scoreboard& lscoreboard);// khoi tao danh sach bang diem
bool get_file_student(list_student& lstudent, string path);// Lay file danh sach hoc sinh tu file csv va luu vao thanh mot danh sach lien ket doi, co head la lstudent, truyen duong dan
bool get_file_staff(list_staff& lstaff, string path);// Lay file nhan vien
bool get_file_course(list_course& lcourse, string path, string &length_of_course);// Lay file khoa hoc
student* enter_infor_for_student(int &pos);// Ham nhap thong tin cho mot hoc sinh vao mot Node, pos dung de dieu khien vi tri nhap thong tin thanh tung dong
void add_student(list_student& lstudent, student* add);// Them mot hoc sinh vao danh sach
void del_student(list_student& lstudent, student* del);// Xoa mot hoc sinh ra khoi danh sach
void add_staff(list_staff& lstaff, staff* add);// Them mot nhan vien vao danh sach
void del_staff(list_staff& lstaff, staff* del);// Xoa mot nhan vien ra khoi danh sach
bool save_student_to_file(list_student lstudent, string path);// Tao ra file csv va luu danh sach vao file, voi duong dan duoc truyen vao
bool update_student_to_file(list_student lstudent, string path);// Cap nhat danh sach hoc sinh trong file csv, xoa bo nhung hoc sinh bi trung id
bool update_course_to_file(list_course lcourse, string path, string duration);// Cap nhat danh sach khoa hoc trong file csv, xoa bo nhung khoa hoc bi trung id
void update_course_for_each_student(string courseID, string path, course* crs);// Cap nhat khoa hoc vao file hoc sinh, moi hoc sinh co 1 file csv ten la id cua ban than, chua khoa hoc da dang ky
void delete_course_for_each_student(string courseID, string path);// Xoa khoa hoc trong file 
bool save_staff_to_file(list_staff lstaff, string path);// Tao ra file csv va luu danh sach vao file, voi duong dan duoc truyen vao
bool save_course_to_file(list_course lcourse, string path, string duration);// Tao ra file csv va luu danh sach vao file, voi duong dan duoc truyen vao
void add_course(list_course& lcourse, course* add);// them khoa hoc
void del_course(list_course& lcourse, course* del);// xoa khoa hoc
course* enter_infor_for_course(int &pos);// nhap thong tin cho mot khoa hoc
string convert_date_to_str(Date date);// chuyen doi struct Date sang string
Date convert_str_to_date(string str);// chuyen doi string sang struct Date
void courses_of_each_student(list_student lstudent, string path, list_course course, string duration);// tao file csv co chua cac khoa hoc da dang ky, lay ten la id cua sinh vien
void display_student(list_student lstudent);// trinh bay danh sach hoc sinh ra man hinh
void display_course(list_course lcourse);// trinh bay danh sach khoa hoc ra man hinh
bool check_day_of_birth(Date date);// kiem tra ngay thang nam nhap vao co hop le
void display_scoreboard_of_a_course(list_scoreboard lscoreboard);// trinh bay bang diem ra man hinh
bool get_file_scoreboard_of_a_course(string path, list_scoreboard &lscoreboard);// lay danh sach ban diem
bool save_file_scoreboard(string path, list_scoreboard lscoreboard);// luu bang diem vao file
bool update_scoreboard_to_file(scoreboard* temp, string path,course* course);// cap nhat bang diem
void add_scoreboard(list_scoreboard& lscoreboard, scoreboard* add);// them diem vao bang diem
void enter_scoreboard(scoreboard* temp);// nhap diem 
void scoreboard_of_each_student(list_scoreboard lscoreboard,course* course);// tao file csv co chua tat ca diem cho moi hoc sinh
bool update_scoreboard_for_a_student(string path, scoreboard* score, string courseID);// cap nhat bang diem
void display_scoreboard_of_a_class(list_student lstudent);// trinh bay bang diem cho mot lop
