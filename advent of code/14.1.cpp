#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	string name, eq, msk;
	string mask;
	map<int, lli> mem;
	while(cin >> name >> eq >> msk){
		if(name == "mask"){
			mask = msk;
			reverse(mask.begin(), mask.end());
			continue;
		}
		name = name.substr(4);
		int pos = name.find(']');
		name = name.substr(0, pos);
		int dir = stoi(name);
		lli val = stoll(msk);
		for(int i = 0; i < 36; ++i){
			if(mask[i] == '1'){
				val |= (1ll << i);
			}else if(mask[i] == '0'){
				val &= ~(1ll << i);
			}
		}
		mem[dir] = val;
	}
	lli ans = 0;
	for(auto par : mem){
		ans += par.second;
	}
	cout << ans << endl;
	return 0;
}