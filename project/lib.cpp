#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <conio.h>
using namespace std;
#define el "\n"
#define sp " "

int res_book(int, int); // To check whether any book a given book no. exists or not
/*Class of books*/
class book
{
protected:
    int bno, quant, shelf; // book no,book quantity,location
    char bname[50];        // book name
    char aname[50];        // book author's name
    char pname[50];        // publication name
public:
    void createb();
    void showb();
    void showlist();
    void assignbno(int x) // book no assigned on the basis of no.
    {                     // no. of objects in file
        bno = 10001;
        bno += x - 1;
    start1:
        bno += 1;
        if (res_book(bno, 0))
            goto start1;
    }
    void set_q()
    {
        quant -= 1;
    }
    int quantity()
    {
        return quant;
    }
    void reset_q()
    {
        quant += 1;
    }
    int retbno()
    {
        return bno;
    }
};
/*End of class book*/

void book::createb() // To enter data in data members of class book
{
    int i;
    cout << "\n\t\tEnter details:\n";
    cout << "\n\t\tEnter Book's Name: ";
    char a[50];
    cin.getline(a,50);
    cin.getline(bname, 50);
    for (i = 0; bname[i] != '\0'; i++)
    {
        if (bname[i] >= 'a' && bname[i] <= 'z')
            bname[i] -= 32;
    }

    cout << "\n\t\tEnter Author's Name: ";
    cin.getline(aname, 50);
    cout << "\n\t\tEnter Publication Name: ";
    cin.getline(pname, 50);
    cout<<"\n\t\tEnter shelf: ";
    cin>>shelf;
    cout << "\n\t\tEnter Book's quantity: ";
    cin >> quant;
}

void book::showb() // To display the details of books
{
    cout << "\n\t\tBook No.: " << bno << el;
    cout << "\n\t\tBook Name: " << bname << el;
    cout << "\n\t\tBook Author Name: " << aname << el;
    cout << "\n\t\tBook Publication: " << pname << el;
    cout<<"\n\t\tShelf Number: "<<shelf<<el;
    cout << "\n\t\tBook Quantity: " << quant << el;
}

void book::showlist() // To display book details in list form
{
    cout << "\n\t" << bno << "\t\t\t" << bname << "\t\t" << aname << "\t\t\t" << quant <<"\t\t"<<shelf<< endl;
}

/*Class of Students*/
class student
{
protected:
    char name[25]; // Student name
    int bno;       // Book no. of book issued
    int token;     // To veirfy book issued or not
public:
    void creates();
    void shows();
    void showlist();
    void settoken(int x) // To set token and assign bno a book no
    {
        bno = x;
        token = 1;
    }
    void resettoken() // To reset token
    {
        bno = 0;
        token = 0;
    }
    int retbno()
    {
        return bno;
    }
    int regno; // Admission No
};
/*End of class Students*/

bool res_student(int);  // To check whether the admission no. already exist or not
void student::creates() // To enter values to all data members of class student
{
plane:
    system("CLS");
    cout << "\n\t\tEnter the details:-\n";
    cout << "\n\t\tEnter student's Registration number : ";
    cin >> regno;
    if (res_student(regno))
    {
        cout << "\n\t\tRecord already exist with this Registration number .";
        cout << "\n\t\tEnter a different Registration number \n";
        system("PAUSE");
        goto plane;
    }
    cout << "\n\t\tEnter student's Name: ";
    char n[50];
    cin.getline(n, 50);
    cin.getline(name, 25);
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] >= 'a' && name[i] <= 'z')
            name[i] -= 32;
    }
    bno = 0;
    token = 0;
}

void student::shows() // Show details of Students
{
    cout << "\n\t\tStudent's Admission No.: " << regno << el;
    cout << "\n\t\tStudent's Name: " << name << el;
    if (token == 1)
    {
        cout << "\n\t\tBook Issued (Book no): " << bno;
    }
}

void student::showlist() // To display Student details in list form
{
    cout << "\n\t" << regno << "\t\t" << name << "\t\t" << bno;
}

