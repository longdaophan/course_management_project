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
        cout << '*';
    for (int i = 0; i < height; i++)
    {
        gotoxy(col + width, row + i);
        cout << '*';
    }
    for (int i = width + col; i > col; i--)
    {
        gotoxy(i, row + height);
        cout << '*';
    }
    for (int i = row + height; i > row; i--)
    {
        gotoxy(col, i);
        cout << '*';
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

void get_file_student(list_student& lstudent)
{
    ifstream file;
    file.open("student.csv");
    if (file.fail())
    {
        cout << "File mo khong thanh cong.";
        return;
    }
    else
        while (!file.eof())
    {
        student* temp = new student;
        file >> temp->no;
        getline(file, temp->student_ID, ',');
        getline(file, temp->first_name, ',');
        getline(file, temp->last_name, ',');
        getline(file, temp->gender, ',');
        string str;
        getline(file, str, ',');
        temp->date_of_birth = convert_str_to_date(str);
        getline(file, temp->social_ID, ',');
        temp->next = temp->prev = NULL;
        add_student(lstudent, temp);
    }
    file.close();
}
void display_student(list_student lstudent)
{
    drawbox(30, 5, 50, 20);
    gotoxy(33, 7);
}
