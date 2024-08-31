#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

const int M = 800;

vector<int> operator*(const vector<int>& a, const vector<int>& b){
    int m = a.size(), n = b.size();
    vector<int> c(m + n - 1);
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            c[i+j] += (lli)a[i]*b[j] % mod;
            if(c[i+j] >= mod) c[i+j] -= mod;
        }
    }
    return c;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int off = 9;
    vector<int> A(19), B(19);
    for(int i = 1; i <= 9; ++i){
        for(int j = 1; j <= 9; ++j){
            if(i != j){
                A[i-j+off]++;
            }
        }
    }
    for(int i = 0; i <= 9; ++i){
        for(int j = 0; j <= 9; ++j){
            if(i != j){
                B[i-j+off]++;
            }
        }
    }
    vector<int> answers(M+1);
    for(int n = 1; n <= M; ++n){
        answers[n] = A[off];
        A = A * B;
        off += 9;
    }
    int q;
    cin >> q;
    while(q--){
        int n;
        cin >> n;
        cout << answers[n] << "\n";
    }
    return 0;
}