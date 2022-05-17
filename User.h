#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <bits/stdc++.h>
#include "Article.h"

using std::string;
using std::vector;

struct article;
struct user
{
    string username;
    string password;
    vector<article *> articles;
};

class User
{
private:
    user *loginUser = nullptr;
    static vector<user *> users;
    string hashPassword(string &password);
    int searchUser(string &username);
    bool vPassword(string &password);

public:
    User();
    ~User();
    void Register(string &username, string &password);
    user *login(string &username, string &password);
    user *getUser(string &username);
    user *getLoginUser();
    bool isLogin();
};

#endif
