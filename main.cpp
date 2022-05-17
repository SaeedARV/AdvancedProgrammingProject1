#include <bits/stdc++.h>
using namespace std;
#include "User.h"
#include "Article.h"

void error404()
{
    cout << "404\nNot found\n";
}

int main()
{
    string work;
    User *thisUser = new User;
    user *loginUser = nullptr;

    while (!thisUser->isLogin())
    {
        cout << "----------------\n";
        cout << "| Register | 0 |\n";
        cout << "----------------\n";
        cout << "|  Login   | 1 |\n";
        cout << "----------------\n";
        cout << "Please enter your Number: ";
        cin >> work;
        if (work == "0") // Register
        {
            string username, password;
            cout << "Please enter your username: ";
            cin >> username;
            cout << "Please enter your password: ";
            cin >> password;
            thisUser->Register(username, password);
        }
        else if (work == "1") // Login
        {
            string username, password;
            cout << "Please enter your username: ";
            cin >> username;
            cout << "Please enter your password: ";
            cin >> password;
            loginUser = thisUser->login(username, password);
        }
        else // 404
        {
            error404();
        }
    }

    Article *thisArticle = new Article(loginUser);

    while (true)
    {
        cout << "-------------------\n";
        cout << "| Add Article | 0 |\n";
        cout << "-------------------\n";
        cout << "Please enter your Number: ";
        cin >> work;
        if (work == "0")
        {
            article *ar = new article;

            string name;
            cout << "Please enter the name of your article: ";
            cin >> name;
            ar->name = name;

            cout << "Please enter the number of reference: \n";
            int n;
            cin >> n;
            cout << "Please enter reference IDs: \n";
            vector<string> refIds;
            string refId;
            for (int i = 0; i < n; i++)
            {
                cin >> refId;
                refIds.push_back(refId);
            }
            ar->refId = refIds;

            cout << "Please enter the number of authors: \n";
            cin >> n;
            cout << "Please enter username of authors: \n";
            string author;
            vector<string> authors;
            for (int i = 0; i < n; i++)
            {
                cin >> author;
                authors.push_back(author);
            }

            cout << "Please enter the body of your article: (Put an enter at the end of your text) \n";
            string body = "";
            string line;
            while (getline(cin, line))
            {
                if (line.empty())
                {
                    break;
                }
                body += line + '\n';
            }
            ar->body;

            thisArticle->addArticle(ar, authors);
        }
    }
}
