#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

struct pt{
    int x, y;
};

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli det(vector<vector<lli>> & A){
	int n = A.size(), i = 0, j = 0;
    lli ans = 1;
	while(i < n && j < n){
		if(A[i][j] == 0){
			for(int k = i + 1; k < n; k++){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
                    ans = (mod - ans) % mod;
					break;
				}
			}
		}
		if(A[i][j] != 0){
			lli inv_mult = power(A[i][j], mod - 2);
			if(A[i][j] != 1){
                ans = ans * A[i][j] % mod;
				for(int l = 0; l < n; ++l){
					A[i][l] = A[i][l] * inv_mult % mod;
				}
			}
			for(int k = 0; k < n; k++){
				if(k != i && A[k][j] != 0){
					lli inv_adit = (mod - A[k][j]) % mod;
					for(int l = 0; l < n; ++l){
						A[k][l] += inv_adit * A[i][l] % mod;
						if(A[k][l] >= mod) A[k][l] -= mod;
					}
				}
			}
			i++;
		}
		j++;
	}
    if(i != n) ans = 0;
	return ans;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, d;
	while(cin >> n >> d){
		if(n == 0 && d == 0) break;
        vector<pt> points(n);
        for(pt & p : points){
            cin >> p.x >> p.y;
        }
        vector<vector<int>> D(n, vector<int>(n));
        vector<vector<int>> A(n, vector<int>(n));
        vector<vector<lli>> Q(n-1, vector<lli>(n-1));
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                if((points[i].x - points[j].x)*(points[i].x - points[j].x) + (points[i].y - points[j].y)*(points[i].y - points[j].y) <= d*d){
                    A[i][j] = 1;
                    A[j][i] = 1;
                    D[i][i]++;
                    D[j][j]++;
                }
            }
        }
        for(int i = 0; i < n-1; ++i){
            for(int j = 0; j < n-1; ++j){
                Q[i][j] = D[i][j] - A[i][j];
                if(Q[i][j] < 0) Q[i][j] += mod;
            }
        }
        cout << det(Q) << "\n";
	}
    return 0;
}