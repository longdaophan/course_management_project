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
student* enter_infor_for_student()
{
    student* temp = new student;
    string str;
    getline(cin, str);
    temp->no = stoi(str);
    getline(cin, temp->student_ID);
    getline(cin, temp->password);
    getline(cin, temp->first_name);
    getline(cin, temp->last_name);
    getline(cin, temp->gender);
    getline(cin, str);
    temp->date_of_birth = convert_str_to_date(str);
    getline(cin, temp->social_ID);
    temp->next = temp->prev = NULL;
    return temp;
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
        delete temp;
        lstudent.size--;
        lstudent.head->prev = NULL;
        return;
    }
    else if (lstudent.tail == del)// xoa cuoi
    {
        student* temp = lstudent.tail;
        lstudent.tail = temp->prev;
        delete temp;
        lstudent.size--;
        lstudent.tail->next = NULL;
        return;
    }
    else// xoa giua
    {
        for (student* temp = lstudent.tail; temp != NULL; temp = temp->next)
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
        for (staff* temp = lstaff.tail; temp != NULL; temp = temp->next)
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
        for (course* temp = lcourse.tail; temp != NULL; temp = temp->next)
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

void get_file_student(list_student& lstudent, string path)
{
    ifstream file(path);
    if (file.fail())
    {
        cout << "File mo khong thanh cong.";
        system("pause");
        return;
    }
    else
    {
        while (!file.eof())
        {
            student* temp = new student;
            string str;
            getline(file, str, ',');
            if (str == "") return;
            temp->no = stoi(str);
            getline(file, temp->student_ID, ',');
            getline(file, temp->password, ',');
            getline(file, temp->first_name, ',');
            getline(file, temp->last_name, ',');
            getline(file, temp->gender, ',');
            getline(file, str, ',');
            if (str == "") return;
            temp->date_of_birth = convert_str_to_date(str);
            getline(file, temp->social_ID, '\n');
            temp->next = temp->prev = NULL;
            add_student(lstudent, temp);
        }
    }
    file.close();
}
void get_file_staff(list_staff& lstaff, string path)
{
    ifstream file(path);
    if (file.fail())
    {
        cout << "File mo khong thanh cong.";
        return;
    }
    else
        while (!file.eof())
        {
            staff* temp = new staff;
            string str;
            getline(file, str, ',');
            if (str == "") return;
            temp->no = stoi(str);
            getline(file, temp->staff_ID, ',');
            getline(file, temp->password, ',');
            getline(file, temp->first_name, ',');
            getline(file, temp->last_name, ',');
            getline(file, temp->gender, ',');
            getline(file, str, ',');
            if (str == "") return;
            temp->date_of_birth = convert_str_to_date(str);
            getline(file, temp->social_ID, '\n');
            temp->next = temp->prev = NULL;
            add_staff(lstaff, temp);
        }
    file.close();
}
void save_student_to_file(list_student lstudent, string path)
{
    ofstream file(path);
    for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
    {
        file << temp->no << "," << temp->student_ID << "," << temp->password << "," << temp->first_name << "," << temp->last_name << ","
            << temp->gender << "," << convert_date_to_str(temp->date_of_birth) << "," << temp->social_ID;
        if (temp != NULL) file << endl;
    }
    file.close();
}
void save_staff_to_file(list_staff lstaff, string path)
{
    ofstream file(path);
    for (staff* temp = lstaff.head; temp != NULL; temp = temp->next)
    {
        file << temp->no << "," << temp->staff_ID << "," << temp->password << "," << temp->first_name << "," << temp->last_name << ","
            << temp->gender << "," << convert_date_to_str(temp->date_of_birth) << "," << temp->social_ID;
        if (temp != NULL) file << endl;
    }
    file.close();
}
void display_student(list_student lstudent)
{
    /*drawbox(30, 5, 50, 20);
    gotoxy(33, 7);*/
    for (student* temp = lstudent.head; temp != NULL; temp = temp->next)
    {
        cout << temp->no << " " << temp->student_ID <<" "<<temp->password << " " << temp->first_name << " " << temp->last_name << " " 
            << temp->gender << " " << convert_date_to_str(temp->date_of_birth) << " " << temp->social_ID << endl;
    }
}
