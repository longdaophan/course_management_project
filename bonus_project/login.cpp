#include "login.h"
string check_password(string id, string password)
{
	list_student lstudent;
	list_staff lstaff;
	init_list_staff(lstaff);
	init_list_student(lstudent);
	get_file_staff(lstaff,"staff.csv");
	get_file_student(lstudent,"student.csv");
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
	int key;
		system("cls");
		drawbox(40, 5, 40, 20);
		gotoxy(58, 6);
		cout << "LOGIN";
		gotoxy(45, 8);
		cout << "Id:";
		gotoxy(45, 9);
		cout << "Password:";
		gotoxy(42, 22);
		cout << "EXIT";
		key = _getch();
		switch (key)
		{
		case 13:
			gotoxy(0, 27);
			system("pause");
			exit(0);
		case 72:
		case 80:
			break;
		}
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
	do {
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
			cout << "List of course in current semester";
			gotoxy(40, 15);
			cout << "Academic results";
			gotoxy(40, 17);
			cout << "Change Password";
			gotoxy(38, 22);
			cout << "LOG OUT";
			x = control(pos, sl, 4);
			sl++;
		} while (x != 0);
		switch (pos)
		{
		case 11:
			profile(student, lstudent);
			break;
		case 13:
			list_of_course_in_student_menu(student);
			break;
		case 15:
			academic_results(student);
			system("pause");
			break;
		case 17:
			change_password(student, lstudent);
			break;
		case 22:
			login_system();
			break;
		}
	} while (pos != 22);
}
void academic_results(student* temp)
{
	system("cls");
	list_course lcourse;
	init_list_course(lcourse);
	list_scoreboard lscoreboard;
	init_list_scoreboard(lscoreboard);
	ifstream file("../academic_years/courseforstudent/" + temp->student_ID + "_scoreboard.csv");
	if (file.fail())
		return;
	else
	{
		while (!file.eof())
		{
			scoreboard* sco = new scoreboard;
			course* cour = new course;
			string str;
			getline(file, cour->course_id, ',');
			getline(file, cour->course_name, ',');
			getline(file, str, ',');
			if (str == "") break;
			sco->midterm_mark = stof(str);
			getline(file, str, ',');
			sco->final_mark = stof(str);
			getline(file, str, ',');
			sco->total_mark = stof(str);
			getline(file, sco->other_mark, '\n');
			sco->next = sco->prev = NULL;
			cour->next = cour->prev = NULL;
			add_scoreboard(lscoreboard, sco);
			add_course(lcourse, cour);
		}
		file.close();
	}
	int pos = 8;
	drawbox(15, 5, 80, 2);
	gotoxy(16, 6);
	cout << "  Course ID |";
	gotoxy(30, 6);
	cout << "     Cousre name    |";
	gotoxy(52, 6);
	cout << "Midterm |";
	gotoxy(62, 6);
	cout << "Final |";
	gotoxy(70, 6);
	cout << "Total |";
	gotoxy(78, 6);
	cout << "Other ";
	course* temp1 = lcourse.head;
	scoreboard* tam = lscoreboard.head;
	while (tam != NULL && temp1 != NULL)
	{
		gotoxy(17, pos);
		cout << temp1->course_id;
		gotoxy(31, pos);
		cout << temp1->course_name;
		gotoxy(53, pos);
		cout << tam->midterm_mark;
		gotoxy(63, pos);
		cout << tam->final_mark;
		gotoxy(71, pos);
		cout << tam->total_mark;
		gotoxy(79, pos++);
		cout << tam->other_mark;
		temp1 = temp1->next;
		tam = tam->next;
	}
	gotoxy(0, pos + 2);
}
void list_of_course_in_student_menu(student* temp)
{
	list_course lcourse;
	init_list_course(lcourse);
	string duration;
	string path = "../academic_years/courseforstudent/" + temp->student_ID + ".csv";
	if (get_file_course(lcourse, path, duration))
	{
		system("cls");
		gotoxy(2, 3);
		cout << "Length of course: " << duration;
		display_course(lcourse);
		system("pause");
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
	save_student_to_file(lstudent, "student.csv");
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
	save_staff_to_file(lstaff,"staff.csv");
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
	cout << "ID: " << staff->staff_ID;
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
void manage_academic_years(staff* staff, list_staff lstaff/*, list_student lstudent, list_class lclass, list_course lcourse*/)
{
	int pos = 11;
	int x;
	int sl = 0;
	do
	{
		do
		{
			system("cls");
			gotoxy(55, 4);
			cout << "HCMUS";
			drawbox(33, 5, 53, 20);
			gotoxy(50, 7);
			cout << "MANAGE ACADEMIC YEARS";
			gotoxy(45, 11);
			cout << "Create new academic year";
			gotoxy(45, 13);
			cout << "Add classes";
			gotoxy(45, 15);
			cout << "Modify classes";
			gotoxy(45, 17);
			cout << "View list of classes";
			/*gotoxy(45, 19);
			cout << "Modify semesters";*/
			gotoxy(38, 22);
			cout << "BACK";
			x = control(pos, sl, 4);
			sl++;
		} while (x != 0);
		switch (pos)
		{
		case 11:
			create_new_academic_year();
			break;
		case 13:
			add_classes();
			break;
		case 15: 
			modify_classes();
			break;
		case 17:
			view_list_of_classes();
			break;
		case 22:
			staff_menu(staff, lstaff);
			break;
		}
	} while (pos != 22);
}
void create_new_academic_year()
{
	int key;
	while (true)
	{
		string year, path;
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap nam hoc muon tao: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(62, 11);
		getline(cin, year);
		path = "../academic_years/" + year;
		int kt = _mkdir(path.c_str());
		if (kt == 0)
		{
			system("cls");
			gotoxy(40, 13);
			cout << "Nam hoc moi da duoc tao.";
			Sleep(2000);
			break;
		}
		else
		{
			system("cls");
			gotoxy(50, 13);
			cout << strerror(errno);
			Sleep(2000);
			key = _getch();
			switch (key)
			{
			case 13:
				return;
				break;
			case 72:
			case 80:
				break;
			}
		}
	}
}
void view_list_of_classes()
{
	int key;
	while (true)
	{
		string year;
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap nam hoc :";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
		case 72:
		case 80:
			break;
		}
		gotoxy(55, 11);
		getline(cin, year);
		ifstream file;
		file.open("../academic_years/" + year + "/classes.csv");
		if (!file.fail())
		{
			int y = 11, x=40;

			system("cls");
			gotoxy(55, 4);
			cout << "HCMUS";
			drawbox(33, 5, 53, 20);
			gotoxy(50, 8);
			cout << "List of class in "<<year;
			while (!file.eof())
			{
				string str;
				file >> str;
				if (str == "")
					break;
				gotoxy(x, y);
				cout << str;
				y += 2;
				if (y >= 19)
				{
					x += 10;
					y = 11;
				}
			}
			gotoxy(38, 22);
			cout << "BACK";
			cin.ignore();
			return;
		}
		else
		{
			system("cls");
			gotoxy(50, 13);
			cout << "Khong ton tai nam hoc vua nhap.";
			Sleep(2000);
			gotoxy(38, 22);
			cout << "BACK";
			key = _getch();
			switch (key)
			{
			case 13:
				return;
			case 72:
			case 80:
				break;
			}
		}
	}
}
//void view_academic_years(list_student lstudent)
//{
//	int key;
//	while (true)
//	{
//		system("cls");
//		gotoxy(55, 4);
//		cout << "HCMUS";
//		drawbox(33, 5, 53, 20);
//		gotoxy(40, 11);
//		cout << "Nhap nam hoc : ";
//		gotoxy(40, 13);
//		cout << "Nhap ten lop: ";
//		gotoxy(38, 22);
//		cout << "BACK";
//		key = _getch();
//		switch (key)
//		{
//		case 13:
//			return;
//			break;
//		case 72:
//		case 80:
//			break;
//		}
//		gotoxy(54, 11);
//		getline(cin, year);
//		gotoxy(53, 13);
//		getline(cin, class_name);
//		path = "../academic_years/" + year + "/" + class_name + "/" + class_name + ".csv";+
//		system("cls");
//		list_student lstudent;
//		init_list_student(lstudent);
//		if (get_file_student(lstudent, path))
//		{
//			display_student(lstudent);
//			system("pause");
//			break;
//		}
//	}
//}
void add_students_manually(list_student &lstudent_for_new_class)
{
	int key;
	int n;
	int pos = 8;
		do
		{
			system("cls");
			gotoxy(55, 4);
			cout << "HCMUS";
			drawbox(33, 5, 53, 20);
			gotoxy(40, 11);
			cout << "Nhap so luong sinh vien:";
			gotoxy(38, 22);
			cout << "BACK";
			key = _getch();
			switch (key)
			{
			case 13:
				return;
				break;
			case 72:
			case 80:
				break;
			}
			gotoxy(65, 11);
			cin >> n;
		} while (n < 1);
		cin.ignore();
		system("cls");
		for (int i = 0; i < n; i++)
		{
			student* std = enter_infor_for_student(pos);
			add_student(lstudent_for_new_class, std);
		}
		update_student_to_file(lstudent_for_new_class, "student.csv");
}
void add_students_by_importing_file(list_student& lstudent_for_new_class)
{
	int key;
	string duong_dan;
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap duong dan: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(57, 11);
		getline(cin, duong_dan);

		if (get_file_student(lstudent_for_new_class, duong_dan))
		{
			system("cls");
			gotoxy(40, 13);
			cout << "Import file thanh cong.";
			Sleep(2000);
			break;
		}
	}
	update_student_to_file(lstudent_for_new_class, "student.csv");
}
void add_classes()
{
	int key;
	string year, path, class_name;
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap nam hoc : ";
		gotoxy(40, 13);
		cout << "Nhap ten lop: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(54, 11);
		getline(cin, year);
		gotoxy(53, 13);
		getline(cin, class_name);
		path = "../academic_years/" + year + "/" + class_name;
		int kt = _mkdir(path.c_str());
		if (kt == 0)
		{
			ofstream file;
			file.open("../academic_years/" + year + "/classes.csv", ios::app);
			file << class_name << endl;
			system("cls");
			gotoxy(40, 13);
			cout << "Lop hoc moi da duoc tao.";
			Sleep(2000);
			break;
		}
		else
		{
			system("cls");
			gotoxy(50, 13);
			cout << strerror(errno);
			Sleep(2000);
			key = _getch();
			switch (key)
			{
			case 13:
				return;
				break;
			case 72:
			case 80:
				break;
			}
		}
	}
	int pos = 11;
	int x;
	int sl = 0;
	list_student lstudent_for_new_class;
	init_list_student(lstudent_for_new_class);
	do
	{
		do
		{
			system("cls");
			gotoxy(55, 4);
			cout << "HCMUS";
			drawbox(33, 5, 53, 20);
			gotoxy(47, 7);
			cout << "ADD STUDENT TO NEWLY-CREATED CLASS";
			gotoxy(45, 11);
			cout << "Add students manually";
			gotoxy(45, 13);
			cout << "Add students by importing file";
			gotoxy(38, 22);
			cout << "BACK";
			x = control(pos, sl, 2);
			sl++;
		} while (x != 0);
		switch (pos)
		{
		case 11:
			add_students_manually(lstudent_for_new_class);
			if (save_student_to_file(lstudent_for_new_class, path + "/" + class_name + ".csv"))
			{
				system("cls");
				gotoxy(40, 13);
				cout << "Da luu vao file thanh cong.";
				Sleep(2000);
			}
			break;
		case 13:
			add_students_by_importing_file(lstudent_for_new_class);
			save_student_to_file(lstudent_for_new_class, path + "/" + class_name + ".csv");
			break;
		case 22:
			break;
		}
	} while (pos != 22);
}
void delete_student(list_student& lstudent)
{
	int key;
	bool ks = true;
	string id;
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap ID sinh vien can xoa: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(66, 11);
		getline(cin, id);
		student* std = lstudent.head;
		while (std != NULL)
		{
			if (std->student_ID == id)
			{
				del_student(lstudent, std);
				system("cls");
				gotoxy(40, 13);
				cout << "Da xoa sinh vien ra khoi file.";
				Sleep(2000);
				ks = false;
				break;
			}
			std = std->next;

		}
		if (ks)
		{
			system("cls");
			gotoxy(40, 13);
			cout << "Khong tim thay id cua sinh vien vua nhap.";
			Sleep(2000);
			key = _getch();
			switch (key)
			{
			case 13:
				return;
				break;
			case 72:
			case 80:
				break;
			}
		}
		else
			break;
	}
}
void modify_classes()
{
	int key;
	string year, path, class_name;
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap nam hoc : ";
		gotoxy(40, 13);
		cout << "Nhap ten lop: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(54, 11);
		getline(cin, year);
		gotoxy(53, 13);
		getline(cin, class_name);
		path = "../academic_years/" + year + "/" + class_name + "/" + class_name + ".csv";
		list_student lstudent;
		init_list_student(lstudent);
		if (get_file_student(lstudent, path))
		{
			int pos = 11;
			int x;
			int sl = 0;
			do
			{
				do
				{
					system("cls");
					gotoxy(55, 4);
					cout << "HCMUS";
					drawbox(33, 5, 53, 20);
					gotoxy(55, 7);
					cout << "MODIFY STUDENTS";
					gotoxy(45, 11);
					cout << "View list of students in current class";
					gotoxy(45, 13);
					cout << "Add students manually";
					gotoxy(45, 15);
					cout << "Add students by importing file";
					gotoxy(45, 17);
					cout << "Delete student from current class";
					gotoxy(38, 22);
					cout << "BACK";
					x = control(pos, sl, 4);
					sl++;
				} while (x != 0);
				switch (pos)
				{
				case 11:
					display_student(lstudent);
					system("pause");
					break;
				case 13:
					add_students_manually(lstudent);
					if(save_student_to_file(lstudent, path))
					{
						system("cls");
						gotoxy(40, 13);
						cout << "Da luu vao file thanh cong.";
						Sleep(2000);
					}
					update_student_to_file(lstudent, "student.csv");
					break;
				case 15:
					add_students_by_importing_file(lstudent);
					save_student_to_file(lstudent, path);
					update_student_to_file(lstudent, "student.csv");
					break;
				case 17:
					delete_student(lstudent);
					save_student_to_file(lstudent, path);
					break;
				case 22:
					break;
				}
			} while (pos != 22);
		}
		else
		{
			gotoxy(30, 13);
			cout << "Lop nay chua co file sinh vien, hay them sinh vien vao lop nay.";
			Sleep(2000);
			int pos = 11;
			int x;
			int sl = 0;
			do
			{
				do
				{
					system("cls");
					gotoxy(55, 4);
					cout << "HCMUS";
					drawbox(33, 5, 53, 20);
					gotoxy(50, 7);
					cout << "MODIFY STUDENTS";
					gotoxy(45, 11);
					cout << "Add students manually";
					gotoxy(45, 13);
					cout << "Add students by importing file";
					gotoxy(38, 22);
					cout << "BACK";
					x = control(pos, sl, 2);
					sl++;
				} while (x != 0);
				switch (pos)
				{
				case 11:
					add_students_manually(lstudent);
					if (save_student_to_file(lstudent, path))
					{
						system("cls");
						gotoxy(40, 13);
						cout << "Da luu vao file thanh cong.";
						Sleep(2000);
					}
					break;
				case 13:
					add_students_by_importing_file(lstudent);
					if (save_student_to_file(lstudent, path))
					{
						system("cls");
						gotoxy(40, 13);
						cout << "Da luu vao file thanh cong.";
						Sleep(2000);
					}
					break;
				case 22:
					break;
				}
			} while (pos != 22);
		}
}
void course_management()
{
	int pos = 11;
	int x;
	int sl = 0;
	do
	{
		do
		{
			system("cls");
			gotoxy(55, 4);
			cout << "HCMUS";
			drawbox(33, 5, 53, 20);
			gotoxy(50, 7);
			cout << "COURSE MANAGEMENT";
			gotoxy(45, 11);
			cout << "Create a new semester";
			gotoxy(45, 13);
			cout << "View list of courses";
			gotoxy(45, 15);
			cout << "Modify courses";
			gotoxy(45, 17);
			cout << "View list of student in a course";
			gotoxy(45, 19);
			cout << "Manage scoreboard of a course";
			gotoxy(38, 22);
			cout << "BACK";
			x = control(pos, sl, 5);
			sl++;
		} while (x != 0);
		switch (pos)
		{
		case 11:
			create_new_semester();
			break;
		case 13:
			view_list_of_courses_in_course_management_menu();
			break;
		case 15:
			modify_course();
			break;
		case 17:
			view_list_of_student_in_a_course();
			break;
		case 19:
			manage_scoreboard_of_a_course();
			break;
		case 22:
			return;
		}
	} while (pos != 22);
}
void create_new_semester()
{
	int key;
	string year, path, number, start, end;
	Date date;
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap hoc ky so may: ";
		gotoxy(40, 13);
		cout << "Nhap ngay bat dau: ";
		gotoxy(40, 15);
		cout << "Nhap ngay ket thuc: ";
		gotoxy(40, 17);
		cout << "Nhap nam hoc cua hoc ky: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(61, 11);
		getline(cin, number);
		do
		{
			gotoxy(60, 13);
			getline(cin, start);
			date = convert_str_to_date(start);
		} while (!check_day_of_birth(date));
		start = convert_date_to_str(date);
		do
		{
			gotoxy(61, 15);
			getline(cin, end);
			date = convert_str_to_date(end);
		} while (!check_day_of_birth(date));
		end = convert_date_to_str(date);
		gotoxy(66, 17);
		getline(cin, year);
		path = "../academic_years/" + year+"/Semester "+number;
		int kt = _mkdir(path.c_str());
		if (kt == 0)
		{
			system("cls");
			gotoxy(40, 13);
			cout << "Hoc ky "<<number<<" da duoc tao trong nam "<<year<<" .";
			Sleep(2000);
			break;
		}
		else
		{
			system("cls");
			gotoxy(50, 13);
			cout << strerror(errno);
			Sleep(2000);
			key = _getch();
			switch (key)
			{
			case 13:
				return;
				break;
			case 72:
			case 80:
				break;
			}
		}
	}
	ofstream file;
	file.open(path + "/courses.csv");
	string temp = start + " -- " + end;
	file << temp << endl;
	file.close();
	int pos = 11;
	int x;
	int sl = 0;
	list_course lcourse;
	init_list_course(lcourse);
	do
	{
		do
		{
			system("cls");
			gotoxy(55, 4);
			cout << "HCMUS";
			drawbox(33, 5, 53, 20);
			gotoxy(50, 7);
			cout << "COURSE MANAGEMENT";
			gotoxy(45, 11);
			cout << "Add a course";
			gotoxy(45, 13);
			cout << "View list of courses";
			gotoxy(38, 22);
			cout << "BACK";
			x = control(pos, sl, 2);
			sl++;
		} while (x != 0);
		switch (pos)
		{
		case 11:
			add_a_course(lcourse, path, temp);
			break;
		case 13:
			view_list_of_courses(path + "/courses.csv");
			system("pause");
			break;
		case 22:
			return;
		}
	} while (pos != 22);
}
void add_a_course(list_course& lcourse, string path, string duration)
{
	system("cls");
	int pos = 8;
	get_file_course(lcourse, path + "/courses.csv", duration);
	course* crs = enter_infor_for_course(pos);
	system("cls");
	gotoxy(40, 13);
	cout << "Hay them file hoc sinh.";
	Sleep(2000);
	system("cls");
	list_student lstudent;
	init_list_student(lstudent);
	add_students_by_importing_file(lstudent);
	save_student_to_file(lstudent, path + "/" + crs->course_id+".csv");
	int sl = 0;
	for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
		sl++;
	crs->number_of_enroller = sl;
	add_course(lcourse, crs);
	courses_of_each_student(lstudent, path, lcourse, duration);
	if (update_course_to_file(lcourse, path + "/courses.csv", duration))
	{
		system("cls");
		gotoxy(40, 13);
		cout << "Da them mot khoa hoc thanh cong.";
		Sleep(2000);
	}
}
bool view_list_of_courses(string path)
{
	string duration;
	list_course lcourse;
	init_list_course(lcourse);
	if (get_file_course(lcourse, path, duration))
	{
		system("cls");
		gotoxy(2, 3);
		cout << "Length of course: " << duration;
		display_course(lcourse);
		system("pause");
		return true;
	}
	else
		return false;
	
}
void view_list_of_courses_in_course_management_menu()
{
	int key;
	string year, path, number;
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap hoc ky so may: ";
		gotoxy(40, 13);
		cout << "Nhap nam hoc cua hoc ky: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(61, 11);
		getline(cin, number);
		gotoxy(66, 13);
		getline(cin, year);
		path = "../academic_years/" + year + "/Semester " + number;
		if (view_list_of_courses(path + "/courses.csv"))
			break;
		else
		{
			system("cls");
			gotoxy(40, 13);
			perror("Error is: ");
			Sleep(2000);
		}
	}
}
void view_list_of_student_in_a_course()
{
	int key;
	string year, path, number, duration, courseID;
	list_student lstudent;
	init_list_student(lstudent);
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap hoc ky : ";
		gotoxy(40, 13);
		cout << "Nhap nam hoc cua hoc ky: ";
		gotoxy(40, 15);
		cout << "Nhap ma khoa hoc muon xem: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(55, 11);
		getline(cin, number);
		gotoxy(66, 13);
		getline(cin, year);
		gotoxy(68, 15);
		getline(cin, courseID);
		path = "../academic_years/" + year + "/Semester " + number;
		if (get_file_student(lstudent, path + "/" + courseID + ".csv"))
		{
			display_student(lstudent);
			system("pause");
			break;
		}
	}
}
void modify_course()
{
	int pos = 11;
	int x;
	int sl = 0;
	do
	{
		do
		{
			system("cls");
			gotoxy(55, 4);
			cout << "HCMUS";
			drawbox(33, 5, 53, 20);
			gotoxy(50, 7);
			cout << "MODIFY COURSE";
			gotoxy(45, 11);
			cout << "Update course information";
			gotoxy(45, 13);
			cout << "Add a student to a course";
			gotoxy(45, 15);
			cout << "Remove a student from a course";
			gotoxy(45, 17);
			cout << "add a course";
			gotoxy(45, 19);
			cout << "Delete a course";
			gotoxy(38, 22);
			cout << "BACK";
			x = control(pos, sl, 5);
			sl++;
		} while (x != 0);
		switch (pos)
		{
		case 11:
			update_course_information();
			break;
		case 13:
			add_a_student_to_the_course();
			break;
		case 15:
			remove_a_student_from_the_course();
			break;
		case 17:
			add_courses();
			break;
		case 19:
			delete_a_course();
			break;
		case 22:
			//staff_menu(staff, lstaff);
			return;
			break;
		}
	} while (pos != 22);
}
void update_course_information()
{
	int key, pos=8;
	string year, path, number, duration;
	list_course lcourse;
	init_list_course(lcourse);
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap hoc ky : ";
		gotoxy(40, 13);
		cout << "Nhap nam hoc cua hoc ky: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(55, 11);
		getline(cin, number);
		gotoxy(66, 13);
		getline(cin, year);
		path = "../academic_years/" + year + "/Semester " + number;
		if (get_file_course(lcourse, path + "/courses.csv", duration))
			break;
		else
		{
			system("cls");
			gotoxy(40, 13);
			perror("Error is: ");
			Sleep(2000);
		}
	}
	string courseID;
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap ma khoa hoc muon cap nhat: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(73, 11);
		getline(cin, courseID);
		system("cls");
		for (course* temp = lcourse.head; temp != NULL; temp = temp->next)
		{
			if (temp->course_id == courseID)
			{
				drawbox(10, 5, 98, 2);
				gotoxy(11, 6);
				cout << " Course id |";
				gotoxy(24, 6);
				cout << "      Course name     |";
				gotoxy(48, 6);
				cout << " Class name |";
				gotoxy(62, 6);
				cout << "   Teacher name   |";
				gotoxy(81, 6);
				cout << " Credit |";
				gotoxy(91, 6);
				cout << "   Day   |";
				gotoxy(102, 6);
				cout << " Session ";
				string str;
				gotoxy(11, pos);
				getline(cin, temp->course_id);
				gotoxy(24, pos);
				getline(cin, temp->course_name);
				gotoxy(48, pos);
				getline(cin, temp->class_name);
				gotoxy(62, pos);
				getline(cin, temp->teacher_name);
				gotoxy(81, pos);
				getline(cin, str);
				temp->number_of_credit = stoi(str);
				gotoxy(91, pos);
				getline(cin, temp->week_day);
				gotoxy(100, pos++);
				getline(cin, temp->session);
				if (save_course_to_file(lcourse, path + "/courses.csv", duration))
				{
					update_course_for_each_student(courseID, path, temp);
					string oldname = path + "/" + courseID + ".csv";
					string newname = path + "/" + temp->course_id + ".csv";
					rename(oldname.c_str(), newname.c_str());
					system("cls");
					gotoxy(40, 13);
					cout << "Da cap nhat khoa hoc thanh cong.";
					Sleep(2000);
					return;
				}
			}
		}
		gotoxy(45, 13);
		cout << "Nhap ma mon hoc sai.";
		Sleep(2000);
	}
}
void add_a_student_to_the_course()
{
	int key;
	string year, path, number, duration, courseID;
	list_course lcourse;
	init_list_course(lcourse);
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap hoc ky : ";
		gotoxy(40, 13);
		cout << "Nhap nam hoc cua hoc ky: ";
		gotoxy(40, 15);
		cout << "Nhap ma khoa hoc muon them hoc sinh: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(55, 11);
		getline(cin, number);
		gotoxy(66, 13);
		getline(cin, year);
		gotoxy(77, 15);
		getline(cin, courseID);
		path = "../academic_years/" + year + "/Semester " + number;
		list_student lstudent;
		init_list_student(lstudent);
		if (get_file_student(lstudent, path + "/" + courseID + ".csv"))
		{
			system("cls");
			int pos = 8;
			student* std = enter_infor_for_student(pos);
			add_student(lstudent, std);
			if (update_student_to_file(lstudent, path + "/" + courseID + ".csv"))
			{
				get_file_course(lcourse, path + "/courses.csv", duration);
				for (course* tam = lcourse.head; tam != NULL; tam = tam->next)
				{
					if (tam->course_id == courseID)
					{
						init_list_course(lcourse);
						get_file_course(lcourse, path + "/courses.csv", duration);
						for (course* tam = lcourse.head; tam != NULL; tam = tam->next)
						{
							if (tam->course_id == courseID)
							{
								tam->number_of_enroller++;
								break;
							}
						}
						save_course_to_file(lcourse, path + "/courses.csv", duration);
						list_course lcourse1;
						init_list_course(lcourse1);
						tam->number_of_enroller++;
						add_course(lcourse1, tam);
						update_course_to_file(lcourse1, "../academic_years/courseforstudent/" + lstudent.tail->student_ID + ".csv", duration);
					}
				}
				system("cls");
				gotoxy(40, 13);
				cout << "Da them hoc sinh thanh cong.";
				Sleep(2000);
				break;
			}
		}
		else
		{
			gotoxy(45, 13);
			perror("Error is: ");
			Sleep(2000);
		}
	}
}
void remove_a_student_from_the_course()
{
	int key;
	string year, path, number, duration, courseID;
	list_course lcourse;
	init_list_course(lcourse);
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap hoc ky : ";
		gotoxy(40, 13);
		cout << "Nhap nam hoc cua hoc ky: ";
		gotoxy(40, 15);
		cout << "Nhap ma khoa hoc muon xoa hoc sinh: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(55, 11);
		getline(cin, number);
		gotoxy(66, 13);
		getline(cin, year);
		gotoxy(75, 15);
		getline(cin, courseID);
		path = "../academic_years/" + year + "/Semester " + number;
		list_student lstudent;
		init_list_student(lstudent);
		if (get_file_student(lstudent, path + "/" + courseID + ".csv"))
		{

			bool ks = true;
			string id;
			while (true)
			{
				system("cls");
				gotoxy(55, 4);
				cout << "HCMUS";
				drawbox(33, 5, 53, 20);
				gotoxy(40, 11);
				cout << "Nhap ID sinh vien can xoa: ";
				gotoxy(38, 22);
				cout << "BACK";
				key = _getch();
				switch (key)
				{
				case 13:
					return;
					break;
				case 72:
				case 80:
					break;
				}
				gotoxy(66, 11);
				getline(cin, id);
				student* std = lstudent.head;
				while (std != NULL)
				{
					if (std->student_ID == id)
					{
						string duration;
						get_file_course(lcourse, "../academic_years/courseforstudent/" + id + ".csv", duration);
						for (course* tam = lcourse.head; tam != NULL; tam = tam->next)
						{
							if (tam->course_id == courseID)
							{
								del_course(lcourse, tam);
								break;
							}
						}
						save_course_to_file(lcourse, "../academic_years/courseforstudent/" + id + ".csv", duration);
						init_list_course(lcourse);
						get_file_course(lcourse, path + "/courses.csv", duration);
						for (course* tam = lcourse.head; tam != NULL; tam = tam->next)
						{
							if (tam->course_id == courseID)
							{
								tam->number_of_enroller--;
								break;
							}
						}
						save_course_to_file(lcourse, path + "/courses.csv", duration);
						del_student(lstudent, std);
						ks = false;
						break;
					}
					std = std->next;
				}
				save_student_to_file(lstudent, path + "/" + courseID + ".csv");
				if (ks)
				{
					system("cls");
					gotoxy(40, 13);
					cout << "Khong tim thay id cua sinh vien vua nhap.";
					Sleep(2000);
				}
				else
					break;
			}
			system("cls");
			gotoxy(40, 13);
			cout << "Da xoa mot hoc sinh thanh cong.";
			Sleep(2000);
			break;

		}
		else
		{
			gotoxy(45, 13);
			cout << "Khong ton tai khoa hoc.";
			Sleep(2000);
		}
	}
}
void add_courses()
{
	int key, pos = 8;
	string year, path, number, duration;
	list_course lcourse;
	init_list_course(lcourse);
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap hoc ky : ";
		gotoxy(40, 13);
		cout << "Nhap nam hoc cua hoc ky: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(55, 11);
		getline(cin, number);
		gotoxy(66, 13);
		getline(cin, year);
		path = "../academic_years/" + year + "/Semester " + number;
			system("cls");
			course* crs = enter_infor_for_course(pos);
			system("cls");
			gotoxy(40, 13);
			cout << "Da them mot khoa hoc thanh cong, hay them file hoc sinh.";
			Sleep(2000);
			system("cls");
			list_student lstudent;
			init_list_student(lstudent);
			add_students_by_importing_file(lstudent);
			save_student_to_file(lstudent, path + "/" + crs->course_id + ".csv");
			int sl = 0;
			for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
				sl++;
			crs->number_of_enroller = sl;
			add_course(lcourse, crs);
			courses_of_each_student(lstudent, path, lcourse, duration);
			if (update_course_to_file(lcourse, path + "/courses.csv", duration))
			{
				system("cls");
				gotoxy(40, 13);
				cout << "Da them mot khoa hoc thanh cong.";
				Sleep(2000);
				break;
			}
			else
			{
				system("cls");
				gotoxy(40, 13);
				perror("Error is: ");
				Sleep(2000);
			}
	}
}
void delete_a_course()
{
	int key, pos = 8;
	string year, path, number, duration;
	list_course lcourse;
	init_list_course(lcourse);
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap hoc ky : ";
		gotoxy(40, 13);
		cout << "Nhap nam hoc cua hoc ky: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(55, 11);
		getline(cin, number);
		gotoxy(66, 13);
		getline(cin, year);
		path = "../academic_years/" + year + "/Semester " + number;
		if (get_file_course(lcourse, path + "/courses.csv", duration))
			break;
	}
	string courseID;
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap ma khoa hoc muon xoa: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(68, 11);
		getline(cin, courseID);
		system("cls");
		for (course* temp = lcourse.head; temp != NULL; temp = temp->next)
		{
			if (temp->course_id == courseID)
			{
				delete_course_for_each_student(courseID, path);
				del_course(lcourse, temp);
				string path_for_file_student = path + "/" + courseID + ".csv";
				remove(path_for_file_student.c_str());
				if (save_course_to_file(lcourse, path + "/courses.csv", duration))
				{
					system("cls");
					gotoxy(40, 13);
					cout << "Da xoa khoa hoc.";
					Sleep(2000);
					return;
				}
			}
		}
		gotoxy(45, 13);
		cout << "Nhap ma mon hoc sai.";
		Sleep(2000);
	}
}
void manage_scoreboard_of_a_course()
{
	int key;
	string year, path, number, courseID;
	list_scoreboard lscoreboard;
	init_list_scoreboard(lscoreboard);
	list_course lcourse;
	init_list_course(lcourse);
	string duration;
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap hoc ky cua khoa hoc: ";
		gotoxy(40, 13);
		cout << "Nhap nam hoc cua hoc ky: ";
		gotoxy(40, 15);
		cout << "Nhap ma khoa hoc muon ghi diem: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(66, 11);
		getline(cin, number);
		gotoxy(65, 13);
		getline(cin, year);
		gotoxy(72, 15);
		getline(cin, courseID);
		path = "../academic_years/" + year + "/Semester " + number+"/"+courseID;
		if (!get_file_course(lcourse, "../academic_years/" + year + "/Semester " + number + "/courses.csv", duration))
		{
			system("cls");
			gotoxy(40, 13);
			perror("Error is: ");
			Sleep(2000);
			continue;
		}
		course* temp = lcourse.head;
		while (temp != NULL)
		{
			if (temp->course_id == courseID)
				break;
			temp = temp->next;
		}
		int pos = 11;
		int x;
		int sl = 0;
		do
		{
			do
			{
				system("cls");
				gotoxy(55, 4);
				cout << "HCMUS";
				drawbox(33, 5, 53, 20);
				gotoxy(50, 7);
				cout << "MANAGE SCOREBOARD";
				gotoxy(45, 11);
				cout << "Export scoreboard of a course";
				gotoxy(45, 13);
				cout << "Import scoreboard";
				gotoxy(45, 15);
				cout << "View scoreboard of a course";
				gotoxy(45, 17);
				cout << "Update a student's result";
				gotoxy(45, 19);
				cout << "View scoreboard of a class";
				gotoxy(38, 22);
				cout << "BACK";
				x = control(pos, sl, 5);
				sl++;
			} while (x != 0);
			switch (pos)
			{
			case 11:
				if (export_scoreboard(path))
				{
					system("cls");
					gotoxy(40, 13);
					cout << "Da export file thanh cong.";
					Sleep(2000);
				}
				break;
			case 13:
				import_scoreboard(lscoreboard, path, temp);
				break;
			case 15:
				system("cls");
				display_scoreboard_of_a_course(lscoreboard);
				system("pause");
				break;
			case 17:
				update_scoreboard(path, lscoreboard, courseID);
				break;
			case 19:
				view_scoreboard_of_a_class();
				break;
			case 22:
				return;
			}
		} while (pos != 22);
	}
}
bool export_scoreboard(string path)
{
	list_student lstudent;
	init_list_student (lstudent);
	while (true)
	{
		if (get_file_student(lstudent, path + ".csv"))
		{
			ofstream file(path + "_scoreboard.csv");
			if (file.is_open())
			{
				file << "No" << "," << "Student ID" << "," << "Student full name" << "," << "Midterm mark" << "," << "Final mark" << "," << "Total mark" << "," << "Other mark" << endl;
				for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
				{
					file << temp->no << "," <<temp->student_ID<<"," << temp->first_name + " " + temp->last_name << "," << "," << "," << "," << "," << endl;
				}
				file.close();
			}
			return true;
		}
		else
		{
			system("cls");
			gotoxy(40, 13);
			perror("Error is: ");
			Sleep(2000);
			return false;
		}
	}
}
void update_scoreboard(string path, list_scoreboard lscoreboard, string courseID)
{
		int key;
		bool ks = true;
		string id;
		while (true)
		{
			system("cls");
			gotoxy(55, 4);
			cout << "HCMUS";
			drawbox(33, 5, 53, 20);
			gotoxy(35, 11);
			cout << "Nhap ID sinh vien muon cap nhat diem:";
			gotoxy(38, 22);
			cout << "BACK";
			key = _getch();
			switch (key)
			{
			case 13:
				return;
				break;
			case 72:
			case 80:
				break;
			}
			gotoxy(72, 11);
			getline(cin, id);
			system("cls");
			scoreboard* score = lscoreboard.head;
			while (score != NULL)
			{
				if (score->student_id == id)
				{
					enter_scoreboard(score);
					save_file_scoreboard(path + "_scoreboard.csv", lscoreboard);
					update_scoreboard_for_a_student("../academic_years/courseforstudent/" + id + "_scoreboard.csv", score, courseID);
					system("cls");
					gotoxy(40, 13);
					cout << "Da cap nhat diem so cua sinh vien.";
					Sleep(2000);
					ks = false;
					break;
				}
				score = score->next;
			}
			if (ks)
			{
				system("cls");
				gotoxy(40, 13);
				cout << "Khong tim thay id cua sinh vien vua nhap.";
				Sleep(2000);
				key = _getch();
				switch (key)
				{
				case 13:
					return;
					break;
				case 72:
				case 80:
					break;
				}
			}
			else
				break;
		}
}
void import_scoreboard(list_scoreboard &lscoreboard, string path, course* course)
{
	int key;
	string duong_dan;
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap duong dan: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(57, 11);
		getline(cin, duong_dan);
		if (get_file_scoreboard_of_a_course(duong_dan, lscoreboard))
		{
			scoreboard_of_each_student(lscoreboard, course);
			save_file_scoreboard(path + "_scoreboard.csv", lscoreboard);
			system("cls");
			gotoxy(40, 13);
			cout << "Import file thanh cong.";
			Sleep(2000);
			break;
		}
	}
}
void view_scoreboard_of_a_class()
{
	int key;
	string year, path, class_name;
	while (true)
	{
		system("cls");
		gotoxy(55, 4);
		cout << "HCMUS";
		drawbox(33, 5, 53, 20);
		gotoxy(40, 11);
		cout << "Nhap nam hoc : ";
		gotoxy(40, 13);
		cout << "Nhap ten lop: ";
		gotoxy(38, 22);
		cout << "BACK";
		key = _getch();
		switch (key)
		{
		case 13:
			return;
			break;
		case 72:
		case 80:
			break;
		}
		gotoxy(54, 11);
		getline(cin, year);
		gotoxy(53, 13);
		getline(cin, class_name);
		path = "../academic_years/" + year + "/" + class_name + "/" + class_name + ".csv";
		list_student lstudent;
		init_list_student(lstudent);
		if (get_file_student(lstudent, path))
		{
			display_scoreboard_of_a_class(lstudent);
			system("pause");
			break;
		}
		else
		{
			system("cls");
			gotoxy(40, 13);
			perror("Error is: ");
			Sleep(2000);
		}
	}
}
void staff_menu(staff* staff, list_staff lstaff)
{
	int pos = 11;
	int x;
	int sl = 0;
	do {
		do
		{
			system("cls");
			gotoxy(55, 4);
			cout << "HCMUS";
			gotoxy(45, 6);
			cout << "Welcome: " << staff->first_name << " " << staff->last_name;
			drawbox(33, 5, 53, 20);
			gotoxy(40, 11);
			cout << "PROFILE";
			gotoxy(40, 13);
			cout << "Manage academic years";
			gotoxy(40, 15);
			cout << "Course Management";
			gotoxy(40, 17);
			cout << "Change Password";
			gotoxy(38, 22);
			cout << "LOG OUT";
			x = control(pos, sl, 4);
			sl++;
		} while (x != 0);
		switch (pos)
		{
		case 11:
			profile(staff, lstaff);
			break;
		case 13:
			manage_academic_years(staff, lstaff);
			break;
		case 15:
			course_management();
			break;
		case 17:
			change_password(staff, lstaff);
			break;
		case 22:
			login_system();
			break;
		}
	} while (pos != 22);
}
void login_system()
{
	list_student lstudent;
	list_staff lstaff;
	init_list_staff(lstaff);
	init_list_student(lstudent);
	get_file_staff(lstaff, "staff.csv");
	get_file_student(lstudent,"student.csv");
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