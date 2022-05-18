#include <bits/stdc++.h>
#include "Article.h"
#include "User.h"
using namespace std;

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

string currentTime(){
    time_t t = time(0);
    tm* now = localtime(&t);
    string date = to_string(now->tm_year + 1900) + '/' + to_string(now->tm_mon + 1) + '/'
    + to_string(now->tm_mday) + ' ' + 
    to_string(now->tm_hour) + ':' + to_string(now->tm_min) + ':' = to_string(now->tm_sec);

    return date;
}

void Article::addArticle(article *newArticle, vector<string> &usernames)
{
    for(auto username: usernames){
        if(getUSer(username) != nullptr)
        {
            newArticle->authors.push_back(getUSer(username));
        }
    }

    newArticle->date = currentTime();

    if (vArticle(newArticle))
    {
        for (int i = 0; i < newArticle->authors.size(); i++)
        {
            newArticle->authors[i]->articles.push_back(newArticle);
            acceptedArticles.push_back(newArticle);
        }
    }
    else{
        rejectedArticles.push_back(newArticle);
    }
}

void Article::trackArticle(string &id)
{
    for (int i = 0; i < acceptedArticles.size(); i++)
    {
        if (acceptedArticles[i]->id == id)
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

    for (auto word : words)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        char end = *(word.end() - 1);
        if (end == '?' || end == '!' || end == '.' || end == ',' || end == ';')
        {
            *(word.end() - 1) = '\0';
        }
        wordCounter[word]++;
    }

    for (auto word : wordCounter)
    {
        if (word.second > 50)
            return false;
    }

    return true;
}

bool Article::grammarCheck(string &body)
{
    int par1 = 0, par2 = 0;
    for (int i = 0; i < body.size(); i++)
    {
        if (body[i] == ',')
        {
            if (i != body.size() - 1 && body[i + 1] != ' ')
                return false;
            else if (i < body.size() - 2 && body[i + 1] == ' ' && body[i + 2] == ' ')
                return false;
        }
        else if (body[i] == '?' || body[i] == '!' || body[i] == '.' || body[i] == ';')
        {
            if (i != body.size() - 1 && body[i + 1] != ' ')
                return false;
            else if (i < body.size() - 2 && body[i + 1] == ' ' && !isupper(body[i + 2]))
                return false;
        }
        else if (body[i] == '\n')
        {
            if (i != body.size() - 1 && !isupper(body[i + 1]))
                return false;
        }
        else if (body[i] == '(')
        {
            par1++;
        }
        else if (body[i] == ')')
        {
            par2++;
            if (par2 > par1)
                return false;
        }
    }

    if (par1 != par2)
        return false;
    return true;
}

void Article::getAllArticle()
{
    vector<article *> allArticle = this->userLogin->articles;
    for (auto ar : allArticle)
    {
        cout << "ID: " << ar->id << "\nName: " << ar->name << "\n----------------------------------------------\n";
    }
}

article *Article::searchArticle(string &id)
{
    for (auto ar : this->articles)
    {
        if (ar->id == id)
        {
            return ar;
        }
    }
    return nullptr;
}

void Article::getArticle(string &id)
{
    article *ar = this->searchArticle(id);
    if (ar)
    {
        cout
            << "ID: " << ar->id
            << "\nName: " << ar->name
            << "\nDate: " << ar->date
            << "\nText: " << ar->body
            << '\n';
    }
    else
    {
        cout << "not found\n";
    }
}