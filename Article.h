#ifndef ARTICLE_H_INCLUDED
#define ARTICLE_H_INCLUDED

#include <bits/stdc++.h>
#include "User.h"

using std::string;
using std::vector;

struct user;
struct article
{
    string name;
    string date;
    string id;
    string body;
    vector<string> refId;
    vector<user *> authors;
};

class Article
{
private:
    vector<article *> allArticles;
    bool minThreeParagraph(string &body);
    bool sizeBody(string &body);
    const user *userLogin;

public:
    Article(user *_userLogin);
    ~Article();
    void addArticle(article *newArticle);
    void trackArticle(std::string &id);
    bool vArticle(article *newArticle);
};

#endif
