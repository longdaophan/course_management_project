#include "login.h"
void login_interface()
{
	drawbox(40, 5, 40, 20);
	gotoxy(58, 6);
	cout << "LOGIN";
	gotoxy(45, 8);
	cout << "Id:";
	gotoxy(45, 9);
	cout << "Password:";
}
void login_system()
{
	system("cls");
	login_interface();

}