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
        cout << username << "  is not available!!\nPlease try another one" << endl;
        return;
    }
    if (!this->vPassword(password))
    {
        cout << "This password is not strong enough.\nPlease try another one." << endl;
        return;
    }
    user *newUser = new user;
    newUser->username = username;
    newUser->password = this->hashPassword(password);
    this->users.push_back(newUser);
    cout << "you are registered:)";
}

user *User::login(string &username, string &password)
{
    int user = this->searchUser(username);
    if (user == -1)
    {
        cout << username << "  is not found!!\nPlease try again" << endl;
        return nullptr;
    }
    if (this->users[user]->password == this->hashPassword(password))
    {
        cout << "you are logined" << endl;
        this->loginUser = this->users[user];
        return this->loginUser;
    }
    cout << "password is not correct" << endl;
}

user *User::getLoginUser()
{
    return this->getLoginUser();
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
    for (int i = 0; i < this->users.size(); i++)
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
    for (int i = 0; i < password.length(); i++)
    {
        a += ((password[i] + 33) % 65) ^ 'A';
    }
    return a;
}

void User::addArticle(Article *newArticle)
{
    this->loginUser->articles.push_back(newArticle);
}

vector<Article *> User::getArticles()
{
    return this->loginUser->articles;
}
