#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<lli> F;

const lli limit = 1e18;
const lli mod = 1e8;

lli gauss(lli a, lli b, lli c){
	if(limit < a) return 0;
	b = min(b, limit);
	lli ans = ((a + b - 2*c) % (2*mod)) * ((b - a + 1) % (2*mod)) % (2*mod);
	if(ans < 0) ans += (2*mod);
	ans /= 2;
	ans %= mod;
	return ans;
}

lli sum_group(int g){
	if(g <= 3) return 0;
	if(g == 4) return 1;
	if(g == 5) return 3;
	lli start = F[g];
	lli acum = F[g];
	lli end = F[g+1] - 1;
	lli a = 0;
	lli sum = 0;
	while(true){
		lli b = (F[g] - 1) / 2;
		sum += gauss(start, start + b - a, start - a);
		if(sum >= mod) sum -= mod;
		if(start == end) break;
		start += b - a + 1;
		g -= 2;
		acum += F[g];
		a = start - acum;
	}
	return sum;
}

int main(){
	lli f0 = 0, f1 = 1, fi;
	while(f0 <= limit){
		F.push_back(f0);
		fi = f0 + f1, f0 = f1, f1 = fi;
	}
	F.push_back(f0);

	lli ans = 0;
	for(int g = 2; g < F.size()-1; ++g){
		ans += sum_group(g);
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}