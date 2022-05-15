#ifndef ARTICLE_H_INCLUDED
#define ARTICLE_H_INCLUDED

#include <bits/stdc++.h>
#include "User.h"

struct user;
struct article
{
    std::string name;
    std::string date;
    std::string id;
    std::string body;
    std::vector<article *> refId;
    std::vector<user *> authors;
};

class Article
{
private:
    vector<article *> allArticles;

public:
    Article();
    ~Article();
    void addArticle(article *newArticle);
    void trackArticle(std::string &id);
    bool vArticle(article *newArticle);
};

#endif
