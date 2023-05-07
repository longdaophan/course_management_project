#pragma once
#include "central_lib.h"
void login_system();
string login_interface();
int control(int& pos,int sl ,int max);
void student_menu(student* student);
void staff_menu();
string check_password(string id, string password);