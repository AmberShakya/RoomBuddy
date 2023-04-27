#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class User
{
private:
    string name;
    bool gender;
    int rollno;
    string dept;
    string email;
    // int phoneNum;
    vector<string> interests;
    int score;

public:
    User(string name, bool gender, int rollno, string dept, string email, int phoneNum, vector<string> interests)
        : name(name), gender(gender), rollno(rollno), dept(dept), email(email), phoneNum(phoneNum), interests(interests), score(0) {}

    void addScore(int points)
    {
        score += points;
    }

    int getScore()
    {
        return score;
    }

    vector<string> getInterests()
    {
        return interests;
    }

    string getName()
    {
        return name;
    }
};

void scoreUsers(vector<User> &userList)
{
    vector<pair<int, string>> scoreList; // vector to store scores and corresponding user name

    for (int i = 0; i < userList.size(); i++) // iterate over all users
    {
        for (int j = i + 1; j < userList.size(); j++) // compare with all other users after i
        {
            int commonInterests = 0;
            vector<string> iInterests = userList[i].getInterests();
            vector<string> jInterests = userList[j].getInterests();

            for (int k = 0; k < iInterests.size(); k++) // count number of common interests
            {
                if (find(jInterests.begin(), jInterests.end(), iInterests[k]) != jInterests.end())
                {
                    commonInterests++;
                }
            }

            if (commonInterests > 0) // if common interests are found, add score to both users and add the other user's name to the vector
            {
                userList[i].addScore(commonInterests);
                userList[j].addScore(commonInterests);
                scoreList.push_back(make_pair(commonInterests, userList[j].getName() + " (" + to_string(userList[j].getScore()) + ")")); // add other user's name and score to vector
            }
        }
    }

    sort(scoreList.begin(), scoreList.end(), greater<pair<int, string>>()); // sort vector in descending order of score

    for (int i = 0; i < scoreList.size(); i++) // print results
    {
        cout << scoreList[i].second << endl;
    }
}

int main()
{
    vector<User> userList;

    // populate userList with data

    // example data
    vector<string> interests1 = {"Cricket", "Football", "Hockey"};
    vector<string> interests2 = {"Cricket", "Tennis"};
    vector<string> interests3 = {"Football", "Basketball"};
    vector<string> interests4 = {"Cricket", "Hockey", "Basketball"};
    vector<string> interests5 = {"Hockey", "Tennis"};

    User user1("Alice", 0, 1, "CS", "alice@example.com", 1234567890, interests1);
    User user2("Bob", 1, 2, "EC", "bob@example.com", 2345678901, interests2);
    User user3("Charlie", 1, 3, "ME", "charlie@example.com", 3456789012, interests3);
    User user4("Eve", 0, 5, "EE", "eve@example.com", 5678901234, interests5);

    userList.push_back(user1);
    userList.push_back(user2);
    userList.push_back(user3);
    userList.push_back(user4);

    scoreUsers(userList);

    return 0;
}