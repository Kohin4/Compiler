#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int main()
{
    ifstream fin("input.c");
    ofstream fout("output.c");
    if(!fin.is_open()||!fout.is_open())
    {
        cout<<"Error opening File"<<endl;
        return 1;
    }

    enum State {normal,in_string,in_char,in_sl_comment,in_ml_comment};
    State state=normal;

    char c;
    while(fin.get(c))
    {
        if(state==normal)
        {
            if(c=='/')
            {
                if(fin.peek()=='/')
                {
                    state=in_sl_comment;
                    fin.get(c);
                    continue;
                }
                else if(fin.peek()=='*')
                {
                    state=in_ml_comment;
                    fin.get(c);
                    continue;
                }
                else
                {
                    fout.put(c);
                }
            }
            else if(c=='"')
            {
                state=in_string;
                fout.put(c);
            }
            else if(c=='\'')
            {
                state=in_char;
                fout.put(c);
            }
            else
            {
                fout.put(c);
            }
        }
        else if(state==in_string)
        {
            fout.put(c);
            if(c=='\\')
            {
                if(fin.get(c)) fout.put(c);
            }
            else if(c=='"')
            {
                state=normal;
            }
        }
        else if(state==in_char)
        {
            fout.put(c);
            if(c=='\\')
            {
                if(fin.get(c)) fout.put(c);
            }
            else if(c=='\'')
            {
                state=normal;
            }
        }
        else if(state==in_sl_comment)
        {
            if(c=='\n')
            {
                fout.put('\n');
                state=normal;
            }
        }
        else if(state==in_ml_comment)
        {
            if(c=='*' && fin.peek()=='/')
            {
                fin.get(c);
                state=normal;
            }
        }
    }
    fin.close();
    fout.close();
    cout<<"Comment Removed ,Check output.c"<<endl;
    return 0;
}
