#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int ten[10];
int mem[10][2][100][100];
int color[10][2][100][100];
int curr = 0;
 
int f(int pos, bool canAll, int mod, int sum, const vector<int> & n, int k){
    if(pos == n.size()){
        return mod == 0 && sum == 0;
    }
    int & ans = mem[pos][canAll][mod][sum];
    int & calc = color[pos][canAll][mod][sum];
    if(calc == curr) return ans;
    ans = 0, calc = curr;
    int lim = canAll ? 9 : n[pos];
    for(int d = 0; d <= lim; ++d){
        ans += f(pos+1, canAll | (d < lim), (mod + ten[n.size()-1-pos]*d) % k, (sum + d) % k, n, k);
    }
    return ans;
}
 
int f(int n, int k){
    if(n == 0 || k >= 100) return 1;
    vector<int> d;
    while(n){
        d.push_back(n%10);
        n /= 10;
    }
    reverse(d.begin(), d.end());
    curr++;
    return f(0, false, 0, 0, d, k);
}
 
int main(){
    //ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ten[0] = 1;
    for(int i = 1; i < 10; ++i){
        ten[i] = ten[i-1]*10;
    }
    int t;
    cin >> t;
    for(int i = 1; i <= t; ++i){
        int a, b, k;
        cin >> a >> b >> k;
        cout << "Case " << i << ": " << f(b, k)-f(a-1, k) << "\n";
    }
    return 0;
}