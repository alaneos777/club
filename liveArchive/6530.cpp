#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, g, s, r;
	while(cin >> n >> g){
		int points = 0;
		vector<int> difs;
		for(int i = 0; i < n; ++i){
			cin >> s >> r;
			if(s > r){
				points += 3;
			}else if(s == r){
				points += 1;
				difs.push_back(0);
			}else{
				difs.push_back(r - s);
			}
		}
		sort(difs.begin(), difs.end());
		for(int i = 0; i < difs.size(); ++i){
			if(difs[i] == 0){
				if(g > 0){
					--g;
					points += 2;
				}
			}else if(difs[i] <= g){
				g -= difs[i];
				points += 1;
				if(g > 0){
					--g;
					points += 2;
				}
			}
		}
		cout << points << "\n";
	}
	return 0;
}