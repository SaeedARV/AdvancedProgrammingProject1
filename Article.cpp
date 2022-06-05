#include <bits/stdc++.h>
#include "Article.h"
#include "User.h"
using namespace std;

vector<article *> Article::notExaminedArticles = {};
vector<article *> Article::acceptedArticles = {};
vector<article *> Article::rejectedArticles = {};

Article::Article(user *_userLogin) : userLogin{_userLogin} {}

Article::~Article() {}
// -----------
/*
 *  Global functions
 */

string Article::createId() // Create an ID with 10 digits
{
    string id = "";
    // set for random number
    srand((unsigned)time(0));
    for (int i = 0; i < 10; i++)
    {
        // get random number
        id += to_string(rand() % 10);
    }
    return id;
}

string currentTime() // Get now date and time
{
    // Get time
    time_t t = time(0);
    tm *now = localtime(&t);
    // Edit time and to string
    string date =
        to_string(now->tm_year + 1900) + '/' +
        to_string(now->tm_mon + 1) + '/' +
        to_string(now->tm_mday) + ' ' +
        to_string(now->tm_hour) + ':' +
        to_string(now->tm_min) + ':' +
        to_string(now->tm_sec);

    return date;
}

vector<string> Article::split(string &str) // Split text by space
{
    vector<string> words;
    string word = "";
    int first = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            // add letters to word
            for (int j = first; j < i; j++)
            {
                word += str[j];
            }
            first = i + 1;
            words.push_back(word);
            word = "";
        }
    }
    // add the finaly word
    for (int j = first; j < str.length(); j++)
    {
        word += str[j];
    }
    words.push_back(word);
    return words;
}

int **Article::lcs(string &str1, string &str2) // Get the largest common sub-discipline
{
    int **r;
    r = new int *[2];
    r[0] = new int[2];
    r[1] = new int[2];
    r[0][0] = 0;
    r[0][1] = 0;
    r[1][0] = 0;
    r[1][1] = 0;
    int maxStr = 0;

    for (int i = 0; i < str1.length(); i++)
    {
        for (int j = i; j < str1.length(); j++)
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

double Article::similarity(string &a, string &b) // Get the length of the longest common strings
{
    double ans = 0;
    int **temp = lcs(a, b);
    int len = temp[0][1] - temp[0][0] + 1; // Get length

    if (len < 50)
    {
        return ans;
    }
    ans += len;
    // Chanck text whit longest common strings
    string s1 = a.substr(0, temp[0][0] + 1);
    string e1 = a.substr(temp[0][1] + 1, a.size() - temp[0][1]);
    string s2 = b.substr(0, temp[1][0] + 1);
    string e2 = b.substr(temp[1][1] + 1, b.size() - temp[1][1]);
    ans += similarity(s1, s2);
    ans += similarity(e1, e2);

    return ans;
}
// -----------
/*
 * Verifiers function
 */
bool Article::minThreeParagraph(string &body) // Check text that is at least 3 paragraphs long
{
    int paragraph = 0;
    if (*(body.end() - 1) != '\n')
        paragraph++;
    for (auto ch : body)
    {
        if (ch == '\n')
        {
            paragraph++;
        }
    }
    return paragraph >= 3;
}

bool Article::countBodyWords(string &body) // Check body have 100-5000 words
{
    vector<string> words = this->split(body);
    return words.size() >= 100 && words.size() <= 5000;
}

bool Article::countNameWords(string &name) // Check name have 1-12 words
{
    vector<string> words = this->split(name);
    return words.size() >= 1 && words.size() <= 12;
}

bool Article::wordsCounter(string &body) // Check that no word exists more than 50 times
{
    vector<string> words = this->split(body);
    map<string, int> wordCounter;

    for (auto word : words)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower); // Set word to lowercase letters
        // --------------
        // Remove the symbols from the end of the word
        char end = *(word.end() - 1);
        if (end == '?' || end == '!' || end == '.' || end == ',' || end == ';')
        {
            *(word.end()) = '\0';
        }
        // --------------
        wordCounter[word]++;
    }

    for (auto word : wordCounter) // Check that no word exists more than 50 times
    {
        if (word.second > 50)
            return false;
    }

    return true;
}
// TODO: set comment
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

bool Article::vArticle(article *article) // Check all restrictions
{
    return (this->countNameWords(article->name)) &&
           (this->countBodyWords(article->body)) &&
           (this->minThreeParagraph(article->body)) &&
           (this->grammarCheck(article->body)) &&
           (this->wordsCounter(article->body));
}
// -----------
/*
 * publice function
 */

