#include <bits/stdc++.h>
#include "User.h"
#include "Article.h"
using namespace std;

User::User() {}

User::~User() {}

vector<user *> User::users = {};
// -----------
/*
 *  Global functions
 */
user *User::getUser(string &username) // Serch user
{
    for (auto us : users)
    {
        if (us->username == username)
            return us;
    }
    return nullptr;
}

string User::hashPassword(string &password) // Hashing the password
{
    string a = "";
    for (auto pass : password) // Get all char and chenging
    {
        a += ((pass + 33) % 65) ^ 'A';
    }
    return a;
}

bool User::vPassword(string &password) // Check validation password
{
    // Check uppercase and lowercase letters and numbers and special character and minimum lenght of 8 characters
    const regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*(\\W|_))(?=^\\S*$).{8,}$");
    return regex_match(password, pattern);
}
// -----------
/*
 * publice function
 */
void User::Register(string &username, string &password) // Register user
{
    if (this->getUser(username)) // Check username available
    {
        cout << username << " is not available!! Please try another one." << endl;
        return;
    }
    if (!this->vPassword(password)) // Check the passwor valid
    {
        cout << "This password is not strong enough. Please try another one." << endl;
        return;
    }
    // add user
    user *newUser = new user;
    newUser->username = username;
    newUser->password = this->hashPassword(password); // set Hash password
    users.push_back(newUser);
    cout << "You are registered." << endl;
}

user *User::login(string &username, string &password) // Login user
{
    user *us = this->getUser(username);
    if (!us) // Found user
    {
        cout << username << " is not found!! Please try again." << endl;
        return nullptr;
    }
    if (us->password == this->hashPassword(password)) // Check password
    {
        cout << "You are logged in." << endl;
        this->loginUser = us;
        return this->loginUser;
    }
    cout << "Password is not correct." << endl;
    return nullptr;
}

user *User::getLoginUser() // Get user is logined
{
    return this->loginUser;
}

bool User::isLogin() // Check login or no
{
    return (bool)this->loginUser;
}

void User::logout() // Log out user
{
    this->loginUser = nullptr;
}
