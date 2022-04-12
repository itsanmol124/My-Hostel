/**
 * This is a simple console application to help hostel administration to manage
 * their student records.
 * Date of Creation : August 2021
 *
 *
 **/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "functions.h"

typedef struct Student STU;
FILE *stu_file, *id_file;

void wlc_txt();                            // welcome message
void reg_stu();                            // register a new student
void show_stu();                           // prints the list of all student admitted with all information
void search();                             // search for student
void search_name(char name[]);             // search student by name
void search_room(int room_id);             // search student by room number
void stu_access();                         // prints the list of student name and their contact details
void update();                             // update the detail of students
void update_id(int id);                    // updates the detail of student with id id
void del();                                // deletes the student information
void del_id(int id);                       //
void ask();                                // ask queries
void sort();                               // sort the student data according to student name
void read_file1(STU *s, int *size);        // read student data file and store student information to s and number of students to size
int read_id();                             // read file containing id and update file with id+1
void write_file1(STU s[], int size);       // write the data file with new list of student s
void print_list(STU students[], int size); // prints all the list of students in students
void print_student(STU s);                 // prints the complete details of a single student s
void restoqueries(int x);

void greet(); // greeting
void login(); // login portal

int main()
{
    system("color 1f");     // change background color to blue and foreground to bright white
    fullscreen();           // activate fullscreen mode
    greet();
}

void wlc_txt()
{
    // greet message
    char g_mes1[] = "WELCOME TO MY HOSTEL";
    char g_mes2[] = "HOSTEL STUDENTS RECORD MANAGEMENT SYSTEM";

    gotoxy(x_cor, 5);
    int len1 = strlen(g_mes1), len2 = strlen(g_mes2), x = 80;

    printf("+");
    h_border(x, '-');
    chline();

    printf("|%*s%*s|", (x + len1) / 2, g_mes1, (x - len1) / 2, "");
    chline();

    printf("+");
    h_border(x, '-');
    chline();

    printf("|%*s%*s|", (x + len2) / 2, g_mes2, (x - len2) / 2, "");
    chline();

    printf("+");
    h_border(x, '-');
    chline();
}

void main_menu()
{
    // all stuff for main menu
    int x = 82;
    char menu[] = "  MAIN MENU  ";
    chline();
    h_line(x, '-');
    chline();
    h_line((x - strlen(menu)) / 2, '-');
    printf("%s", menu);
    h_line((x - strlen(menu)) / 2 + 1, '-');
    chline();
    h_line(x, '-');
    chnline(2);

    // get current time and print it
    time(&now);
    printf("%s", ctime(&now));
    chline();
}

void greet()
{
    wlc_txt();
    login();
}

void login()
{
    wlc_txt();
    static int count = 0;
    char pword[] = "pass";
    char pass[4];
    int i=0;
    char c;

    // prints hello only once
    if (!count)
    {
        chline();
        printf("Hello!\n");
    }
    chline();
    if (count == 0)
        printf("Enter password to login: ");
    else
    {
        printf("Incorrect password.");
        chnline(2);
        printf("Please enter password again: ");
    }

    while(i<4)
	{
	    pass[i]=getch();
	    c=pass[i];
	    printf("*");
	    i++;
	}
	pass[i]='\0';
	count = 1;

    // correct password leads to successful login
    if (strcmp(pass,pword) == 0)
    {
        system("cls");
        gotoxy(x_cor, 5);
        printf("Successfully logged in..\n");
        ask();
    }
    else
    {
        system("cls");
        Beep(600, 500);
        gotoxy(x_cor, 5);
        login();    // incorrect password make recursive call to login function
    }

}

void ask()
{
    static int count = 0;

    /**
     * this will be printed each time a query gets completed
     * and doesn't print for the first time after login
     **/
    if (count)
    {
        chnline(1);
        fflush(stdin);
        printf("Press any key to go to main menu.");
        getch();
        fflush(stdin);
        system("cls");
    }
    wlc_txt();
    main_menu();
    chline();
    chline();
    count++;

    // prints the possible request admin can do
    printf("1. Student Registration\n");
    chline();
    printf("2. View All Students Details\n");
    chline();
    printf("3. Search Student Details\n");
    chline();
    printf("4. Student Access\n");
    chline();
    printf("5. Update Student Details\n");
    chline();
    printf("6. Delete Student Details\n");
    chline();
    printf("7. Exit\n\n");
    chline();
    printf("Select Option: ");
    int x;
    scanf("%d", &x);
    restoqueries(x);
}

