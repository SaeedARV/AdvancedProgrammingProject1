#include <bits/stdc++.h>
#include "User.h"
#include "Article.h"
using namespace std;

User::User() {}

User::~User() {}

void User::Register(string &username, string &password)
{
    if (this->searchUser(username) != -1)
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
    this->users.push_back(newUser);
    cout << "You are registered:)";
}

user *User::login(string &username, string &password)
{
    int user = this->searchUser(username);
    if (user == -1)
    {
        cout << username << " is not found!! Please try again." << endl;
        return nullptr;
    }
    if (this->users[user]->password == this->hashPassword(password))
    {
        cout << "You are logged in." << endl;
        this->loginUser = this->users[user];
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
    int user = this->searchUser(username);
    if (user == -1)
    {
        cout << "not found user!!" << endl;
        return nullptr;
    }
    return this->users[user];
}

int User::searchUser(string &username)
{
    for (int i = 0; i < (int)this->users.size(); i++)
    {
        if (this->users[i]->username == username)
            return i;
    }
    return -1;
}

bool User::vPassword(string &password)
{
    const regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*(\\W|_))(?=^\\S*$).{8,}$");
    return regex_match(password, pattern);
}

string User::hashPassword(string &password)
{
    string a = "";
    for (int i = 0; i < (int)password.length(); i++)
    {
        a += ((password[i] + 33) % 65) ^ 'A';
    }
    return a;
}