void Article::addArticle(article *newArticle, vector<string> &usernames) // Add article
{
    // set date and id
    newArticle->date = currentTime();
    newArticle->id = this->createId();
    cout << "The ID is: " << newArticle->id << "\n";

    for (auto username : usernames) // checking if author in register add author in author article else show not found
    {
        if (User::getUser(username))
        {
            newArticle->authors.push_back(User::getUser(username));
        }
        else
        {
            cout << username << " is not found. \n";
        }
    }

    if (vArticle(newArticle)) // check if valid article add to notExaminedArticles and else add to rejectedArticles
    {
        cout << "This Article is under examination.\n";
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

void Article::trackArticle(string &id) // Check similarity
{
    bool rejected = false;
    for (auto notExaminedArticle1 : this->userLogin->notExaminedArticles)
    {
        if (notExaminedArticle1->id == id) // Find Article
        {
            for (auto notExaminedArticle2 : this->notExaminedArticles) // Check with not examined Articles
            {
                if (notExaminedArticle1->id != notExaminedArticle2->id) // Check not selfe
                {
                    if (find(notExaminedArticle1->refId.begin(), notExaminedArticle1->refId.end(), notExaminedArticle2->id) == notExaminedArticle1->refId.end()) // Check the Article not in the refrens
                    {
                        double sim = similarity(notExaminedArticle1->body, notExaminedArticle2->body) * 2 / (notExaminedArticle1->body.size() + notExaminedArticle2->body.size()); // Get similarity

                        if (sim > 0.5)
                        {
                            rejected = true;
                            for (auto author : notExaminedArticle2->authors) // add to reject not examinedArticle2
                            {
                                author->rejectedArticles.push_back(notExaminedArticle2);
                                author->notExaminedArticles.erase(find(author->notExaminedArticles.begin(), author->notExaminedArticles.end(), notExaminedArticle2));
                            }
                            notExaminedArticles.erase(find(notExaminedArticles.begin(), notExaminedArticles.end(), notExaminedArticle2));
                            rejectedArticles.push_back(notExaminedArticle2);
                        }
                    }
                }
            }

            for (auto acceptedArticle : this->acceptedArticles) // Check with accepted Articles
            {

                if (find(notExaminedArticle1->refId.begin(), notExaminedArticle1->refId.end(), acceptedArticle->id) == notExaminedArticle1->refId.end()) // Check the Article not in the refrens
                {

                    double sim = similarity(notExaminedArticle1->body, acceptedArticle->body) * 2 / (notExaminedArticle1->body.size() + acceptedArticle->body.size()); // Get similarity

                    if (sim > 0.5)
                    {
                        rejected = true;
                    }
                }
            }
            if (rejected)
            {
                for (auto author : notExaminedArticle1->authors) // add to reject
                {
                    author->rejectedArticles.push_back(notExaminedArticle1);
                    author->notExaminedArticles.erase(find(author->notExaminedArticles.begin(), author->notExaminedArticles.end(), notExaminedArticle1));
                }

                rejectedArticles.push_back(notExaminedArticle1);
                cout << "This article is rejected." << endl;
            }
            else
            {
                for (auto author : notExaminedArticle1->authors) // add to the accept
                {
                    author->acceptedArticles.push_back(notExaminedArticle1);
                    author->notExaminedArticles.erase(find(author->notExaminedArticles.begin(), author->notExaminedArticles.end(), notExaminedArticle1));
                }

                acceptedArticles.push_back(notExaminedArticle1);
                cout << "This article is accepted." << endl;
            }
            notExaminedArticles.erase(find(notExaminedArticles.begin(), notExaminedArticles.end(), notExaminedArticle1));
        }
    }
}

void Article::getAllArticle() // show all article for login user
{
    if (this->userLogin->notExaminedArticles.size())
    {
        cout << "Not-examined articles:\n";
    }
    for (auto ar : this->userLogin->notExaminedArticles)
    {
        cout << "ID: " << ar->id << "\nName: " << ar->name << "\n----------------------------------------------\n";
    }

    if (this->userLogin->acceptedArticles.size())
    {
        cout << "Accepted articles:\n";
    }
    for (auto ar : this->userLogin->acceptedArticles)
    {
        cout << "ID: " << ar->id << "\nName: " << ar->name << "\n----------------------------------------------\n";
    }
    if (this->userLogin->rejectedArticles.size())
    {
        cout << "Rejected articles:\n";
    }
    for (auto ar : this->userLogin->rejectedArticles)
    {
        cout << "ID: " << ar->id << "\nName: " << ar->name << "\n----------------------------------------------\n";
    }
}

void Article::getArticle(string &id) // Show article
{
    article *art = nullptr;
    if (!art)
        for (auto ar : this->userLogin->notExaminedArticles)
        {
            if (ar->id == id)
            {
                cout << "This Article is under examination.\n";
                art = ar;
            }
        }

    if (!art)
        for (auto ar : this->userLogin->acceptedArticles)
        {
            if (ar->id == id)
            {
                art = ar;
            }
        }

    if (!art)
        for (auto ar : this->userLogin->rejectedArticles)
        {
            if (ar->id == id)
            {
                cout << "This Article is rejected.\n";
                art = ar;
            }
        }

    if (art)
    {
        cout
            << "ID: " << art->id
            << "\nName: " << art->name
            << "\nDate: " << art->date
            << "\nText:\n " << art->body
            << '\n';
    }
    else
    {
        cout << "This article is not found.\n";
    }
}
