#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int costPerDigit[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
const int M = 1e6;

int getCost(int n){
    int ans = 0;
    while(n){
        ans += costPerDigit[n % 10];
        n /= 10;
    }
    return ans;
}

int main(){
    vector<vector<int>> divs(M+1);
    for(int i = 1; i <= M; ++i){
        for(int j = i; j <= M; j += i){
            divs[j].push_back(i);
        }
    }
    
    vector<int> cost_m(M+1), cost(M+1);
    int ans = 0;
    for(int n = 1; n <= M; ++n){
        cost_m[n] = getCost(n);
        for(int i : divs[n]){
            cost_m[n] = min(cost_m[n], cost_m[n/i] + getCost(i) + 2);
        }
    }
    for(int n = 1; n <= M; ++n){
        cost[n] = cost_m[n];
        for(int i = 1; 2*i <= n; ++i){
            cost[n] = min(cost[n], cost[n-i] + cost_m[i] + 2);
        }
        ans += cost[n];
    }
    cout << ans << "\n";
    return 0;
}