void restoqueries(int x)
{
    system("cls");
    gotoxy(x_cor, 5);
    switch (x)
    {
    case 1:
        reg_stu();
        break;
    case 2:
        show_stu();
        break;
    case 3:
        search();
        break;
    case 4:
        stu_access();
        break;
    case 5:
        update();
        break;
    case 6:
        del();
        break;
    case 7:
        printf("\n\t***Thank You For Using My Hostel***\n");
        exit(1);
    }
    ask();
}

// register a new student
void reg_stu()
{
    STU stu;
    int id = read_id();
    gotoxy(x_cor, 5);
    printf("Id of student: %d", id);

    chnline(2);
    fflush(stdin);
    printf("Enter Student's Name: ");
    gets(stu.name);
    ucase(stu.name);        // upper case all the alphabet in the name

    chline();
    printf("Enter Student's Mobile number: ");
    gets(stu.number);

    chline();
    printf("Enter Student's School: ");
    gets(stu.inst);

    chline();
    printf("Enter Student's Guardian Name: ");
    gets(stu.guardian_name);

    chline();
    printf("Enter Student's Guardian Mobile Number: ");
    gets(stu.guardian_no);

    chline();
    printf("Enter the room allocated to the student: ");
    scanf("%d", &stu.room_no);
    chnline(3);

    printf("Student Successfully registered.");
    chline();

    stu.stu_no = id;

    // get current time and store to the date of enrollment of student
    time(&now);
    strcpy(stu.date, ctime(&now));

    // last char of return of ctime is \n so replaced it with \0.
    // if not changed printing date will create a new line
    stu.date[strlen(stu.date) - 1] = '\0';

    // print the details of student added.
    print_student(stu);

    // append this new data to the end of file.
    stu_file = fopen("data.bin", "a");
    encrypt(&stu);
    fwrite(&stu, sizeof(STU), 1, stu_file);
    fclose(stu_file);

    // sort the data in file according to the name
    sort();
}

void show_stu()
{
    STU s[1000];
    int size = 0;
    read_file1(s, &size);
    // if size == 0 the print the message and return
    if (!size){
        printf("Sorry! No Student has been registered yet.");
        return;
    }
    // otherwise print the list of student s
    print_list(s, size);
}

void search()
{
    // asks for some info and search the student
    char name[20];
    fflush(stdin);
    chline();
    printf("Do you want to search student by:");
    chline();
    printf("1. Name");
    chline();
    printf("2. Room Number");
    chnline(2);
    printf("Enter your option (1 or 2): ");
    char x;
    scanf(" %c", &x);
    fflush(stdin);
    chnline(1);
    if (x == '1')               // search by name if 1 is selected.
    {
        fflush(stdin);
        chline();
        printf("Enter the Student Name: ");
        gets(name);
        ucase(name);
        search_name(name);
    }
    else if (x == '2')          // search by room if 2 is selected.
    {
        int room;
        chline();
        printf("Enter Room Number: ");
        scanf("%d", &room);
        search_room(room);
    }
    chline();
}

void search_name(char name[])
{
    STU temp[1000], found[1000];
    int size = 0, count_found = 0;
    read_file1(temp, &size);
    for (int i = 0; i < size; i++)
    {
        // checks if name is substring of temp[i].name  and add to new array.
        if (issubstring(name, temp[i].name))
        {
            found[count_found++] = temp[i];
        }
    }
    if (!count_found)           // if no student found then print message and return
    {
        chline();
        printf("Sorry! No Student found with name %s.", name);
        chline();
        return;
    }
    // prints the new array with students
    print_list(found, count_found);
}

void search_room(int room)
{
    STU temp[1000], found[1000];
    int size = 0, count_found = 0;
    read_file1(temp, &size);
    for (int i = 0; i < size; i++)
    {
        if (temp[i].room_no == room)        // checks room number of each student and add to new array.
        {
            found[count_found++] = temp[i];
        }
    }
    if (!count_found)
    {
        chline();
        printf("Sorry! No Student found for the Room No %d.", room);
        chline();
        return;
    }
    print_list(found, count_found);
}

