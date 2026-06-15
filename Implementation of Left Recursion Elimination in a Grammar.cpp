#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>> n;

    string prod[50];
    string result[100];
    int k = 0;

    for(int i = 0; i < n; i++)
    {
        cin>> prod[i];
    }


    cout<<endl<<"Output : "<<endl;
    for(int i = 0;i < n;i++)
    {
        char A = prod[i][0];

        int pos1 = prod[i].find("->");
        string rhs = prod[i].substr(pos1 + 2);

        int pos2 = rhs.find("|");

        if(pos2 == string::npos)
        {
            result[k++] = prod[i];
            continue;
        }

        string p1 = rhs.substr(0, pos2);
        string p2 = rhs.substr(pos2 + 1);

        string alpha, beta;

        if(p1[0] == A)
        {
            alpha = p1.substr(1);
            beta = p2;

            result[k++] = string(1, A) + "->" + beta + string(1, A) + "'";
            result[k++] = string(1, A) + "'" + "->" + alpha + string(1, A) + "'|e";
        }
        else if(p2[0] == A)
        {
            alpha = p2.substr(1);
            beta = p1;

            result[k++] = string(1, A) + "->" + beta + string(1, A) + "'";
            result[k++] = string(1, A) + "'" + "->" + alpha + string(1, A) + "'|e";
        }
        else
        {
            result[k++] = prod[i];
        }
    }

    for(int i = 0;i < k;i++)
    {
        cout << result[i] << endl;
    }

    return 0;
}
