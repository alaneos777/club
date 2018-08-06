#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

int main()
{
    int t, a, b, k, maximo=100000;
    vector<ull> suma(maximo+1, 0), numero(maximo+1, 0);
    for(int i=1;i<=maximo;i++){
        for(int j=i;j<=maximo;j+=i){
            suma[j] += i;
            numero[j]++;
        }
    }
    cin >> t;
    for(int i=0;i<t;i++){
        cin >> a >> b >> k;
        int inf = a+k-((a-1)%k)-1, sup=b-(b%k);
        ull ans1=0, ans2=0;
        for(int j=inf;j<=sup;j+=k){
            ans1 += suma[j], ans2 += numero[j];
        }
        cout << ans2 << " " << ans1 << "\n";
    }
    return 0;
}
