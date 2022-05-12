#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <bits/stdc++.h>
#include "Article.h"

struct article;
struct user
{
    std::string username;
    std::string password;
    std::vector<article *> articles;
};

class User
{
private:
    user *loginUser;
    std::vector<user *> users;
    std::string hashPassword(std::string &password);
    int searchUser(std::string &username);
    bool vPassword(std::string &password);

public:
    User();
    ~User();
    void Register(std::string &username, std::string &password);
    user *login(std::string &username, std::string &password);
    user *getUser(std::string &username);
    user *getLoginUser();
};

#endif 
