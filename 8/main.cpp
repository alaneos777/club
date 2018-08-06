#include <bits/stdc++.h>

using namespace std;

int main()
{
    string cadena;
    set<char> m;
    getline(cin, cadena);
    for(int i=0;i<cadena.size();i++){
        char a = cadena[i];
        m.insert(a);
    }
    cout << (cadena.size()-m.size()+1);
    return 0;
}
