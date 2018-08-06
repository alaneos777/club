#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b){
    while(b!=0){
        int res = a%b;
        a = b;
        b = res;
    }
    return a;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int a, b, n;
    cin >> a >> b;
    cin >> n;
    int k = gcd(a, b);
    map<int, int> factores;
    for(int j=1;j<=sqrt(k);j++){
        if(k%j == 0){
            factores[j] = 1;
            factores[k/j] = 1;
        }
    }
    //for(pair<int,int> f:factores) cout << f.first << endl;
    for(int i=0;i<n;i++){
        int low, high;
        cin >> low >> high;
        int ans = -1;
        for(map<int,int>::reverse_iterator it=factores.rbegin(); it!=factores.rend(); ++it){
            if(low <= it->first && it->first <= high){
                ans = it->first;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
