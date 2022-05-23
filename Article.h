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
    static vector<article *> notExaminedArticles;
    static vector<article *> acceptedArticles;
    static vector<article *> rejectedArticles;
    const user *userLogin;
    vector<string> split(string &str);
    bool minThreeParagraph(string &body);
    bool countBodyWords(string &body);
    bool countNameWords(string &name);
    bool wordsCounter(string &body);
    bool grammarCheck(string &body);
    bool vArticle(article *_article);
    int **lcs(string &str1, string &str2);
    string createId();
    article *searchLoginUserArticle(string &id);
    double similarity(string &a, string &b);

public:
    Article(user *_userLogin);
    ~Article();
    void addArticle(article *newArticle, vector<string> &usernames);
    void trackArticle(string &id);
    void getAllArticle();
    void getArticle(string &id);
};

#endif
