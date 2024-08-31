#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    lli n;
    cin >> n;
    lli i = 1;
    vector<lli> a;
    while(i <= n){
        lli ni = n/i, u = n/ni;
        a.push_back(u);
        i = u+1;
    }
    cout << a.size() << "\n";
    for(lli ai : a){
        cout << ai << " ";
    }
    cout << "\n";
    return 0;
}