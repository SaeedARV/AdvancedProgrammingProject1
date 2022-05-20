#include <bits/stdc++.h>
#include "User.h"
#include "Article.h"
using namespace std;

User::User() {}

User::~User() {}

vector<user *> User::users = {};

void User::Register(string &username, string &password)
{
    if (this->getUser(username))
    {
        cout << username << " is not available!! Please try another one." << endl;
        return;
    }
    if (!this->vPassword(password))
    {
        cout << "This password is not strong enough. Please try another one." << endl;
        return;
    }
    user *newUser = new user;
    newUser->username = username;
    newUser->password = this->hashPassword(password);
    users.push_back(newUser);
    cout << "You are registered." << endl;
}

user *User::login(string &username, string &password)
{
    user *us = this->getUser(username);
    if (!us)
    {
        cout << username << " is not found!! Please try again." << endl;
        return nullptr;
    }
    if (us->password == this->hashPassword(password))
    {
        cout << "You are logged in." << endl;
        this->loginUser = us;
        return this->loginUser;
    }
    cout << "Password is not correct." << endl;
    return nullptr;
}

user *User::getLoginUser()
{
    return this->loginUser;
}

user *User::getUser(string &username)
{
    for (auto us : users)
    {
        if (us->username == username)
            return us;
    }
    return nullptr;
}

bool User::vPassword(string &password)
{
    const regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*(\\W|_))(?=^\\S*$).{8,}$");
    return regex_match(password, pattern);
}

string User::hashPassword(string &password)
{
    string a = "";
    for (auto pass : password)
    {
        a += ((pass + 33) % 65) ^ 'A';
    }
    return a;
}

bool User::isLogin()
{
    return (bool)this->loginUser;
}

void User::logout()
{
    this->loginUser = nullptr;
}