/*To Write object of class book in file*/
void add_book()
{
    book bk;
    ofstream outf("book1.txt", ios::app | ios::binary);
    outf.seekp(0, ios::end);
    int x = outf.tellp() / sizeof(book);
    bk.assignbno(x);
    bk.createb();
    bk.showb();
    outf.write( (char *)&bk, sizeof(book));
    cout << "\n\t\tRecord added successfully";
    outf.close();
}

/*To Write object of class student in file*/
void write_student()
{
    student st;
    ofstream outf("student.txt", ios::app | ios::binary);
    outf.seekp(0, ios::end);
    st.creates();
    st.shows();
    outf.write((char *)&st, sizeof(student));
    cout << "\n\t\tRecord added successfully";
    outf.close();
}

/*To display Student records in list form*/
void list_student()
{
    system("CLS");
    student st;
    ifstream intf("student.txt", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        cout << "\n\t*****Students Details*****\n\n";
        cout << "\n\tAdmission No:\tName: \tBook Issued:";
        while (intf.read( (char *)&st, sizeof(student)))
            st.showlist();
    }
    intf.close();
}

/*To display book records in list form*/
void list_book()
{
    book bk;
    ifstream intf("book1.txt", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        cout << "\n\t*****Books Details*****\n\n";
        cout << "\n\tBook No: \t\tName: \t\tAuthor's Name: \t\tQuantity: \t\tShelf no" << endl;
        while (intf.read( (char *)&bk, sizeof(book)))
            bk.showlist();
    }
    intf.close();
}

/*To search for a specific book*/
void search_book(int x)
{
    book bk;
    int cnt = 0;
    ifstream intf("book1.txt", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        while (intf.read( (char *)(&bk), sizeof(book)))
        {
            if (bk.retbno() == x)
            {
                cnt++;
                cout << "\n\t\tFILE FOUND!!!!";
                bk.showb();
                break;
            }
        }
        if (cnt == 0)
            cout << "\n\t\tNo such record exists";
    }
    intf.close();
}

/*To modify the book records*/
void modify_book(int x)
{
    book bk;
    int cnt = 0;
    fstream intf("book1.txt", ios::in | ios::out | ios::ate | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        while (intf.read((char *)&bk, sizeof(book)))
        {
            if (bk.retbno() == x)
            {
                cnt++;
                bk.createb();
                bk.showb();
                intf.seekp(intf.tellp() - sizeof(book));
                intf.write( (char *)&bk, sizeof(book));
                cout << "\n\t\tRecord Updated";
                break;
            }
        }
        if (cnt == 0)
            cout << "\n\t\tNo such record exists";
    }
    intf.close();
}
/*To delete a specific student record*/
void delete_student(int x)
{
    student st;
    int cnt = 0;
    ifstream intf("student.txt", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        ofstream outf("temp.txt", ios::app | ios::binary);
        while (intf.read( (char *)&st, sizeof(student)))
        {
            if (st.regno == x)
                cnt++;
            else
                outf.write( (char *)&st, sizeof(student));
        }
        intf.close();
        outf.close();
        if (cnt == 0)
        {
            remove("temp.txt");
            cout << "\n\t\tNo such record exists";
        }
        else
        {
            remove("student.txt");
            rename("temp.txt", "student.txt");
            cout << "\n\t\tRecord deleted successfully";
        }
    }
}

/*To delete a specific book record*/
void delete_book(int x)
{
    book bk;
    int cnt = 0;
    ifstream intf("book1.txt", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        ofstream outf("temp1.txt", ios::app | ios::binary);
        while (intf.read( (char *)&bk, sizeof(book)))
        {
            if (bk.retbno() == x)
                cnt++;
            else
                outf.write( (char *)&bk, sizeof(book));
        }
        intf.close();
        outf.close();
        if (cnt == 0)
        {
            remove("temp1.txt");
            cout << "\n\t\tNo such record exists";
        }
        else
        {
            remove("book.txt");
            rename("D:temp1.txt", "D:book.txt");
            cout << "\n\t\tRecord deleted successfully";
        }
    }
}

