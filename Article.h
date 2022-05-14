#ifndef ARTICLE_H_INCLUDED
#define ARTICLE_H_INCLUDED

#include <bits/stdc++.h>
#include "User.h"

struct user;
struct article
{
    std::string name;
    std::string date;
    std::string Id;
    std::string body;
    std::vector<article *> refId;
    std::vector<user *> authors;
};

class Article
{
private:
public:
    Article();
    ~Article();
    void addArticle(article *newArticle);
    bool vArticle(article *newArticle);
};




#endif