void stu_access()
{
    STU temp[1000];
    int size = 0;

    // print all
    read_file1(temp, &size);
    t_row1();
    printf("|%-20s |%15s |", "Name", "Mobile No.");
    chline();
    t_row1();
    t_row1();
    for (int i = 0; i < size; i++)
    {
        printf("|%-20s |%15s |", temp[i].name, temp[i].number);
        chline();
        t_row1();
    }
}

void update()
{

    printf("Do you know the Id(or Form no.) of Student(y): ");
    char response;
    fflush(stdin);
    response = getche();

    if (response != 'y' && response != 'Y')
    {
        char name[20];
        chnline(2);
        printf("Enter the Name of Student: ");
        fflush(stdin);
        gets(name);
        fflush(stdin);
        ucase(name);
        search_name(name);
    }
    int id;

    chnline(2);
    printf("Enter the Id number: ");
    scanf("%d", &id);
    update_id(id);
}

void update_id(int id)
{

    STU temp[1000];
    int size = 0, ind = -1;

    read_file1(temp, &size);
    for (int i = 0; i < size; i++)
    {
        if (temp[i].stu_no == id)
        {
            ind = i;
            break;
        }
    }

    if (ind == -1)
    {
        chline();
        printf("Sorry! No Student found with Id %d", id);
        chline();
        return;
    }

    STU new;
    new.stu_no = temp[ind].stu_no;
    strcpy(new.date, temp[ind].date);
    char x;
    chline();
    printf("Enter (y or Y) if you want to update each.");
    chline();
    fflush(stdin);
    printf("Name (y/n): ");
    x = getche();
    chline();
    if (x == 'y' || x == 'Y')
    {
        chline();
        fflush(stdin);
        printf("Enter New Name: ");
        gets(new.name);
        fflush(stdin);
        ucase(new.name);
    }
    else
        strcpy(new.name, temp[ind].name);

    chline();
    printf("Number (y/n): ");
    x = getche();
    chline();
    if (x == 'y' || x == 'Y')
    {
        chline();
        fflush(stdin);
        printf("Enter New Number: ");
        gets(new.number);
        fflush(stdin);
    }
    else
        strcpy(new.number, temp[ind].number);

    chline();
    printf("School/College (y/n): ");
    x = getche();
    chline();
    if (x == 'y' || x == 'Y')
    {
        chline();
        fflush(stdin);
        printf("Enter New School/College Name: ");
        gets(new.inst);
        fflush(stdin);
    }
    else
        strcpy(new.inst, temp[ind].inst);

    chline();
    printf("Guardian Name (y/n): ");
    x = getche();
    chline();
    if (x == 'y' || x == 'Y')
    {
        chline();
        fflush(stdin);
        printf("Enter New Guardian Name: ");
        gets(new.guardian_name);
        fflush(stdin);
    }
    else
        strcpy(new.guardian_name, temp[ind].guardian_name);

    chline();
    printf("Guardian Number (y/n): ");
    x = getche();
    chline();
    if (x == 'y' || x == 'Y')
    {
        chline();
        fflush(stdin);
        printf("Enter New Guardian Number: ");
        gets(new.guardian_no);
        fflush(stdin);
    }
    else
        strcpy(new.guardian_no, temp[ind].guardian_no);

    chline();
    printf("Room (y/n): ");
    x = getche();
    fflush(stdin);
    chline();
    if (x == 'y' || x == 'Y')
    {
        chline();
        fflush(stdin);
        printf("Enter New Room Number: ");
        scanf("%d", &new.room_no);
        fflush(stdin);
    }
    else
        new.room_no = temp[ind].room_no;
    system("cls");
    gotoxy(x_cor, 5);
    printf("Details updated.");
    chnline(2);
    printf("Old Details of Student:");
    print_student(temp[ind]);
    temp[ind] = new;

    chnline(1);
    printf("New Details of Student:");
    print_student(temp[ind]);
    write_file1(temp, size);
    sort();
}

