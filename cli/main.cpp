#include <iostream>
#include <string>

using namespace std;

int main()
{
    // Define the username and password
    string username = "admin";
    string password = "password";

    // Prompt the user to enter their username and password
    string input_username, input_password;
    cout << "Username: ";
    cin >> input_username;
    cout << "Password: ";
    cin >> input_password;

    // Check if the username and password are correct
    if (input_username == username && input_password == password)
    {
        cout << "Login successful!" << endl;
    }
    else
    {
        cout << "Incorrect username or password." << endl;
    }

    return 0;
}
