#include <iostream>
#include <vector>
#include <sqlite3.h>
using namespace std;

// Function to handle errors thrown by SQLite
static int errorHandler(void *NotUsed, int errorCode, const char *errorMessage)
{
    cerr << "SQLite error: " << errorMessage << endl;
    return 0;
}

// Function to insert user data into the database
void insertUserData(string name, bool gender, int rollno, string dept, string email, int phoneNum, vector<string> interests)
{
    // Open the database
    sqlite3 *db;
    int result = sqlite3_open("user_data.db", &db);

    if (result != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Prepare the SQL statement
    sqlite3_stmt *stmt;
    result = sqlite3_prepare_v2(db, "INSERT INTO users (name, gender, rollno, dept, email, phoneNum) VALUES (?, ?, ?, ?, ?, ?)", -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind the parameters to the statement
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, gender);
    sqlite3_bind_int(stmt, 3, rollno);
    sqlite3_bind_text(stmt, 4, dept.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, phoneNum);

    // Execute the statement
    result = sqlite3_step(stmt);

    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting data into database: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // Get the ID of the last inserted row
    int userId = sqlite3_last_insert_rowid(db);

    // Prepare the SQL statement to insert interests
    result = sqlite3_prepare_v2(db, "INSERT INTO interests (user_id, interest) VALUES (?, ?)", -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind the user ID to the statement
    sqlite3_bind_int(stmt, 1, userId);

    // Insert each interest
    for (const string &interest : interests)
    {
        sqlite3_bind_text(stmt, 2, interest.c_str(), -1, SQLITE_TRANSIENT);

        result = sqlite3_step(stmt);

        if (result != SQLITE_DONE)
        {
            cerr << "Error inserting data into database: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        sqlite3_reset(stmt);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);
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
    

    // push to DB idk how
}
int main()
{
    getNewUserData();
}