void del()
{

    printf("Do you know the Id(or form no.) of Student(y): ");
    char response;
    fflush(stdin);
    response = getche();
    chnline(2);

    if (response != 'y' && response != 'Y')
    {
        char name[20];
        printf("Enter the Name of Student: ");
        fflush(stdin);
        gets(name);
        ucase(name);
        search_name(name);
    }
    int id;
    chline();
    printf("Enter the Id number: ");
    scanf("%d", &id);
    chline();
    del_id(id);
}

void del_id(int id)
{
    STU s[1000], newlist[1000];
    int size = 0, found = 0, count = 0;

    read_file1(s, &size);
    for (int i = 0; i < size; i++)
    {
        if (s[i].stu_no == id && !found)
        {
            found = 1;
            printf("Student Successfully Deleted.");
            chnline(2);
            print_student(s[i]);
            continue;
        }
        newlist[count++] = s[i];
    }
    if (!found)
    {
        chline();
        printf("Sorry! No Student found with Id %d.\n", id);
        chline();
    }
    write_file1(newlist, count);
}

void print_student(STU s)
{

    chnline(2);
    printf("%-35s %30d\n", "Id/Form number:", s.stu_no);
    chline();
    printf("%-35s %30s\n", "Name:", s.name);
    chline();
    printf("%-35s %30s\n", "Mobile Number:", s.number);
    chline();
    printf("%-35s %30s\n", "School/College Name:", s.inst);
    chline();
    printf("%-35s %30s\n", "Guardian Name:", s.guardian_name);
    chline();
    printf("%-35s %30s\n", "Guardian Number:", s.guardian_no);
    chline();
    printf("%-35s %30s\n", "Date of Enrollment:", s.date);
    chline();
    printf("%-35s %30d\n", "Room Number:", s.room_no);
    chline();
}

void swap(STU *s1, STU *s2)
{
    STU temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

void sort()
{
    STU s[1000];
    int size = 0;

    read_file1(s, &size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j) continue;
            if (strcmp(s[i].name, s[j].name) < 0) swap(&s[i], &s[j]);
        }
    }

    write_file1(s, size);
}

void print_list(STU s[], int size)
{
    chrow();
    table_row();
    //       id   name    mob   school  guarname num dateEnroll roomno
    printf("|%5s |%-20s |%-15s |%-20s |%-20s |%-15s |%-25s |%-9s |", "ID", "Name", "Mobile No.", "School", "Guard.. Name", "Guard.. No.", "Date of enrollment", "Room No.");
    chrow();
    for (int i = 0; i < size; i++)
    {
        table_row();
        printf("|%5d |%-20s |%-15s |%-20s |%-20s |%-15s |%-25s |%-9d |", s[i].stu_no, s[i].name, s[i].number, s[i].inst, s[i].guardian_name, s[i].guardian_no, s[i].date, s[i].room_no);
        chrow();
    }
    table_row();
}

void read_file1(STU *s, int *size)
{
    stu_file = fopen("data.bin", "r");

    STU temp;
    *size = 0;
    while (fread(&temp, sizeof(STU), 1, stu_file))
    {

        if (feof(stu_file)) break;
        dencrypt(&temp);
        *(s + *size) = temp;
        (*size)++;
    }
    fclose(stu_file);
}

int read_id()
{
    int id = 1;
    id_file = fopen("count.bin", "r");

    if (id_file == NULL)
    {
        // if file is not created then initialize is with 1 and sotre in file
        id = 1;
        id_file = fopen("count.bin", "w");
        fwrite(&id, sizeof(int), 1, id_file);
        fclose(id_file);
    }
    else    // if the file is already created and there will be form no./id
    {       // we will update id and store in the same file and return it too.

        fread(&id, sizeof(int), 1, id_file);
        fclose(id_file);
        id++;
        id_file = fopen("count.bin","w");
        fwrite(&id, sizeof(int), 1, id_file);
        fclose(id_file);
    }
    return id;
}

void write_file1(STU s[], int size)
{
    // write the file with the data in array s[]
    stu_file = fopen("data.bin", "w");
    for (int i = 0; i < size; i++)
    {
        encrypt(&s[i]);
        fwrite(&s[i], sizeof(STU), 1, stu_file);
    }
    fclose(stu_file);
}
