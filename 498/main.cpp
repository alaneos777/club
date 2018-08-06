#include <bits/stdc++.h>

using namespace std;

typedef long long int ull;

int main()
{
    ios_base::sync_with_stdio(0);
    string a, b;
    ull m, n;
    while(getline(cin, a) && getline(cin, b)){
        vector<ull> coeficientes, valores;
        stringstream ss1(a), ss2(b);
        while(ss1 >> m) coeficientes.push_back(m);
        while(ss2 >> n) valores.push_back(n);
        bool flag = true;
        for(ull valor:valores){
            if(flag){
                flag = false;
            }else{
                cout << " ";
            }
            ull r = 0;
            for(ull coeficiente:coeficientes){
                r = r*valor + coeficiente;
            }
            cout << r;
        }
        cout << "\n";
    }
    return 0;
}
