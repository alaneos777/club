#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
    cin >> n >> k;
    vector<bool> valid(n+1, true);
    for(int i = 1; i <= k; ++i){
        int ai;
        cin >> ai;
        valid[ai] = false;
    }
    int valids = 0;
    for(int i = 1; i <= n; ++i){
        valids += valid[i];
    }
    vector<pair<int, int>> pairs;
    int pos = 1;
    int total = 0;
    while(pos <= n){
        if(valid[pos]){
            int start = pos;
            while(pos <= n && valid[pos]){
                pos++;
            }
            pairs.emplace_back(start, pos-1);
            total ^= (pos - start);
        }else{
            pos++;
        }
    }
    int ans = 1e9;
    for(auto par : pairs){
        int l, r;
        tie(l, r) = par;
        //cout << "(" << l << ", " << r << ")\n";
        for(int sz = 1; sz <= r-l+1; ++sz){
            for(int i = l, j = i+sz-1; i <= r && j <= r; ++i, ++j){
                int sz1 = i - l; //[l, i-1]
                int sz2 = j - i + 1; //[i, j]
                int sz3 = r - j; //[j+1, r]
                //cout << sz1 << " " << sz2 << "[" << i << ", " << j << "] " << sz3 << "\n";
                assert(sz1>=0 && sz2>=0 && sz3>=0);
                int sum = sz1 ^ sz3 ^ total ^ (r - l + 1);
                if(sum == 0 && sz2 != valids){
                    ans = min(ans, sz2);
                }
            }
        }
    }
    if(ans == 1e9){
        cout << "-1\n";
    }else{
        cout << ans << "\n";
    }
    return 0;
}