#include <iostream>
#include <vector>
using namespace std;
typedef long long int lli;

inline lli comb(lli r){
	return r * (r - 1) / 2;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	lli n, m;
	cin >> n >> m;
	lli g = n / m;
	lli r = n % m;
	cout << (r * comb(g + 1) + (m - r) * comb(g)) << " " << comb(n - m + 1) << "\n";
	return 0;
}