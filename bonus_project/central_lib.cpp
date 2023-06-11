#include "central_lib.h"
void gotoxy(short x, short y)
{
    COORD coor = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}
void drawbox(int col, int row, int width, int height)
{
    gotoxy(col, row);
    for (int i = 0; i < width; i++)
        cout << char(223);
    for (int i = 0; i < height; i++)
    {
        gotoxy(col + width, row + i);
        cout << char(223);
    }
    for (int i = width + col; i > col; i--)
    {
        gotoxy(i, row + height);
        cout << char(223);
    }
    for (int i = row + height; i > row; i--)
    {
        gotoxy(col, i);
        cout << char(223);
    }
}
void init_list_student(list_student& lstudent)
{
    lstudent.head = lstudent.tail = NULL;
    lstudent.size = 0;
}
void init_list_staff(list_staff& lstaff)
{
    lstaff.head = lstaff.tail = NULL;
    lstaff.size = 0;
}
void init_list_course(list_course& lcourse)
{
    lcourse.head = lcourse.tail = NULL;
    lcourse.size = 0;
}
void init_list_class(list_class& lclass)
{
    lclass.head = lclass.tail = NULL;
    lclass.size = 0;
}
void init_list_scoreboard(list_scoreboard& lscoreboard)
{
    lscoreboard.head = lscoreboard.tail = NULL;
}
void add_student(list_student& lstudent, student* add)
{
    if (lstudent.head == NULL)
        lstudent.head = lstudent.tail = add;
    else
    {
        lstudent.tail->next = add;
        add->prev = lstudent.tail;
        lstudent.tail = add;
    }
    lstudent.size++;
}
student* enter_infor_for_student(int &pos)
{
    drawbox(15, 5, 95, 2);
    gotoxy(16, 6);
    cout << " No |";
    gotoxy(22, 6);
    cout <<"  MSSV   |";
    gotoxy(33, 6);
    cout << " Password |";
    gotoxy(45, 6);
    cout << " First name |";
    gotoxy(59, 6);
    cout<<" Last name |";
    gotoxy(72, 6);
    cout << " Gender |";
    gotoxy(82, 6);
    cout << " Date of birth |";
    gotoxy(99, 6);
    cout << " Social ID ";
    student* temp = new student;
    string str;
    gotoxy(16, pos);
    getline(cin, str);
    temp->no = stoi(str);
    gotoxy(22, pos);
    getline(cin, temp->student_ID);
    gotoxy(33, pos);
    getline(cin, temp->password);
    gotoxy(45, pos);
    getline(cin, temp->first_name);
    gotoxy(59, pos);
    getline(cin, temp->last_name);
    gotoxy(72, pos);
    getline(cin, temp->gender);
    do
    {
        gotoxy(82, pos);
        getline(cin, str);
        temp->date_of_birth = convert_str_to_date(str);
    } while (!check_day_of_birth(temp->date_of_birth));
    gotoxy(99, pos++);
    getline(cin, temp->social_ID);
    temp->next = temp->prev = NULL;
    return temp;
}
course* enter_infor_for_course(int &pos)
{
    drawbox(10, 5, 105, 2);
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
    course* crs = new course;
    string str;
    gotoxy(11, pos);
    getline(cin, crs->course_id);
    gotoxy(24, pos);
    getline(cin, crs->course_name);
    gotoxy(48, pos);
    getline(cin, crs->class_name);
    gotoxy(62, pos);
    getline(cin, crs->teacher_name);
    gotoxy(82, pos);
    getline(cin, str);
    crs->number_of_credit = stoi(str);
    gotoxy(92, pos);
    getline(cin, crs->week_day);
    gotoxy(101, pos++);
    getline(cin, crs->session);
    crs->next = crs->prev = NULL;
    return crs;
}
void del_student(list_student& lstudent, student* del)
{
    if (lstudent.head == NULL) return;
    else if (lstudent.head->next == NULL&& del==lstudent.head)// DS co 1 phan tu
    {
        student* temp = lstudent.head;
        delete temp;
        lstudent.size--;
        lstudent.head = lstudent.tail = NULL;
        return;
    }
    else if (lstudent.head == del)// xoa dau
    {
        student* temp = lstudent.head;
        lstudent.head = temp->next;
        lstudent.head->prev = NULL;
        delete temp;
        lstudent.size--;
       
        return;
    }
    else if (lstudent.tail == del)// xoa cuoi
    {
        student* temp = lstudent.tail;
        lstudent.tail = temp->prev;
        lstudent.tail->next = NULL;
        delete temp;
        lstudent.size--;
        
        return;
    }
    else// xoa giua
    {
        for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
        {
            if (temp == del)
            {
                student* tam = temp;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete tam;
                lstudent.size--;
                return;
            }
        }
    }
}
//void save_student_to_file(student* save)
//{
//    ofstream file;
//    file.open("student.csv");
//    for (student* temp = save; temp != NULL; temp = temp->next)
//    {
//        file << temp->no << "," << temp->student_ID << "," << temp->password << "," << temp->first_name << "," << temp->last_name << "," << temp->gender << ","
//            << temp->date_of_birth.day << "/" << temp->date_of_birth.month << "/" << temp->date_of_birth.year << "," << temp->social_ID;
//        if (temp != NULL) file << endl;
//    }
//    file.close();
//}
//void save_staff_to_file(staff* save)
//{
//    ofstream file;
//    file.open("staff.csv");
//    for (staff* temp = save; temp != NULL; temp = temp->next)
//    {
//        file << temp->no << "," << temp->staff_ID << "," << temp->password << "," << temp->first_name << "," << temp->last_name << "," << temp->gender << "," 
//            << temp->date_of_birth.day << "/" << temp->date_of_birth.month << "/"<< temp->date_of_birth.year << "," << temp->social_ID;
//        if (temp != NULL) file << endl;
//    }
//    file.close();
//}
void add_staff(list_staff& lstaff, staff* add)
{
    if (lstaff.head == NULL)
        lstaff.head = lstaff.tail = add;
    else
    {
        lstaff.tail->next = add;
        add->prev = lstaff.tail;
        lstaff.tail = add;
    }
    lstaff.size++;
}
void del_staff(list_staff& lstaff, staff* del)
{
    if (lstaff.head == NULL) return;
    else if (lstaff.head->next == NULL && del == lstaff.head)// DS co 1 phan tu
    {
        staff* temp = lstaff.head;
        delete temp;
        lstaff.size--;
        lstaff.head = lstaff.tail = NULL;
        return;
    }
    else if (lstaff.head == del)// xoa dau
    {
        staff* temp = lstaff.head;
        lstaff.head = temp->next;
        delete temp;
        lstaff.size--;
        lstaff.head->prev = NULL;
        return;
    }
    else if (lstaff.tail == del)// xoa cuoi
    {
        staff* temp = lstaff.tail;
        lstaff.tail = temp->prev;
        delete temp;
        lstaff.size--;
        lstaff.tail->next = NULL;
        return;
    }
    else// xoa giua
    {
        for (staff* temp = lstaff.head; temp != NULL; temp = temp->next)
        {
            if (temp == del)
            {
                staff* tam = temp;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete tam;
                lstaff.size--;
                return;
            }
        }
    }
}
void add_course(list_course& lcourse, course* add)
{
    if (lcourse.head == NULL)
        lcourse.head = lcourse.tail = add;
    else
    {
        lcourse.tail->next = add;
        add->prev = lcourse.tail;
        lcourse.tail = add;
    }
    lcourse.size++;
}
void del_course(list_course& lcourse, course* del)
{
    if (lcourse.head == NULL) return;
    else if (lcourse.head->next == NULL && del == lcourse.head)// DS co 1 phan tu
    {
        course* temp = lcourse.head;
        delete temp;
        lcourse.size--;
        lcourse.head = lcourse.tail = NULL;
        return;
    }
    else if (lcourse.head == del)// xoa dau
    {
        course* temp = lcourse.head;
        lcourse.head = temp->next;
        delete temp;
        lcourse.size--;
        lcourse.head->prev = NULL;
        return;
    }
    else if (lcourse.tail == del)// xoa cuoi
    {
        course* temp = lcourse.tail;
        lcourse.tail = temp->prev;
        delete temp;
        lcourse.size--;
        lcourse.tail->next = NULL;
        return;
    }
    else// xoa giua
    {
        for (course* temp = lcourse.head; temp != NULL; temp = temp->next)
        {
            if (temp == del)
            {
                course* tam = temp;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete tam;
                lcourse.size--;
                return;
            }
        }
    }
}
void add_scoreboard(list_scoreboard& lscoreboard, scoreboard* add)
{
    if (lscoreboard.head == NULL)
        lscoreboard.head = lscoreboard.tail = add;
    else
    {
        lscoreboard.tail->next = add;
        add->prev = lscoreboard.tail;
        lscoreboard.tail = add;
    }
}
string convert_date_to_str(Date date)
{
    string str="";
    if (date.day < 10)
        str += "0";
    str += to_string(date.day) + "/";
    if (date.month < 10)
        str += '0';
    str += to_string(date.month) + '/';
    str += to_string(date.year);
    return str;
}
Date convert_str_to_date(string str)
{
    Date date;
    date.day = stoi(str.substr(0,str.find('/')));
    str.erase(0,str.find('/')+1);
    date.month= stoi(str.substr(0, str.find('/')));
    str.erase(0, str.find('/') + 1);
    date.year = stoi(str);
    return date;
}

