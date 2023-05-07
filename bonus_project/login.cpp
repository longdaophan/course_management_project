#include "login.h"
string check_password(string id, string password)
{
	list_student lstudent;
	list_staff lstaff;
	init_list_staff(lstaff);
	init_list_student(lstudent);
	get_file_staff(lstaff);
	get_file_student(lstudent);
	student* std = lstudent.head;
	staff* sta = lstaff.head;
	while (std != NULL)
	{
		if (std->student_ID == id)
		{
			if (std->password == password)
				return std->student_ID;
		}
		std = std->next;
	}
	while (sta != NULL)
	{
		if (sta->staff_ID == id)
		{
			if (sta->password == password)
				return sta->staff_ID;
		}
		sta = sta->next;
	}
	return "0";
}
string login_interface()
{
	string id ;
	string password ;
		system("cls");
		drawbox(40, 5, 40, 20);
		gotoxy(58, 6);
		cout << "LOGIN";
		gotoxy(45, 8);
		cout << "Id:";
		gotoxy(45, 9);
		cout << "Password:";
		gotoxy(48, 8);
		getline(cin, id);
		gotoxy(54, 9);
		getline(cin, password);
		return check_password(id, password);
}
int control(int& pos, int sl, int max)
{
	max--;
	static int x ;
	if (sl == 0)
		x = pos;
		gotoxy(35, pos);
		cout << "->";
		int key = _getch();
		switch (key)
		{
		case 13:
			return 0;
			break;
		case 72:
			pos -= 2;
			if (pos < x)
				pos = x + max * 2;
			if (pos > (x + max * 2))
				pos = x;
			break;
		case 80:
			pos += 2;
			if (pos > (x + max * 2))
				pos = x;
			break;
		case 75:
			pos = 22;
			break;
		}
		return 1;
}
void student_menu(student* student)
{
	int pos = 11;
	int x;
	int sl = 0;
	do
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		gotoxy(45, 6);
		cout << "Welcome: " << student->first_name << " " << student->last_name;
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "PROFILE";
		gotoxy(40, 13);
		cout << "Student Management";
		gotoxy(40, 15);
		cout << "Course Management";
		gotoxy(40, 17);
		cout << "Change Password";
		gotoxy(38, 22);
		cout << "LOG OUT";
		x= control(pos,sl, 4);
		sl++;
	} while (x!=0);
}
void login_system()
{
	list_student lstudent;
	list_staff lstaff;
	init_list_staff(lstaff);
	init_list_student(lstudent);
	get_file_staff(lstaff);
	get_file_student(lstudent);
	student* std = lstudent.head;
	staff* sta = lstaff.head;
	string temp = login_interface();
	while (true)
	{
		system("cls");
		if (temp != "0")
		{
			system("cls");
			gotoxy(50, 13);
			cout << "Login success!";
			Sleep(2000);
			break;
		}
		else
		{
			system("cls");
			gotoxy(50, 13);
			cout << "Login failed!";
			Sleep(2000);
		}
	}
	if(true)
		while (std != NULL)
		{
			if (std->student_ID == temp)
			{
				student_menu(std);
				return;
			}
			std = std->next;
		}
	/*else
		while (sta != NULL)
		{
			if (sta->staff_ID == temp)
			{
				staff_menu();
				return;
			}
			sta = sta->next;
		}*/
}