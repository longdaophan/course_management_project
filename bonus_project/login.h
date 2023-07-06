#pragma once
#include "central_lib.h"
void login_system();// ham nhap id va mat khau
string login_interface();// giao dien de nhap id mat khau
int control(int& pos,int sl ,int max);// ham dieu khien viec chon lua bang mui ten trong ban phim
void student_menu(student* student, list_student lstudent);
void staff_menu(staff* staff, list_staff lstaff);
string check_password(string id, string password);
void change_password(student* student, list_student lstudent);// thay doi mat khau cho sinh vien
void change_password(staff* staff, list_staff lstaff);// thay doi mat khau cho nhan vien
void profile(student* student, list_student lstudent);// profile hoc sinh
void profile(staff* staff, list_staff lstaff);// profile nhan vien
void manage_academic_years(staff* staff, list_staff lstaff);
void create_new_academic_year();
void add_classes();
void add_students_manually(list_student &lstudent_for_new_class);
void add_students_by_importing_file(list_student& lstudent_for_new_class);
void add_a_course(list_course& lcourse, string path, string duration);
void add_courses();
void modify_classes();
void delete_student(list_student &lstudent);
void view_list_of_classes();
bool view_list_of_courses(string path);
void view_list_of_courses_in_course_management_menu();
void view_list_of_student_in_a_course();
void course_management();
void create_new_semester();
void modify_course();
void update_course_information();
void add_a_student_to_the_course();
void remove_a_student_from_the_course();
void delete_a_course();
void manage_scoreboard_of_a_course();
bool export_scoreboard(string path);
void update_scoreboard(string path, list_scoreboard lscoreboard, string courseID);
void import_scoreboard(list_scoreboard &lscoreboard, string path, course* course);
void view_scoreboard_of_a_class();
void academic_results(student* temp);
void list_of_course_in_student_menu(student* temp);