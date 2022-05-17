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
    static vector<article *> articles;
    const user *userLogin;
    bool minThreeParagraph(string &body);
    bool countBodyWords(string &body);
    bool countNameWords(string &name);
    bool wordsCounter(string &body);
    vector<string> split(string &str);


public:
    Article(user *_userLogin);
    ~Article();
    string createId();
    void addArticle(article *newArticle);
    void trackArticle(string &id);
    bool vArticle(article *_article);

};

#endif
