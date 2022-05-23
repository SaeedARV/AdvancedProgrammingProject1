#include <bits/stdc++.h>
#include "Article.h"
#include "User.h"
using namespace std;

vector<article *> Article::notExaminedArticles = {};
vector<article *> Article::acceptedArticles = {};
vector<article *> Article::rejectedArticles = {};

Article::Article(user *_userLogin) : userLogin{_userLogin} {}

Article::~Article() {}

string Article::createId()
{
    string id = "";
    srand((unsigned)time(0));
    for (int i = 0; i < 10; i++)
    {
        id += to_string(rand() % 10);
    }
    return id;
}

string currentTime()
{
    time_t t = time(0);
    tm *now = localtime(&t);
    string date =
        to_string(now->tm_year + 1900) + '/' +
        to_string(now->tm_mon + 1) + '/' +
        to_string(now->tm_mday) + ' ' +
        to_string(now->tm_hour) + ':' +
        to_string(now->tm_min) + ':' +
        to_string(now->tm_sec);

    return date;
}

void Article::addArticle(article *newArticle, vector<string> &usernames)
{
    for (auto username : usernames)
    {
        if (User::getUser(username))
        {
            newArticle->authors.push_back(User::getUser(username));
        }
        else
        {
            cout << username << " is not found.";
        }
    }

    newArticle->date = currentTime();
    newArticle->id = this->createId();
    cout << "The ID is: " << newArticle->id << "\n";

    if (vArticle(newArticle))
    {
        // todo: better text
        cout << "Posted for review ...\n";
        for (auto author : newArticle->authors)
        {
            author->notExaminedArticles.push_back(newArticle);
        }
        notExaminedArticles.push_back(newArticle);
    }
    else
    {
        cout << "Your article is rejected.\n";
        for (auto author : newArticle->authors)
        {
            author->rejectedArticles.push_back(newArticle);
        }
        rejectedArticles.push_back(newArticle);
    }
}

int **Article::lcs(string &str1, string &str2)
{
    int **r;
    r[0] = new int[2];
    r[1] = new int[2];
    r[0][0] = 0;
    r[0][1] = 0;
    r[1][0] = 0;
    r[1][1] = 0;
    int maxStr = 0;

    for (int i = 0; i < str1.length(); i++)
    {
        for (int j = 0; j < str2.length(); j++)
        {
            string a = "";
            for (int k = i; k <= j; k++)
            {
                a += str1[k];
            }

            int i2 = str2.find(a);
            int len = a.length();
            if (i2 == -1)
            {
                break;
            }
            else if (len > maxStr)
            {
                maxStr = len;
                r[0][0] = i;
                r[0][1] = j;
                r[1][0] = i2;
                r[1][1] = i2 + maxStr - 1;
            }
        }
    }
    return r;
}

// TODO:edit trackArticle
void Article::trackArticle(string &id)
{
    for (auto acceptedArticle : this->acceptedArticles)
    {
        if (acceptedArticle->id == id)
        {
            cout << "This article is accepted." << endl;
            return;
        }
    }
    cout << "This article is rejected." << endl;
}

bool Article::vArticle(article *article)
{
    return (this->countNameWords(article->name)) &&
           (this->countBodyWords(article->body)) &&
           (this->minThreeParagraph(article->body)) &&
           (this->grammarCheck(article->body)) &&
           (this->wordsCounter(article->body));
}

bool Article::minThreeParagraph(string &body)
{
    int paragraph = 1;
    for (auto ch : body)
    {
        if (ch == '\n')
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
            *(word.end()) = '\0';
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
    int openPar = 0, closePar = 0;
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
            if (i != body.size() - 1 && body[i + 1] != ' ' && body[i + 1] != '\n')
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
            openPar++;
        }
        else if (body[i] == ')')
        {
            closePar++;
            if (closePar > openPar)
                return false;
        }
    }

    if (openPar != closePar)
        return false;
    return true;
}

void Article::getAllArticle()
{
    cout << "notExaminedArticles:\n";
    for (auto ar : this->userLogin->notExaminedArticles)
    {
        cout << "ID: " << ar->id << "\nName: " << ar->name << "\n----------------------------------------------\n";
    }

    cout << "Acceoted articles:\n";
    for (auto ar : this->userLogin->acceptedArticles)
    {
        cout << "ID: " << ar->id << "\nName: " << ar->name << "\n----------------------------------------------\n";
    }
    cout << "Rejected articles:\n";
    for (auto ar : this->userLogin->rejectedArticles)
    {
        cout << "ID: " << ar->id << "\nName: " << ar->name << "\n----------------------------------------------\n";
    }
}

article *Article::searchLoginUserArticle(string &id)
{
    for (auto ar : this->userLogin->notExaminedArticles)
    {
        if (ar->id == id)
        {
            cout << "This Article is under examination.\n";
            return ar;
        }
    }

    for (auto ar : this->userLogin->acceptedArticles)
    {
        if (ar->id == id)
        {
            return ar;
        }
    }
    for (auto ar : this->userLogin->rejectedArticles)
    {
        if (ar->id == id)
        {
            cout << "This Article is rejected.\n";
            return ar;
        }
    }
    return nullptr;
}

void Article::getArticle(string &id)
{
    article *ar = this->searchLoginUserArticle(id);
    if (ar)
    {
        cout
            << "ID: " << ar->id
            << "\nName: " << ar->name
            << "\nDate: " << ar->date
            << "\nText:\n " << ar->body
            << '\n';
    }
    else
    {
        cout << "This article is not found.\n";
    }
}

double Article::similarity(string &a, string &b)
{
    double ans = 0;
    int **temp = lcs(a, b);

    if (temp[0][1] - temp[0][0] + 1 < 50)
    {
        return ans;
    }

    ans += temp[0][1] - temp[0][0] + 1;

    string p = a.substr(0, temp[0][0] + 1), q = b.substr(0, temp[1][0] + 1);
    string r = a.substr(temp[0][1] + 1, a.size()), s = b.substr(temp[1][1] + 1, b.size());
    ans += similarity(p, q);
    ans += similarity(r, s);
    return ans;
}