// To search whether a specific student record exists or not
bool res_student(int x)
{
    student st;
    int cnt = 0, f = 0;
    ifstream intf("student.txt", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        f = 1;
    else
    {
        while (intf.read( (char *)&st, sizeof(student)))
        {
            if (st.regno == x)
            {
                cnt++;
                break;
            }
        }
        if (cnt == 0)
            f = 1;
    }
    intf.close();
    if (f)
        return 0;
    else
        return 1;
}

/*To search a specific book and return true or false*/
int res_book(int x, int z)
{
    book bk;
    int cnt = 0, f = 1;
    fstream intf("book1.txt", ios::in | ios::out | ios::ate | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        f = 0;
    else
    {
        while (intf.read( (char *)&bk, sizeof(book)))
        {
            if (bk.retbno() == x)
            {
                cnt++;
                if (z == 1)
                {
                    bk.showb();
                    if (bk.quantity() > 0)
                    {
                        bk.set_q();
                        intf.seekp(intf.tellp() - sizeof(book));
                        intf.write( (char *)&bk, sizeof(book));
                    }
                    else
                        f = 2;
                }
                else if (z == 2)
                {
                    bk.showb();
                    bk.reset_q();
                    intf.seekp(intf.tellp() - sizeof(book));
                    intf.write( (char *)&bk, sizeof(book));
                }
                break;
            }
        }
        if (cnt == 0)
            f = 0;
    }
    intf.close();
    return f;
}

/*To issue books*/
void book_issue()
{
    int sn, bn;
    system("CLS");
    cout << "\n\n\t\t*****BOOK ISSUE******";
    cout << "\n\n\t\tEnter the student's Registration number : ";
    cin >> sn;
    int cnt = 0;
    student st;
    fstream outf("student.txt", ios::in | ios::out | ios::ate | ios::binary);
    outf.seekg(0, ios::beg);
    if (!outf)
        cout << "\n\t\tstudent not found\n";
    else
    {
        while (outf.read( (char *)&st, sizeof(student)))
        {
            if (st.regno == sn)
            {
                cnt++;
                list_book();
                cout << "\n\n\t\tEnter the book no.:";
                cin >> bn;
                cout << "\n";
                int flag = res_book(bn, 1);
                if (flag == 1)
                {
                    st.settoken(bn);
                    outf.seekp(outf.tellp() - sizeof(student));
                    outf.write( (char *)&st, sizeof(student));
                    cout << "\n\t\tBook Issued";
                    cout << "\n\t\tNote: Write the current date in backside of the book";
                    cout << "\n\t\t Should be submitted within 7 days to avoid fine";
                    cout << "\n\t\t The fine is Rs. 10 for each day after 7 days period\n";
                    break;
                }
                else if (flag == 2)
                {
                    cout << "\n\t\tTHE BOOK IS OUT OF STOCK!!!";
                    break;
                }
                else
                {
                    cout << "\n\t\tNo such record exists\n";
                    break;
                }
            }
        }
        if (cnt == 0)
            cout << "\n\t\tNo such record exists\n";
    }
    outf.close();
}

/*To deposit books*/
void book_deposit()
{
    int sn, bn;
    system("CLS");
    cout << "\n\n\t\t*****BOOK DEPOSIT******";
    cout << "\n\n\t\tEnter the student's Registration number : ";
    cin >> sn;
    int cnt = 0;
    student st;
    fstream outf("student.txt", ios::in | ios::out | ios::ate | ios::binary);
    outf.seekg(0, ios::beg);
    if (!outf)
        cout << "\n\t\tFile not found\n";
    else
    {
        while (outf.read( (char *)&st, sizeof(student)))
        {
            if (st.regno == sn)
            {
                cnt++;
                bn = st.retbno();
                bool flag = res_book(bn, 2);
                if (flag)
                {
                    st.resettoken();
                    outf.seekp(outf.tellp() - sizeof(student));
                    outf.write( (char *)&st, sizeof(student));
                    int days;
                    cout << "\n\t\tBook deposited in no. of days:";
                    cin >> days;
                    if (days > 7)
                    {
                        int fine = (days - 7) * 10;
                        cout << "\n\n\t\tFine: Rs." << fine << el;
                    }
                    cout << "\n\t\tBook Deposited Successfully\n";
                    break;
                }
                else
                {
                    cout << "\n\t\tNo such record exists\n";
                    break;
                }
            }
        }
        if (cnt == 0)
            cout << "\n\t\tNo such record exists\n";
    }
    outf.close();
}

/*Function that has features of Admin Menu*/
void admin_menu()
{
fine:
    system("PAUSE");
    system("CLS");

    int opt;
    cout << "\n\n\n\t\t\t******ADMINISTRATOR MENU******";
    cout << "\n\n\t1.\tCREATE STUDENT RECORD";
    cout << "\n\n\t2.\tDISPLAY ALL STUDENTS RECORD";
    cout << "\n\n\t3.\tDELETE STUDENT RECORD";
    cout << "\n\n\t4.\tADD BOOK ";
    cout << "\n\n\t5.\tDISPLAY ALL BOOKS ";
    cout << "\n\n\t6.\tMODIFY BOOK ";
    cout << "\n\n\t7.\tDELETE BOOK ";
    cout << "\n\n\t8.\tBACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Option (1-8) ";
    cin >> opt;
    if (opt == 1)
    {
        system("CLS");
        write_student();
        cout << el;
        goto fine;
    }
    else if (opt == 2)
    {
        system("CLS");
        list_student();
        cout << el;
        goto fine;
    }

    else if (opt == 3)
    {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the Registration number of the student : ";
        cin >> ad;
        delete_student(ad);
        cout << el;
        goto fine;
    }
    else if (opt == 4)
    {
        system("CLS");
        add_book();
        cout << el;
        goto fine;
    }
    else if (opt == 5)
    {
        system("CLS");
        list_book();
        cout << el;
        goto fine;
    }
    else if (opt == 6)
    {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the book no. of the book";
        cin >> ad;
        modify_book(ad);
        cout << el;
        goto fine;
    }
    else if (opt == 7)
    {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the book no. of the book : ";
        cin >> ad;
        delete_book(ad);
        cout << el;
        goto fine;
    }
    else if (opt == 8)
        return;
    else
    {
        cout << "\n\t\tEnter correct option : ";
        cout << el;
        goto fine;
    }
}

/*Checks for correct password*/
// The password if predefined and has to be changed through the source code
// of application
bool passwords()
{
    int i = 0;
    char ch, st[21], ch1[21] = {"0808"};
    cout << "\n\n\t\tEnter Password : ";
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            st[i] = '\0';
            break;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            cout << "\b \b";
        }
        else
        {
            cout << "*";
            st[i] = ch;
            i++;
        }
    }
    for (i = 0; st[i] == ch1[i] && st[i] != '\0' && ch1[i] != '\0'; i++)
        ;
    if (st[i] == '\0' && ch1[i] == '\0')
        return 1;
    else
        return 0;
}

