#include "login.h"
int main()
{
	/*list_course lcourse;
	init_list_course(lcourse);
	string duration;
	string path = "../academic_years/2022/Semester 1";
	get_file_course(lcourse, path + "/courses.csv", duration);
	cout << duration;
	display_course(lcourse);*/
	//save_course_to_file(lcourse, path + "/courses.csv", duration);
	login_system();
	/*list_student lstudent;
	init_list_student(lstudent);
	get_file_student(lstudent, "student.csv");
	display_student(lstudent);
	save_student_to_file(lstudent, "student.csv");*/
	gotoxy(0, 27);
	system("pause");
	return 0;
}