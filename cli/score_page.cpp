#include <iostream>
#include <vector>
#include <algorithm>
#include<sqlite3.h>
using namespace std;

class User
{
private:
    string name;
    bool gender;
    int rollno;
    string dept;
    string email;
    string interests;
    int score;
    bool available;

public:
    User(string name, bool gender, int rollno, string dept, string email, string interests, int score, bool available)
        : name(name), gender(gender), rollno(rollno), dept(dept), email(email), interests(interests), score(score), available(available) {}

    void addScore(int points)
    {
        score += points;
    }

    int getScore()
    {
        return score;
    }

    string getUserInterests()
    {
        return interests;
    }

    string getName()
    {
        return name;
    }

    string getDept()
    {
        return dept;
    }

    int getRollno()
    {
        return rollno;
    }

    string getEmail()
    {
        return email;
    }

    bool isAvailable() 
    {
        return available;
    }

    bool hasSameGender(User otherUser) 
    {
        return gender == otherUser.gender;
    }
};

vector<User> getUsersFromDatabase(int rollno)
{
    vector<User> userList;

    // connect to database
    sqlite3* db;
    if (sqlite3_open("students.db", &db) == SQLITE_OK)
    {
        // build query to retrieve user details
        string query = "SELECT name, gender, rollno, dept, email, interests, score, available FROM Students WHERE rollno != " + to_string(rollno) + ";";

        // execute query and retrieve results
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK)
        {
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                // retrieve values from database row
                string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                bool gender = sqlite3_column_int(stmt, 1);
                int rollno = sqlite3_column_int(stmt, 2);
                string dept = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
                string interests = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
                int score = sqlite3_column_int(stmt, 6);
                bool available = sqlite3_column_int(stmt, 7);

                // create User object and add to vector
                User user(name, gender, rollno, dept, email, interests, score, available);
                userList.push_back(user);
            }
        }

        // finalize statement and close database
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    return userList;
}

void scoreUsers(vector<User> &userList)
{
    vector<pair<int, string> > scoreList; // vector to store scores and corresponding user name

    int i = 0;

    for (int j = i + 1; j < userList.size(); j++) // compare with all other users after i
    {
        if (userList[i].hasSameGender(userList[j]) && userList[j].isAvailable())
        { // check if users have same gender and are available
            int commonInterests = 0;
            string iInterests = userList[i].getUserInterests();
            string jInterests = userList[j].getUserInterests();

            for (int k = 0; k < iInterests.length() && k < jInterests.length(); k++) // count number of common interests
            {
                if (iInterests[k] == '1' && jInterests[k] == '1')
                {
                    commonInterests++;
                }
            }

            if (commonInterests > 0) // if common interests are found, add score to both users and add the other user's name to the vector
            {
                userList[i].addScore(commonInterests);
                userList[j].addScore(commonInterests);
                scoreList.push_back(make_pair(commonInterests, userList[j].getName() + " (" + userList[j].getEmail() + ", " + to_string(userList[j].getScore()) + ")")); // add other user's name, email, and score to vector
            }
            }
        }

    sort(scoreList.begin(), scoreList.end(), greater<pair<int, string> >()); // sort vector in descending order of score

    for(int i = 0; i < scoreList.size(); i++) // print results
    {
        cout << scoreList[i].second << endl;
    }
}

int main()
{
    vector<User> userList;

    // populate userList with data

    User user3("nishaanth", 1, 3, "EC", "nitin@example.com", "1100101000", 0, true);
    User user4("David", 1, 4, "CS", "david@example.com", "1111101110", 0, true);
    User user5("Emily", 0, 5, "ME", "emily@example.com", "1100001101", 0, true);

    userList.push_back(user3);
    userList.push_back(user4);
    userList.push_back(user5);
    scoreUsers(userList);

    return 0;
}