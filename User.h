#include <vector>
#include <string>
#include "Article.h"

struct user
{
    string username;
    string password;
    vector<Article *> articles;
};

class User
{
private:
    user *loginUser;
    vector<user *> users;
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
    void addArticle(Article *newArticle);
    vector<Article *> getArticles();
};
