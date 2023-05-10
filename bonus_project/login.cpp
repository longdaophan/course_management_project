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
void student_menu(student* student, list_student lstudent)
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
		cout << "Academic Results";
		gotoxy(40, 15);
		cout << "Course Registration";
		gotoxy(40, 17);
		cout << "Change Password";
		gotoxy(38, 22);
		cout << "LOG OUT";
		x= control(pos,sl, 4);
		sl++;
	} while (x!=0);
	switch (pos)
	{
	case 11:
		profile(student, lstudent);
		break;
	case 17:
		change_password(student, lstudent);
		break;
	case 22:
		login_system();
		break;
	}
}
void change_password(student* student, list_student lstudent)
{
	bool ks = true;
	int key;
	while (ks)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		gotoxy(45, 6);
		cout << "Welcome: " << student->first_name << " " << student->last_name;
		drawbox(33, 5, 53, 20);
		gotoxy(55, 7);
		cout << "CHANGE PASSWORD";
		gotoxy(45, 11);
		cout << "ID:";
		gotoxy(45, 13);
		cout << "Password:";
		gotoxy(45, 15);
		cout << "New password:";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			student_menu(student, lstudent);
			break;
		case 72:
		case 80:
			break;
		}
		string id;
		string password;
		gotoxy(48, 11);
		getline(cin, id);
		gotoxy(54, 13);
		getline(cin, password);
		if (student->student_ID == id && student->password == password)
			ks = false;
		else
		{
			system("cls");
			gotoxy(40, 13);
			cout << "Ban nhap id hoac mat khau sai, vui long nhap lai.";
			Sleep(2000);
			gotoxy(38, 22);
			key = _getch();
			switch (key)
			{
			case 13:
				student_menu(student, lstudent);
				break;
			case 72:
			case 80:
				break;
			}
		}
	}
	string new_password;
	gotoxy(58, 15);
	getline(cin, new_password);
	student->password = new_password;
	save_student_to_file(lstudent);
	system("cls");
	gotoxy(40, 13);
	cout << "Da luu mat khau, vui long dang nhap lai.";
	Sleep(2000);
	login_system();
}
void change_password(staff* staff, list_staff lstaff)
{
	bool ks = true;
	int key;
	while (ks)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		gotoxy(45, 6);
		cout << "Welcome: " << staff->first_name << " " << staff->last_name;
		drawbox(33, 5, 53, 20);
		gotoxy(55, 7);
		cout << "CHANGE PASSWORD";
		gotoxy(45, 11);
		cout << "ID:";
		gotoxy(45, 13);
		cout << "Password:";
		gotoxy(45, 15);
		cout << "New password:";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			staff_menu(staff, lstaff);
			break;
		case 72:
		case 80:
			break;
		}
		string id;
		string password;
		gotoxy(48, 11);
		getline(cin, id);
		gotoxy(54, 13);
		getline(cin, password);
		if (staff->staff_ID == id && staff->password == password)
			ks = false;
		else
		{
			system("cls");
			gotoxy(40, 13);
			cout << "Ban nhap id hoac mat khau sai, vui long nhap lai.";
			Sleep(2000);
			gotoxy(38, 22);
			key = _getch();
			switch (key)
			{
			case 13:
				staff_menu(staff, lstaff);
				break;
			case 72:
			case 80:
				break;
			}
		}
	}
	string new_password;
	gotoxy(58, 15);
	getline(cin, new_password);
	staff->password = new_password;
	save_staff_to_file(lstaff);
	system("cls");
	gotoxy(40, 13);
	cout << "Da luu mat khau, vui long dang nhap lai.";
	Sleep(2000);
	login_system();
}
void profile(student* student, list_student lstudent)
{
	system("cls");
	gotoxy(55, 4);
	cout << "HCMUS";
	gotoxy(45, 6);
	cout << "Welcome: " << student->first_name << " " << student->last_name;
	drawbox(33, 5, 53, 20);
	gotoxy(55, 8);
	cout << "PROFILE";
	gotoxy(42, 11);
	cout << "Ho va ten: " << student->first_name << " " << student->last_name;
	gotoxy(42, 13);
	cout << "MSSV(ID): " << student->student_ID;
	gotoxy(42, 15);
	cout << "Ngay sinh: " << convert_date_to_str(student->date_of_birth);
	gotoxy(42, 17);
	cout << "Social ID: " << student->social_ID;
	gotoxy(38, 22);
	cout << "BACK";
	int key = _getch();
	switch (key)
	{
	case 13:
		student_menu(student, lstudent);
		break;
	}
}
void profile(staff* staff, list_staff lstaff)
{
	system("cls");
	gotoxy(55, 4);
	cout << "HCMUS";
	gotoxy(45, 6);
	cout << "Welcome: " << staff->first_name << " " << staff->last_name;
	drawbox(33, 5, 53, 20);
	gotoxy(55, 8);
	cout << "PROFILE";
	gotoxy(42, 11);
	cout << "Ho va ten: " << staff->first_name << " " << staff->last_name;
	gotoxy(42, 13);
	cout << "MSSV(ID): " << staff->staff_ID;
	gotoxy(42, 15);
	cout << "Ngay sinh: " << convert_date_to_str(staff->date_of_birth);
	gotoxy(42, 17);
	cout << "Social ID: " << staff->social_ID;
	gotoxy(38, 22);
	cout << "BACK";
	int key = _getch();
	switch (key)
	{
	case 13:
		staff_menu(staff, lstaff);
		break;
	}
}
void manage_academic_years(staff* staff, list_staff lstaff, list_student lstudent, list_class lclass, list_course lcourse)
{
	int pos = 11;
	int x;
	int sl = 0;
	do
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(55, 7);
		cout << "MANAGE ACADEMIC YEARS";
		gotoxy(45, 11);
		cout << "View academic years";
		gotoxy(45, 13);
		cout << "Create new academic year";
		gotoxy(38, 22);
		cout << "BACK";
		x = control(pos, sl, 2);
		sl++;
	} while (x != 0);
	switch (pos)
	{
	case 11:
		break;
	case 13:
		break;
	case 22:
		staff_menu(staff, lstaff);
		break;
	}
}
void create_new_academic_year()
{
	string year, class_name, course_name, path;
	path = "../academic_years/" + year + "/Classes/" + class_name;
	_mkdir(path.c_str());
	system("cls");
	gotoxy(55, 4);
	cout << "HCMUS";
	drawbox(33, 5, 53, 20);
	gotoxy(40, 11);
	cout << "Nhap nam hoc: ";
	gotoxy(40, 13);
	cout << "Nhap ten lop: ";
	gotoxy(38, 22);
	cout << "BACK";
	gotoxy(55, 11);
	getline(cin, year);
	/*gotoxy(55, 11);
	getline(cin, class_name);*/
	path = "../academic_years/" + year;
	_mkdir(path.c_str());


}
void staff_menu(staff* staff, list_staff lstaff)
{
	int pos = 9;
	int x;
	int sl = 0;
	do
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		gotoxy(45, 6);
		cout << "Welcome: " << staff->first_name << " " << staff->last_name;
		drawbox(33, 5, 53, 20);
		gotoxy(40, 9);
		cout << "PROFILE";
		gotoxy(40, 11);
		cout << "Manage academic years";
		gotoxy(40, 13);
		cout << "Course Management";
		gotoxy(40, 15);
		cout << "Student Management";
		gotoxy(40, 17);
		cout << "Change Password";
		gotoxy(38, 22);
		cout << "LOG OUT";
		x = control(pos, sl, 5);
		sl++;
	} while (x != 0);
	switch (pos)
	{
	case 9:
		profile(staff, lstaff);
		break;
	case 17:
		change_password(staff, lstaff);
		break;
	case 22:
		login_system();
		break;
	}
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
	string temp;
	while (true)
	{
		temp = login_interface();
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
				student_menu(std, lstudent);
				return;
			}
			std = std->next;
		}
	if(true)
		while (sta != NULL)
		{
			if (sta->staff_ID == temp)
			{
				staff_menu(sta, lstaff);
				return;
			}
			sta = sta->next;
		}
}