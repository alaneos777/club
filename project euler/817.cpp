#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int p = 1e9+7;
const int L = 1e5;

bitset<L> M;

int main(){
	int cnt = 0;
	lli sum = 0;
	__int128_t m2 = 0;
	for(lli m = 1; cnt < L; ++m){
		m2 += 2*m-1;
		__int128_t sq = m2;
		while(sq){
			int x = sq%p;
			sq /= p;
			if(p-L <= x && x <= p-1 && !M[x+L-p]){
				sum += m;
				cnt++;
				M[x+L-p] = true;
			}
		}
	}
	cout << sum << "\n";
	return 0;
}