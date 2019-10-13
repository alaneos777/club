#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, last;
    cin >> n;
    vector<bool> bucket(1000, false);
    for(int i = 0; i < n; ++i){
        int ni;
        cin >> ni;
        bucket[ni] = true;
        last = ni;
    }
    vector<int> ans;
    for(int i = 1; i <= last; ++i){
        if(!bucket[i]) ans.push_back(i);
    }
    if(ans.empty()) cout << "good job\n";
    else{
        for(int ii : ans) cout << ii << "\n";
    }
    return 0;
}