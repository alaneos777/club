#include <bits/stdc++.h>
using namespace std;
using lli = uint64_t;

const lli limit = 1e12;

int main(){
	set<lli> conj;
	conj.insert(1);
	for(lli b = 2; ; ++b){
		lli acum = 1 + b + b*b;
		if(acum >= limit) break;
		while(acum < limit){
			conj.insert(acum);
			acum = acum*b + 1;
		}
	}
	lli sum = 0;
	for(lli n : conj){
		sum += n;
	}
	cout << conj.size() << " " << sum << "\n";
	return 0;
}
