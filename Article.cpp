#include <bits/stdc++.h>
using namespace std;
#include "Article.h"

Article::Article(){}

Article::~Article() {}

void Article::addArticle(article *newArticle)
{
    if(vArticle(newArticle)){
        for(int i = 0; i < newArticle->authors.size(); i++){
            newArticle->authors[i]->articles.push_back(newArticle);
        }
    }
}

bool Article::vArticle(article *newArticle){
}

