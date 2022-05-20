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

    while (true)
    {
        while (!thisUser->isLogin())
        {
            cout << "----------------\n";
            cout << "| Register | 0 |\n";
            cout << "----------------\n";
            cout << "|  Login   | 1 |\n";
            cout << "----------------\n";
            cout << "Please enter a Number: ";
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

        while (thisUser->isLogin())
        {
            cout << "------------------------\n";
            cout << "| Add Article      | 0 |\n";
            cout << "------------------------\n";
            cout << "| Track Article    | 1 |\n";
            cout << "------------------------\n";
            cout << "| Get All Articles | 2 |\n";
            cout << "------------------------\n";
            cout << "| Get An Article   | 3 |\n";
            cout << "------------------------\n";
            cout << "| Logout           | 3 |\n";
            cout << "------------------------\n";
            cout << "| Exit             | 4 |\n";
            cout << "------------------------\n";
            cout << "Please enter a Number: ";
            cin >> work;
            if (work == "0") // Add Article
            {
                article *ar = new article;

                string name;
                cout << "Please enter the name of your article: ";
                getline(cin >> ws, name);
                ar->name = name;

                cout << "Please enter the number of reference: ";
                int n;
                cin >> n;
                if (n > 0)
                {
                    cout << "Please enter reference IDs: \n";
                }
                vector<string> refIds;
                string refId;
                for (int i = 0; i < n; i++)
                {
                    cin >> refId;
                    refIds.push_back(refId);
                }
                ar->refId = refIds;

                cout << "Please enter the number of authors: ";
                cin >> n;
                if (n > 0)
                {
                    cout << "Please enter username of authors: \n";
                }
                string author;
                vector<string> authors;
                string usernameLoginUser = thisUser->getLoginUser()->username;
                authors.push_back(usernameLoginUser);
                for (int i = 0; i < n; i++)
                {
                    cin >> author;
                    authors.push_back(author);
                }

                cout << "Please enter the body of your article: (Put an back tike (`) at the end of your text) \n";
                string body;
                getline(cin >> ws, body, '`');
                ar->body = body;

                thisArticle->addArticle(ar, authors);
            }
            else if (work == "1") // Track Article
            {
                string id;
                cout << "Please enter your article ID: ";
                cin >> id;
                thisArticle->trackArticle(id);
            }
            else if (work == "2") // Get All Articles
            {
                thisArticle->getAllArticle();
            }
            else if (work == "3") // Get Arti
            {
                string id;
                cout << "Please enter your article ID: ";
                cin >> id;
                thisArticle->getArticle(id);
            }
            else if (work == "4") // Logout
            {
                thisUser->logout();
                cout << "You are logged out!\n";
                delete thisArticle;
            }
            else if (work == 4) // Exit
            {
                cout << "Good bye!\n";
                return 0;
            }
            else // 404
            {
                error404();
            }
        }
    }
}
