#include <bits/stdc++.h>
using namespace std;
#include "Article.h"

Article::Article(user *_userLogin) : userLogin{_userLogin}{}

Article::~Article() {}

string Article::createId(){
    string id = "";
    for(int i = 0; i < 10; i++){
        id += char(rand()%10);
    }
    return id;
}

void Article::addArticle(article *newArticle)
{
    if (vArticle(newArticle))
    {
        for (int i = 0; i < newArticle->authors.size(); i++)
        {
            newArticle->authors[i]->articles.push_back(newArticle);
            allArticles.push_back(newArticle);
        }
    }
}

void Article::trackArticle(string &id){
    for(int i = 0; i < allArticles.size(); i++){
        if(allArticles[i]->id == id){
            cout << "The article is accepted." << endl;
            return;
        } 
    }
    cout << "The article is rejected." << endl;
}

bool Article::vArticle(article *newArticle)
{
    return true;
}

bool Article::minThreeParagraph(string &body)
{
    int paragraph = 1;
    for (int i = 0; i < body.length(); i++)
    {
        if (body[i] == '\n')
        {
            paragraph++;
        }
    }
    return paragraph >= 3;
}

bool Article::sizeBody(string &body)
{
    return body.length() > 100 && body.length() < 5000;
}