// null
#include <iostream>
#include <vector>
#include <sqlite3.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <openssl/sha.h>

// install from https://www.openssl.org/source/
//  #include <openssl/evp.h>

using namespace std;
string getInterest()
{
    string hobies[] = {"basketball", "volleyball", "football", "swimming", "running", "cycling", "cricket", "chess", "Music", "Singing", "AI & machine learning", "web & app development", "computer programming", "Blockchain", "Video Games", "Traveling and exploring new places", "painting", "drawing", "photography", "graphic design", "Watching movies", "Watching series"};
    int num_hobies = sizeof(hobies) / sizeof(hobies[0]);
    int choices[22] = {0};
    int c;

    // to clear the terminal screen
#ifdef _WIN32
    system("cls");
#elif _WIN64
    system("cls");
#else
    system("clear");
#endif

    for (int i = 0; i < num_hobies; i++)
    {
        cout << "\n"
             << i + 1 << "." << hobies[i];
    }

    cout << "\nEnter your Choices(ex 1 3 7 etc.. Press 0. to exit):\n";
    do
    {
        cout << "\nEnter choice num:";
        cin >> c;
        if (c > 0 && c <= num_hobies)
        {
            choices[c - 1] = 1;
        }
        else if (c == 0)
        {
            break;
        }
        else
        {
            cout << "\nenter valid choice";
        }
        //
    } while (c != 0);
    string result = "";
    for (int i = 0; i < num_hobies; i++)
    {
        char k = choices[i] == 1 ? ('1') : ('0');
        result = result + k;
    }
    return result;
}

void insertStudentData(string name, bool gender, int rollno, string dept, string email, string password, string interest, bool available)
{
    try
    {
        mongocxx::instance inst{};
        mongocxx::client conn{mongocxx::uri{}};

        bsoncxx::builder::stream::document document{};

        // add values to document
        document << "name" << name
                 << "gender" << gender
                 << "rollno" << rollno
                 << "dept" << dept
                 << "email" << email
                 << "password" << password
                 << "interest" << interest
                 << "available" << available;

        // access student collection
        auto collection = conn["mydb"]["student"];

        // insert document
        bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
            collection.insert_one(document.view());

        if (result)
        {
            cout << "Record inserted successfully" << endl;
        }
        else
        {
            cout << "Record insertion failed" << endl;
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << endl;
    }
}

void getNewUserData()
{

    cout << "*********************************************************";
    cout << "\n\n\t\tSIGN UP";
    string name;
    bool gender;
    int rollno;
    string dept;
    string email;
    int phoneNum;
    string interest = "";
    bool available = false;

    cout << "\nName: ";
    cin >> name;

    // Input validation for gender (allow only 0 or 1)
    cout << "\nGender (1 for male, 0 for female): ";
    while (true)
    {
        if (!(cin >> gender))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter 1 for male or 0 for female: ";
        }
        else if (gender != 0 && gender != 1)
        {
            cout << "Invalid input. Enter 1 for male or 0 for female: ";
        }
        else
        {
            break;
        }
    }

    // Input validation for rollno and phoneNum
    cout << "\nRollNO: ";
    while (!(cin >> rollno))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a valid integer: ";
    }

    cout << "\nDept: ";
    cin >> dept;

    cout << "\nEmail: ";
    cin >> email;

    cout << "\nPhone Number: ";
    while (!(cin >> phoneNum))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a valid integer: ";
    }
    string password, password_confirmation;

    do
    {
        cout << "\nPlease enter your password: ";
        cin >> password;

        cout << "\nPlease confirm your password: ";
        cin >> password_confirmation;

        if (password != password_confirmation)
        {
            cout << "\tPasswords do not match. Please try again." << endl;
        }
    } while (password != password_confirmation);

    cout << "Password confirmed!" << endl;

    cout << "*********************************************************";

#ifdef _WIN32 // to clear the terminal screen
    system("cls");
#else
    system("clear");
#endif

    // interest choosing function to be implemented

    // push to DB idk how
    // insertStudentData(name, gender, rollno, dept,email, password, interest, available);
    interest = getInterest(); // getting a bit stream of interest
    // cout << interest;

    // collected all data : push to db now
}
int main()
{

    getNewUserData();
}