bool get_file_student(list_student& lstudent, string path)
{
    ifstream file(path);
    if (file.fail())
    {
        system("cls");
        gotoxy(40, 13);
        perror("Error is: ");
        Sleep(2000);
        return false;
    }
    else
    {
        while (!file.eof())
        {
            student* temp = new student;
            string str;
            getline(file, str, ',');
            if (str == "") return true;
            temp->no = stoi(str);
            getline(file, temp->student_ID, ',');
            getline(file, temp->password, ',');
            getline(file, temp->first_name, ',');
            getline(file, temp->last_name, ',');
            getline(file, temp->gender, ',');
            getline(file, str, ',');
            if (str == "") return true;
            temp->date_of_birth = convert_str_to_date(str);
            getline(file, temp->social_ID, '\n');
            temp->next = temp->prev = NULL;
            add_student(lstudent, temp);
        }
        file.close();
    }
   
    return true;
}
bool get_file_staff(list_staff& lstaff, string path)
{
    ifstream file(path);
    if (file.fail())
    {
        system("cls");
        gotoxy(40, 13);
        cout << "File mo khong thanh cong.";
        Sleep(2000);
        return false;
    }
    else
    {
        while (!file.eof())
        {
            staff* temp = new staff;
            string str;
            getline(file, str, ',');
            if (str == "") return true;
            temp->no = stoi(str);
            getline(file, temp->staff_ID, ',');
            getline(file, temp->password, ',');
            getline(file, temp->first_name, ',');
            getline(file, temp->last_name, ',');
            getline(file, temp->gender, ',');
            getline(file, str, ',');
            if (str == "") return true;
            temp->date_of_birth = convert_str_to_date(str);
            getline(file, temp->social_ID, '\n');
            temp->next = temp->prev = NULL;
            add_staff(lstaff, temp);
        }
        file.close();
    }
   
    return true;
    
}
bool get_file_course(list_course& lcourse, string path, string& length_of_course)
{
    ifstream file(path);
    if (file.fail())
    {
        return false;
    }
    else
    {
        getline(file, length_of_course);
        while (!file.eof())
        {
            course* temp = new course;
            string str;
            getline(file, temp->course_id, ',');
            getline(file, temp->course_name, ',');
            getline(file, temp->class_name, ',');
            getline(file, temp->teacher_name, ',');
            getline(file, str, ',');
            if (str == "")
                return true;
            temp->number_of_credit = stoi(str);
            getline(file, str, ',');
            if (str == "")
                return true;
            temp->max_number = stoi(str);
            getline(file, str, ',');
            if (str == "")
                return true;
            temp->number_of_enroller = stoi(str);
            getline(file, temp->week_day, ',');
            getline(file, temp->session, '\n');
            temp->next = temp->prev = NULL;
            add_course(lcourse, temp);
        }
        file.close();
    }
    
    return true;
}
bool save_student_to_file(list_student lstudent, string path)
{
    ofstream file;
    file.open(path);
    if (file.fail())
    {
        system("cls");
        gotoxy(40, 13);
        perror("error is: ");
        Sleep(2000);
        return false;
    }
    else
    {

        for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
        {
            file << temp->no << "," << temp->student_ID << "," << temp->password << "," << temp->first_name << "," << temp->last_name << ","
                << temp->gender << "," << convert_date_to_str(temp->date_of_birth) << "," << temp->social_ID;
            if (temp != NULL) file << endl;
        }
        file.close();
    }
    
    return true;
}
bool update_student_to_file(list_student lstudent, string path)
{
    list_student lstudent1;
    init_list_student(lstudent1);
    bool check = false;
    if (get_file_student(lstudent1, path))
        check = true;
    ofstream file;
    file.open(path, ios::app);
    if (file.fail())
        return false;
    else
    {
        if (check)
            for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
            {
                bool ks = true;
                for (student* temp1 = lstudent1.head; temp1 != NULL; temp1 = temp1->next)
                    if (temp1->student_ID == temp->student_ID)
                    {
                        ks = false;
                        break;
                    }
                if(ks)
                {
                  file << temp->no << "," << temp->student_ID << "," << temp->password << "," << temp->first_name << "," << temp->last_name << ","
                            << temp->gender << "," << convert_date_to_str(temp->date_of_birth) << "," << temp->social_ID;
                  if (temp != NULL) file << endl;
                }
            }
        else
            for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
            {
                file << temp->no << "," << temp->student_ID << "," << temp->password << "," << temp->first_name << "," << temp->last_name << ","
                    << temp->gender << "," << convert_date_to_str(temp->date_of_birth) << "," << temp->social_ID;
                if (temp != NULL) file << endl;
            }
        file.close();
    }
    
    return true;
}
bool update_course_to_file(list_course lcourse, string path, string duration)
{
    list_course lcourse1;
    init_list_course(lcourse1);
    bool check = false;
    if (get_file_course(lcourse1, path, duration))
        check = true;
    ofstream file;
    file.open(path, ios::app);
    if (file.fail())
        return false;
    else
    {
        if (check)
        {
            for (course* temp = lcourse.head; temp != NULL; temp = temp->next)
            {
                bool ks = true;
                for (course* temp1 = lcourse1.head; temp1 != NULL; temp1 = temp1->next)
                    if (temp->course_id == temp1->course_id)
                    {
                        ks = false;
                        break;
                    }
                if (ks)
                {
                    file << temp->course_id << "," << temp->course_name << "," << temp->class_name << "," << temp->teacher_name << "," << temp->number_of_credit << "," << temp->max_number << ","
                        << temp->number_of_enroller << "," << temp->week_day << "," << temp->session;
                    if (temp != NULL) file << endl;
                }
            }
        }
        else
        {
            file << duration << endl;
            for (course* temp = lcourse.head; temp != NULL; temp = temp->next)
            {
                file << temp->course_id << "," << temp->course_name << "," << temp->class_name << "," << temp->teacher_name << "," << temp->number_of_credit << "," << temp->max_number << ","
                    << temp->number_of_enroller << "," << temp->week_day << "," << temp->session;
                if (temp != NULL) file << endl;
            }
        }
        file.close();
    }
   
    return true;
}
bool save_staff_to_file(list_staff lstaff, string path)
{
    ofstream file(path);
    if (file.fail())
    {
        system("cls");
        gotoxy(40, 13);
        cout << "File mo khong thanh cong.";
        Sleep(2000);
        return false;
    }
    else
    {
        for (staff* temp = lstaff.head; temp != NULL; temp = temp->next)
        {
            file << temp->no << "," << temp->staff_ID << "," << temp->password << "," << temp->first_name << "," << temp->last_name << ","
                << temp->gender << "," << convert_date_to_str(temp->date_of_birth) << "," << temp->social_ID;
            if (temp != NULL) file << endl;
        }
        file.close();
    }
   
    return true;
}
bool save_course_to_file(list_course lcourse, string path, string duration)
{
    ofstream file(path);
    if (file.fail())
    {
        system("cls");
        gotoxy(40, 13);
        cout << "File mo khong thanh cong.";
        Sleep(2000);
        return false;
    }
    else
    {
        file << duration << endl;
        for (course* temp = lcourse.head; temp != NULL; temp = temp->next)
        {
            file << temp->course_id << "," << temp->course_name << "," << temp->class_name << "," << temp->teacher_name << "," << temp->number_of_credit << "," << temp->max_number << ","
                << temp->number_of_enroller << "," << temp->week_day << "," << temp->session;
            if (temp != NULL) file << endl;
        }
        file.close();
    }
   
    return true;
}
void display_student(list_student lstudent)
{
    int pos = 8;
    system("cls");
    drawbox(20, 5, 83, 2);
    gotoxy(21, 6);
    cout << " No |";
    gotoxy(28, 6);
    cout << "  MSSV   |";
    gotoxy(38, 6);
    cout << "      Full name       |";
    gotoxy(62, 6);
    cout << " Gender  |";
    gotoxy(73, 6);
    cout << " Date of birth |";
    gotoxy(90, 6);
    cout << "  Social ID  ";
    for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
    {
        gotoxy(21, pos);
        cout << temp->no;
        gotoxy(28, pos);
        cout << temp->student_ID;
        gotoxy(40, pos);
        cout << temp->first_name << " " << temp->last_name;
        gotoxy(64, pos);
        cout << temp->gender;
        gotoxy(75, pos);
        cout << convert_date_to_str(temp->date_of_birth);
        gotoxy(92, pos++);
        cout << temp->social_ID;
    }
    gotoxy(0, pos + 2);
}
void display_course(list_course lcourse)
{
    int pos = 8;
    drawbox(2, 5, 115, 2);
    gotoxy(3, 6);
    cout << "   Id   |";
    gotoxy(13, 6);
    cout << "      Course name     |";
    gotoxy(37, 6);
    cout << "  Class  |";
    gotoxy(48, 6);
    cout << "   Teacher name   |";
    gotoxy(68, 6);
    cout << "Credit|";
    gotoxy(76, 6);
    cout << "Max num|";
    gotoxy(85, 6);
    cout << "Enrollers|";
    gotoxy(96, 6);
    cout << "   Day   |";
    gotoxy(106, 6);
    cout << "Session";
    for (course* temp = lcourse.head; temp != NULL; temp = temp->next)
    {
        gotoxy(3, pos);
        cout << temp->course_id;
        gotoxy(13, pos);
        cout << temp->course_name;
        gotoxy(37, pos);
        cout << temp->class_name;
        gotoxy(48, pos);
        cout << temp->teacher_name;
        gotoxy(68, pos);
        cout << temp->number_of_credit;
        gotoxy(76, pos);
        cout << temp->max_number;
        gotoxy(85, pos);
        cout << temp->number_of_enroller;
        gotoxy(96, pos);
        cout << temp->week_day;
        gotoxy(106, pos++);
        cout << temp->session;
    }
    gotoxy(0, pos + 2);
}
void courses_of_each_student(list_student lstudent, string path, list_course course, string duration)
{
    path = "../academic_years/courseforstudent";
    for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
    {
        update_course_to_file(course, path + "/" + temp->student_ID + ".csv", duration);
    }
}
bool check_day_of_birth(Date date)
{
    if (date.month < 1 || date.month>12 || date.year < 1 )
        return false;
    bool nhuan = false;
    int max;
    if (date.year % 400 == 0 || (date.year % 4 == 0 && date.year % 100 != 0))
        nhuan = true;
    switch (date.month)
    {
    case 1:case 3: case 5: case 7: case 8: case 10: case 12:
        max = 31;
        break;
    case 2:
        if (nhuan)
            max = 29;
        else
            max = 28;
        break;
    case 4: case 6: case 9: case 11:
        max = 30;
        break;
    }
    if (date.day<1 || date.day>max)
        return false;
    return true;
}
void update_course_for_each_student(string courseID, string path, course* crs)
{
    list_student lstudent;
    init_list_student(lstudent);
    get_file_student(lstudent, path+"/"+courseID+".csv");
    for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
    {
        list_course lcourse;
        init_list_course(lcourse);
        string duration;
        if (get_file_course(lcourse, "../academic_years/courseforstudent/" + temp->student_ID + ".csv", duration))
        {
            for (course* tam = lcourse.head; tam != NULL; tam = tam->next)
            {
                if (tam->course_id == courseID)
                {
                    *tam = *crs;
                    save_course_to_file(lcourse, "../academic_years/courseforstudent/" + temp->student_ID + ".csv", duration);
                    break;
                }
            }
        }
    }
}
void delete_course_for_each_student(string courseID, string path)
{
    list_student lstudent;
    init_list_student(lstudent);
    get_file_student(lstudent, path + "/" + courseID + ".csv");
    for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
    {
        list_course lcourse;
        init_list_course(lcourse);
        string duration;
        if (get_file_course(lcourse, "../academic_years/courseforstudent/" + temp->student_ID + ".csv", duration))
        {
            for (course* tam = lcourse.head; tam != NULL; tam = tam->next)
            {
                if (tam->course_id == courseID)
                {
                    del_course(lcourse, tam);
                    save_course_to_file(lcourse, "../academic_years/courseforstudent/" + temp->student_ID + ".csv", duration);
                    break;
                }
            }
        }
    }
}
void display_scoreboard_of_a_course(list_scoreboard lscoreboard)
{
    int pos = 8;
    drawbox(15, 5, 95, 2);
    gotoxy(16, 6);
    cout << "  No  |";
    gotoxy(24, 6);
    cout << "  Student ID  |";
    gotoxy(40, 6);
    cout << "      Full name      |";
    gotoxy(63, 6);
    cout << "Midterm mark|";
    gotoxy(77, 6);
    cout << "Final mark|";
    gotoxy(89, 6);
    cout << "Total mark|";
    gotoxy(100, 6);
    cout << " Other mark";
    for (scoreboard* temp = lscoreboard.head; temp != NULL; temp = temp->next)
    {
        gotoxy(16, pos);
        cout << temp->no;
        gotoxy(26, pos);
        cout << temp->student_id;
        gotoxy(42, pos);
        cout << temp->student_full_name;
        gotoxy(65, pos);
        cout << temp->midterm_mark;
        gotoxy(79, pos);
        cout << temp->final_mark;
        gotoxy(91, pos);
        cout << temp->total_mark;
        gotoxy(102, pos++);
        cout << temp->other_mark;
    }
    gotoxy(0, pos + 2);
}
bool get_file_scoreboard_of_a_course(string path, list_scoreboard& lscoreboard)
{
    string no, studentID, name, ttmark, fnmark, midmark, other;
    ifstream file(path);
    if (file.fail())
    {
        system("cls");
        gotoxy(40, 13);
        perror("Error is: ");
        Sleep(2000);
        return false;
    }
    else
    {
        getline(file, no, ',');
        getline(file, studentID, ',');
        getline(file, name, ',');
        getline(file, midmark, ',');
        getline(file, fnmark, ',');
        getline(file, ttmark, ',');
        getline(file, other, '\n');
        while (!file.eof())
        {
            scoreboard* temp = new scoreboard;
            string str;
            getline(file, str, ',');
            if (str == "") return true;
            temp->no = stoi(str);
            getline(file, temp->student_id, ',');
            getline(file, temp->student_full_name, ',');
            getline(file, str, ',');
            temp->midterm_mark = stof(str);
            getline(file, str, ',');
            temp->final_mark = stof(str);
            getline(file, str, ',');
            temp->total_mark = stof(str);
            getline(file, temp->other_mark, '\n');
            temp->next = temp->prev = NULL;
            add_scoreboard(lscoreboard, temp);
        }
        file.close();
    }
    return true;
}
bool save_file_scoreboard(string path, list_scoreboard lscoreboard)
{
    ofstream file;
    file.open(path);
    if (file.fail())
    {
        system("cls");
        gotoxy(40, 13);
        perror("error is: ");
        Sleep(2000);
        return false;
    }
    else
    {
        file << "No" << "," << "Student ID" << "," << "Student full name" << "," << "Midterm mark" << "," << "Final mark" << "," << "Total mark" << "," << "Other mark" << endl;
        for (scoreboard* temp = lscoreboard.head; temp != NULL; temp = temp->next)
        {
            file << temp->no << "," << temp->student_id << "," << temp->student_full_name << "," 
                << temp->midterm_mark << "," << temp->final_mark << "," << temp->total_mark  << "," << temp->other_mark;
            if (temp != NULL) file << endl;
        }
        file.close();
    }
    return true;
}
void enter_scoreboard(scoreboard* temp)
{
    int pos = 8;
    drawbox(15, 5, 95, 2);
    gotoxy(16, 6);
    cout << "  No  |";
    gotoxy(24, 6);
    cout << "  Student ID  |";
    gotoxy(40, 6);
    cout << "    Full name    |";
    gotoxy(63, 6);
    cout << "Midterm mark|";
    gotoxy(77, 6);
    cout << "Final mark|";
    gotoxy(89, 6);
    cout << "Total mark|";
    gotoxy(100, 6);
    cout << " Other mark";

    string str;
    gotoxy(16, pos);
    cout << temp->no;
    gotoxy(26, pos);
    cout << temp->student_id;
    gotoxy(42, pos);
    cout << temp->student_full_name;
    gotoxy(65, pos);
    getline(cin, str);
    temp->midterm_mark = stof(str);
    gotoxy(79, pos);
    getline(cin, str);
    temp->final_mark = stof(str);
    gotoxy(91, pos);
    getline(cin, str);
    temp->total_mark = stof(str);
    gotoxy(102, pos);
    getline(cin, temp->other_mark);
}
bool update_scoreboard_to_file(scoreboard* temp, string path,course* course)
{
    ofstream file;
    file.open(path, ios::app);
    if (file.fail())
        return false;
    else
    {
        file << course->course_id << "," << course->course_name << "," << temp->midterm_mark << "," << temp->final_mark << "," << temp->total_mark << "," << temp->other_mark << endl;
        file.close();
        return true;
    }
}
void scoreboard_of_each_student(list_scoreboard lscoreboard,course* course)
{
    string path = "../academic_years/courseforstudent/";
    for (scoreboard* temp = lscoreboard.head; temp != NULL; temp = temp->next)
    {
        update_scoreboard_to_file(temp, path + temp->student_id + "_scoreboard.csv", course);
    }
}
bool update_scoreboard_for_a_student(string path, scoreboard* score, string courseID)
{
    list_course lcourse;
    init_list_course(lcourse);
    list_scoreboard lscoreboard;
    init_list_scoreboard(lscoreboard);
    ifstream file(path);
    if (file.fail())
        return false;
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
    ofstream file1(path);
    if (file1.is_open())
    {
        course* temp = lcourse.head;
        scoreboard* tam = lscoreboard.head;
        while (tam != NULL && temp != NULL)
        {
            if (temp->course_id == courseID)
            {
                *tam = *score;
                break;
            }
            temp = temp->next;
            tam = tam->next;
        }
        temp = lcourse.head;
        tam = lscoreboard.head;
        while (tam != NULL && temp != NULL)
        {
            file1 << temp->course_id << "," << temp->course_name << ","
                << tam->midterm_mark << "," << tam->final_mark << "," << tam->total_mark << "," << tam->other_mark;
            if (temp != NULL && tam!=NULL) file1 << endl;
            temp = temp->next;
            tam = tam->next;
        }
        file1.close();
    }
    return true;
}
void display_scoreboard_of_a_class(list_student lstudent)
{
    system("cls");
    int pos = 8;
    float overall_GDP = 0;
    for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
    {
        float GDP = 0;
        int sl = 0;
        list_course lcourse;
        init_list_course(lcourse);
        list_scoreboard lscoreboard;
        init_list_scoreboard(lscoreboard);
        ifstream file("../academic_years/courseforstudent/"+temp->student_ID+ "_scoreboard.csv");
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
                sl++;
                GDP += sco->total_mark;
            }
            file.close();
            GDP /= sl;
        }
        overall_GDP += GDP;
        drawbox(2, 5, 115, 2);
        gotoxy(3, 6);
        cout << " No|";
        gotoxy(8, 6);
        cout << " Student ID|";
        gotoxy(20, 6);
        cout << "      Full name      |";
        gotoxy(43, 6);
        cout << "  Course ID |";
        gotoxy(57, 6);
        cout << "     Cousre name    |";
        gotoxy(79, 6);
        cout << "Midterm |";
        gotoxy(89, 6);
        cout << "Final |";
        gotoxy(97, 6);
        cout << "Total |";
        gotoxy(105, 6);
        cout << "Other |";
        gotoxy(112, 6);
        cout << "GDP ";
        course* temp1 = lcourse.head;
        scoreboard* tam = lscoreboard.head;
        gotoxy(4, pos);
        cout << temp->no;
        gotoxy(9, pos);
        cout << temp->student_ID;
        gotoxy(21, pos);
        cout << temp->first_name + " " + temp->last_name;
        while (tam != NULL && temp1 != NULL)
        {
            gotoxy(44, pos);
            cout << temp1->course_id;
            gotoxy(58, pos);
            cout << temp1->course_name;
            gotoxy(80, pos);
            cout << tam->midterm_mark;
            gotoxy(90, pos);
            cout << tam->final_mark;
            gotoxy(98, pos);
            cout << tam->total_mark;
            gotoxy(106, pos++);
            cout << tam->other_mark;
            temp1 = temp1->next;
            tam = tam->next;
        }
        gotoxy(113, pos++);
        cout << GDP;
    }
    overall_GDP /= lstudent.size;
    gotoxy(113, pos++);
    cout << "------";
    gotoxy(113, pos++);
    cout << overall_GDP;
    gotoxy(0, pos + 2);
}