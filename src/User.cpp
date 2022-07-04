#include <bits/stdc++.h>
#include "User.h"
#include "Article.h"
using namespace std;

User::User() {}

User::~User() {}

vector<user *> User::users = {};
// -----------

/*
 *  Private functions
 */

string User::hashPassword(string &password) // Hash the password
{
    string a = "";
    for (auto pass : password) 
    {
        a += ((pass + 33) % 65) ^ 'A';
    }
    return a;
}

bool User::vPassword(string &password) // Check if the password is valid
{
    // Check if the password has uppercase letters, lowercase letters, numbers, special character, and the minimum lenght of 8 characters
    const regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*(\\W|_))(?=^\\S*$).{8,}$");
    return regex_match(password, pattern);
}
// -----------

/*
 * public function
 */

void User::Register(string &username, string &password) // Register user
{
    if (this->getUser(username)) // Check if the username is available
    {
        cout << username << " is not available!! Please try another one." << endl;
        return;
    }
    if (!this->vPassword(password)) // Check if the password is valid
    {
        cout << "This password is not strong enough. Please try another one." << endl;
        return;
    }
    // Add the user
    user *newUser = new user;
    newUser->username = username;
    newUser->password = this->hashPassword(password); // Hash the password
    users.push_back(newUser);
    cout << "You are registered." << endl;
}

user *User::login(string &username, string &password) // Login
{
    user *us = this->getUser(username);
    if (!us) // Find the user
    {
        cout << username << " is not found!! Please try again." << endl;
        return nullptr;
    }
    if (us->password == this->hashPassword(password)) // Check the password
    {
        cout << "You are logged in." << endl;
        this->loginUser = us;
        return this->loginUser;
    }
    cout << "Password is not correct." << endl;
    return nullptr;
}

user *User::getUser(string &username) // Search for the user
{
    for (auto us : users)
    {
        if (us->username == username)
            return us;
    }
    return nullptr;
}

user *User::getLoginUser() // Get the logged-in user
{
    return this->loginUser;
}

bool User::isLogin() // Check if the user is logged in or not
{
    return (bool)this->loginUser;
}

void User::logout() // Log out
{
    this->loginUser = nullptr;
}
