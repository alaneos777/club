#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string linea;
    while(getline(cin, linea)){
        stringstream ss(linea);
        int f[5];
        int s[5];
        for(int i=0;i<5;i++){
            ss >> f[i];
        }
        getline(cin, linea);
        stringstream ss2(linea);
        for(int i=0;i<5;i++){
            ss2 >> s[i];
        }
        bool pass = true;
        for(int i=0;i<5;i++){
            if(f[i]+s[i]!=1){
                pass = false;
                break;
            }
        }
        if(pass){
            cout << "Y\n";
        }else{
            cout << "N\n";
        }
    }
    return 0;
}
