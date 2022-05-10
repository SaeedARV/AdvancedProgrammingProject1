#ifndef ARTICLE_H_INCLUDED
#define ARTICLE_H_INCLUDED

#include <bits/stdc++.h>
#include "User.h"

struct article
{
    std::string name;
    std::string date;
    std::string Id;
    std::string body;
    std::vector<article *> refId;
    std::vector<user *> author;
};

class Article
{
private:
public:
    Article();
    ~Article();
};
/*
void addArticle(Article *newArticle);
std::vector<Article *> getArticles();
*/

#endif // ARTICLE_H_INCLUDED
