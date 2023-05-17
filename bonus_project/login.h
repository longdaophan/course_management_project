#pragma once
#include "central_lib.h"
void login_system();
string login_interface();
int control(int& pos,int sl ,int max);
void student_menu(student* student, list_student lstudent);
void staff_menu(staff* staff, list_staff lstaff);
string check_password(string id, string password);
void change_password(student* student, list_student lstudent);
void change_password(staff* staff, list_staff lstaff);
void profile(student* student, list_student lstudent);
void profile(staff* staff, list_staff lstaff);
void manage_academic_years(staff* staff, list_staff lstaff/*, list_student lstudent, list_class lclass, list_course lcourse*/ );
void create_new_academic_year();
void view_academic_years();
void add_classes();
void add_students_manually(list_student &lstudent_for_new_class);
void add_students_by_importing_file(list_student& lstudent_for_new_class);