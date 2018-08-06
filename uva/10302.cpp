#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

int main()
{
    ios_base::sync_with_stdio(0);
    ull n;
    while(cin >> n){
        ull tmp;
        if(n%2==0) tmp = (n/2)*(n+1);
        else tmp = n*((n+1)/2);
        cout << tmp*tmp << endl;
    }
    return 0;
}
