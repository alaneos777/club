#include <bits/stdc++.h>

using namespace std;
typedef long long int ull;

int main()
{
    ios_base::sync_with_stdio(0);
    ull k, n, r;
    while(cin >> k){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string linea;
        getline(cin, linea);
        stringstream ss(linea);
        vector<ull> coef;
        while(ss >> n){
            coef.push_back(n);
        }
        r = 0;
        vector<ull> q(coef.size());
        for(int i=0;i<coef.size();i++){
            r = r*k + coef[i];
            q[i] = r;
        }
        cout << "q(x):";
        for(int i=0;i<q.size()-1;i++){
            cout << " " << q[i];
        }
        cout << "\nr = " << r << "\n\n";
    }
    return 0;
}
