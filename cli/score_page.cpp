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

    bool isAvailable() // public member function to access the 'available' variable
    {
        return available;
    }

    bool hasSameGender(User otherUser) // public member function to access the 'gender' variable
    {
        return gender == otherUser.gender;
    }
};

void scoreUsers(vector<User>& userList)
{
    vector<pair<int, string> > scoreList; // vector to store scores and corresponding user name

    int i=0;
    
        for (int j = i + 1; j < userList.size(); j++) // compare with all other users after i
        {
            if (userList[i].hasSameGender(userList[j]) && userList[j].isAvailable()) { // check if users have same gender and are available
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
                    scoreList.push_back(make_pair(commonInterests, userList[j].getName() + " (" + to_string(userList[j].getScore()) + ")")); // add other user's name and score to vector
                }
            }
        }
    

    sort(scoreList.begin(), scoreList.end(), greater<pair<int, string> >()); // sort vector in descending order of score

    for (int i = 0; i < scoreList.size(); i++) // print results
    {
        cout << scoreList[i].second << endl;
    }
}




int main()
{
    vector<User> userList;

    // populate userList with data

    User user3("nishaanth",1,3, "EC", "nitin@example.com", "1100101000", 0, true);
    User user4("David",1,4, "CS", "david@example.com", "1111101110", 0, true);
    User user5("Emily",0,5, "ME", "emily@example.com", "1100001101", 0, true);


    userList.push_back(user3);
    userList.push_back(user4);
    userList.push_back(user5);
    scoreUsers(userList);

    return 0;
}