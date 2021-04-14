#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	lli ans = 0;
	vector<int> part_max, digs_max;
	vector<int> digits(10);
	iota(digits.begin(), digits.end(), 0);
	swap(digits[0], digits[1]);
	do{
		int x = 0;
		for(int i = 0; i <= 1; ++i){
			x = x*10 + digits[i];
			if(x % 3 != 0) continue;
			if(x > 49) continue;
			function<vector<vector<int>>(int, int)> dp = [&](int pos, int k){
				vector<vector<int>> ans = {{}};
				if(pos == 10) return ans;
				if(k == 1){
					int z = 0;
					for(int j = pos; j < 10; ++j){
						z = z*10 + digits[j];
					}
					return vector<vector<int>>{{z}};
				}
				ans = {};
				int curr = 0;
				for(int j = pos; j < 10; ++j){
					curr = curr*10 + digits[j];
					if(j+1 < 10 && digits[j+1] == 0) continue;
					for(auto& y : dp(j+1, k-1)){
						y.push_back(curr);
						ans.push_back(y);
					}
				}
				return ans;
			};
			if(digits[i+1] == 0) continue;
			for(const auto& part : dp(i+1, 2)){
				string str;
				for(lli y : part){
					str += to_string(x*y);
				}
				set<char> st(str.begin(), str.end());
				if(str[0] != '0' && str.size() == 10 && st.size() == 10){
					lli n = stoll(str);
					if(n > ans){
						ans = n;
						digs_max = digits;
						part_max = part;
						part_max.push_back(x);
						reverse(part_max.begin(), part_max.end());
					}
				}
			}
		}
	}while(next_permutation(digits.begin(), digits.end()));
	cout << ans << "\n";
	for(int d : digs_max) cout << d; cout << "\n";
	for(int p : part_max){
		cout << p << " ";
	}
	return 0;
}