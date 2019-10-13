#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<bool> values(n);
    for(int i = 0; i < n; ++i){
        char c;
        cin >> c;
        if(c == 'T') values[i] = true;
        else values[i] = false;
    }
    stack<bool> res;
    char c;
    while(cin >> c){
        if('A' <= c && c <= 'Z'){
            res.push(values[c - 'A']);
        }else if(c == '+'){
            bool v1 = res.top(); res.pop();
            bool v2 = res.top(); res.pop();
            res.push(v1 | v2);
        }else if(c == '*'){
            bool v1 = res.top(); res.pop();
            bool v2 = res.top(); res.pop();
            res.push(v1 & v2);
        }else if(c == '-'){
            bool v1 = res.top(); res.pop();
            res.push(!v1);
        }
    }
    bool ans = res.top();
    if(ans) cout << "T\n";
    else cout << "F\n";
    return 0;
}