#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <bits/stdc++.h>
#include "Article.h"

struct user
{
    std::string username;
    std::string password;
    std::vector<Article *> articles;
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
    void addArticle(Article *newArticle);
    std::vector<Article *> getArticles();
};

#endif // USER_H_INCLUDED
