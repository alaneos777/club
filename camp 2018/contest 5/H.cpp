#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >

using namespace std;

const int MAXN = 105;

int cur;
int tam[MAXN];
int num[MAXN];
int row[MAXN];
int grundy[MAXN][MAXN];
int grundyFila[MAXN][MAXN];

int solve(int ini, int fin, int n) {
	if(grundy[ini][fin] != -1) return grundy[ini][fin];

	vi mex(MAXN, 0);
	for(int i=ini;i<=fin;i++) {
		int ans = 0;
		for(int j=ini;j<=fin;j++) {
			while(j <= fin && num[j] <= num[i]) j++;
			if(j > fin) break;
			int h = j;
			while(j <= fin && num[j] > num[i]) j++;
			j--;
			ans ^= solve(h, j, n);
		}

		mex[ans] = 1;
		if(ini == 0 && fin == n - 1)
			grundyFila[cur][i] = ans;
	}

	int res = 0;
	forn(i, MAXN)
		if(!mex[i]) {
			res = i;
			break;
		}
	
	return grundy[ini][fin] = res;
}

int go(int n) {
	forn(i, n)
		forn(j, n)
			grundy[i][j] = -1;
	forn(i, n) grundy[i][i] = 1;
	return solve(0, n - 1, n);
}

// чтение и перевод это будет пустой тратой времени
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int k,n;
	cin>>k;

	int ans = 0;
	forn(h, k) {
		cin>>n;
		tam[h] = n;
		forn(i, n) cin>>num[i];
		cur = h;
		row[h] = go(n);
		ans ^= row[h];
	}

	if(ans > 0) {
		cout<<"G"<<endl;
		forn(i, k) {
			int res = (ans ^ row[i]);
			forn(j, tam[i]) {
				if((res ^ grundyFila[i][j]) == 0) {
					cout<<i+1<<" "<<j+1<<endl;
					return 0;
				}
			}
		}
	} else {
		cout<<"S"<<endl;
	}
	return 0;
}
