#include <bits/stdc++.h>
using namespace std;
#include "User.h"
#include "Article.h"

int main()
{
    User *a = new User;
    string username = "ai", password = "a1#Algdf";
    a->Register(username, password);
    a->Register(username, password);
    user *loginUser = a->login(username, password);

    article *ar = new article;
    ar->body = "asdsadasdasd\nasddsg, asdfsdfdsfsd.";
    ar->authors.push_back(loginUser);
    Article *Ar = new Article(loginUser);
    Ar->addArticle(ar);
    for(int i = 0; i < loginUser->articles.size(); i++){
        cout << loginUser->articles[i]->body << " ";
    }
    cout << '\n';
    Ar->trackArticle(ar->id);
}
