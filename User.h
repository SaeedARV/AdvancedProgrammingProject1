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
    vector<article *> acceptedArticles;
    vector<article *> rejectedArticles;
};

class User
{
private:
    user *loginUser = nullptr;
    static vector<user *> users;
    string hashPassword(string &password);
    bool vPassword(string &password);
    static int searchUser(string &username);

public:
    User();
    ~User();
    void Register(string &username, string &password);
    user *login(string &username, string &password);
    static user *getUser(string &username);
    user *getLoginUser();
    bool isLogin();
};

#endif
