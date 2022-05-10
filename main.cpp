#include <bits/stdc++.h>
using namespace std;
#include "User.h"
#include "Article.h"

int main()
{
    User *a = new User;
    string username = "alai", password = "a1#Algdf";
    a->Register(username, password);
    a->Register(username, password);
    user *loginUser = a->login(username, password);
    cout << loginUser->password << endl;
}