// Main function
int main()
{
    cout << "\n\n\t\t\t*******************************************";
    cout << "\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
    cout << "\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t*******************************************";
    bool a = passwords();
    if (!a)
    {
        for (int i = 0; i < 2; i++)
        {
            cout << "\nWrong password";
            cout << "\nYou have " << 2 - i << "attempts left";
            if (passwords())
                goto last;
            if (i == 1)
            {
                cout << "\n\n\n\t\t\t All attempts failed........";
                cout << "\n\n\t\t\t Sorry, but you can't login";
                exit(0);
            }
        }
    }
last:
    cout << "\n\n";
start:
    system("PAUSE");
    system("CLS");
    int opt;
    cout << "\n\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
    cout << "\n\t\t\t--------------------------------------------";
    cout << "\n\t\t\t1.\tSEARCH BOOK";
    cout << "\n\t\t\t2.\tBOOK ISSUE";
    cout << "\n\t\t\t3.\tBOOK DEPOSIT";
    cout << "\n\t\t\t4.\tADMINISTRATOR MENU";
    cout << "\n\t\t\t5.\tExit";
    cout << "\n\n Enter your option: ";
    cin >> opt;
    if (opt == 1)
    {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the book no. of the book : ";
        cin >> ad;
        search_book(ad);
        cout << el;
        goto start;
    }
    else if (opt == 2)
    {
        system("CLS");
        book_issue();
        goto start;
    }
    else if (opt == 3)
    {
        system("CLS");
        book_deposit();
        goto start;
    }
    else if (opt == 4)
    {
        admin_menu();
        goto start;
    }
    else if (opt == 5)
        exit(0);
    else
    {
        cout << "\n\t\tEnter correct option";
        goto start;
    }
    return 0;
}
