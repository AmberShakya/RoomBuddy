#include <iostream>
#include <vector>
using namespace std;

class User
{
private:
    string name;
    bool gender; // 1 if male <> 0 if female Assuming there are only 2 genders
    int rollno;
    string dept;
    string email;
    int phoneNum;
    vector<string> interests;

public:
    // Constructor
    User(string name, bool gender, int rollno, string dept, string email, int phoneNum, vector<string> interests)
        : name(name), gender(gender), rollno(rollno), dept(dept), email(email), phoneNum(phoneNum), interests(interests) {}
};

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

    cout << "*********************************************************";

#ifdef _WIN32 // to clear the terminal screen
    system("cls");
#else
    system("clear");
#endif

    cout << "*********************************************************";
    cout << "\n1.Cricket 2.football 3.hockey";

    vector<string> interests;
    vector<string> int_list;
    int_list.push_back("Cricket");
    int_list.push_back("Football");
    int_list.push_back("doodsa");

    int choice = 1;
    while (choice != 0)
    {

        cout << "\nEnter interest (0 to stop): ";
        cin >> choice;
        if (choice == 0)
        {
            break;
        }
        interests.push_back(int_list[choice]);
    }
    cout << "*********************************************************";
    User newUser(name, gender, rollno, dept, email, phoneNum, interests);

    // push to DB idk how
}
int main()
{
    getNewUserData();
}
