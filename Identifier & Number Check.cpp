#include<bits/stdc++.h>
using namespace std;

bool isIdentifier(string s)
{
    if(!(isalpha(s[0])||s[0]=='_')) return false;
    for(int i = 1;i<s.size();i++)
    {
        if(!(isalnum(s[i])||s[i]=='_')) return false;
    }
    return true;
}

bool isNumber(string s)
{
    bool dotSeen = false,expSeen=false;
    int i = 0;
    if(s[i]=='+' || s[i]=='-') i++;
    for(;i<s.size();i++)
    {
        if(isdigit(s[i])) continue;
        else if(s[i]=='.'  && !dotSeen) dotSeen = true;
        else if((s[i]=='E'||s[i]=='e')&&!expSeen)
        {
            expSeen  = true;
            if(i+1<s.size()&&(s[i+1]=='+'||s[i+1]=='-')) i++;
        }
        else return false;

    }
    return true;
}

int main()
{
    string token;
    cout<<"Please Give a Token : ";
    cin>>token;

    if(isIdentifier(token)) cout<<token<<" is a valid Identifier"<<endl;
    else if(isNumber(token)) cout<<token<<" is a valid Number"<<endl;
    else cout<<token<<" is Invalid"<<endl;
    return 0;
}
