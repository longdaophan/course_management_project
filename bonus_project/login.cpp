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
void login_system()
{
	while (true)
	{
		system("cls");
		string temp = login_interface();
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


}