#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

const int inf = 1e9;
const int MAXN = 1000001;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int a,b;
	cin>>a>>b;
	if(b == 0) cout<<"Impossible"<<endl;
	else {
		int q = a / b;
		int r = a % b;
		if(a > 0 && b > 0);
		else if(a < 0 && b > 0) {
			if(r != 0) q--, r += b;
		} else if(a < 0 && b < 0) {
		} else if(a > 0 && b < 0){
			if(r != 0)
				q--, r += b;
		}
		cout<<q<<" "<<r<<endl;
	}
	return 0;
}
