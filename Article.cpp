#include <bits/stdc++.h>
using namespace std;
#include "Article.h"

Article::Article(user *_userLogin) : userLogin{_userLogin}
{
}

Article::~Article() {}

string Article::createId()
{
    string id = "";
    for (int i = 0; i < 10; i++)
    {
        id += char(rand() % 10);
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

void Article::trackArticle(string &id)
{
    for (int i = 0; i < allArticles.size(); i++)
    {
        if (allArticles[i]->id == id)
        {
            cout << "The article is accepted." << endl;
            return;
        }
    }
    cout << "The article is rejected." << endl;
}

bool Article::vArticle(article *_article)
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

vector<string> Article::split(string &str)
{
    vector<string> words;
    string word = "";
    long long int first = 0;
    for (long long int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            for (int j = first; j < i; j++)
            {
                word += str[j];
            }
            first = i + 1;
            words.push_back(word);
            word = "";
        }
    }
    for (int j = first; j < str.length(); j++)
    {
        word += str[j];
    }
    words.push_back(word);
    return words;
}

bool Article::countBodyWords(string &body)
{
    vector<string> words = this->split(body);
    return words.size() >= 100 && words.size() <= 5000;
}

bool Article::countNameWords(string &name)
{
    vector<string> words = this->split(name);
    return words.size() <= 12;
}

bool Article::wordsCounter(string &body)
{
    vector<string> words = this->split(body);
    map<string, int> wordCounter;

    for (int i = 0; i < words.size(); i++)
    {
        transform(words[i].begin(), words[i].end(), words[i].begin(), ::tolower);
        char end = *(words[i].end() - 1);
        if (end == '?' || end == '!' || end == '.' || end == ',' || end == ';')
        {
            *(words[i].end() - 1) = '\0';
        }
        wordCounter[words[i]]++;
    }

    for (auto word : wordCounter)
    {
        if (word.second > 50)
            return false;
    }

    return true;
}