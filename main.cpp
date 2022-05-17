#include <bits/stdc++.h>
using namespace std;
#include "User.h"
#include "Article.h"

void errore404()
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
            errore404();
        }
    }
    
}
