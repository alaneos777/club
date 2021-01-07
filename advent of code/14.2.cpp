#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	string name, eq, msk;
	string mask;
	map<lli, lli> mem;
	while(cin >> name >> eq >> msk){
		if(name == "mask"){
			mask = msk;
			reverse(mask.begin(), mask.end());
			continue;
		}
		name = name.substr(4);
		int pos = name.find(']');
		name = name.substr(0, pos);
		lli dir = stoi(name);
		lli val = stoll(msk);
		for(int i = 0; i < 36; ++i){
			if(mask[i] == '1'){
				dir |= (1ll << i);
			}
		}
		function<void(int, lli)> f = [&](int pos, lli acum){
			if(pos == 36){
				mem[acum] = val;
			}else{
				if(mask[pos] == 'X'){
					f(pos + 1, acum | (1ll << pos));
					f(pos + 1, acum & ~(1ll << pos));
				}else{
					f(pos + 1, acum);
				}
			}
		};
		f(0, dir);
	}
	lli ans = 0;
	for(auto par : mem){
		ans += par.second;
	}
	cout << ans << endl;
	return 0;
}