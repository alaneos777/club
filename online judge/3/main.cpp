#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string linea;
    short int paridad = 0;
    while(getline(cin, linea)){
        if(linea == "") break;
        for(int i=0;i<linea.size();i++){
            char actual = linea[i];
            if(actual == '"'){
                if(paridad == 0) cout << "``";
                else if(paridad == 1) cout << "''";
                paridad = (paridad + 1) % 2;
            }else{
                cout << actual;
            }
        }
        cout << "\n";
    }
    return 0;
}
