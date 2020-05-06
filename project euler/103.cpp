#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int sum(const vector<int> & a){
	int ans = 0;
	for(int x : a){
		ans += x;
	}
	return ans;
}

bool valid(const vector<int> & a){
	int n = a.size();
	bool valid = true;
	for(int mask = 0; mask < (1 << n); ++mask){
		int sub = mask;
		while(sub > 0){
			int cnt_B = 0, cnt_C = 0;
			int sum_B = 0, sum_C = 0;
			for(int i = 0; i < n; ++i){
				if(!(mask & (1 << i))) continue;
				if(sub & (1 << i)){
					sum_B += a[i];
					cnt_B++;
				}else{
					sum_C += a[i];
					cnt_C++;
				}
			}
			if(cnt_B && cnt_C){
				valid &= ((sum_B != sum_C) & ((!(cnt_B > cnt_C)) | (sum_B > sum_C)));
			}
			if(!valid) break;
			sub = (sub - 1) & mask;
		}
		if(!valid) break;
	}
	return valid;
}

int main(){
	int mini = 0;
	vector<int> ans;
	int l = 20, r = 45;
	for(int a = l; a <= r; ++a){
		for(int b = a+1; b <= r; ++b){
			for(int c = b+1; c <= r; ++c){
				for(int d = c+1; d <= r; ++d){
					for(int e = d+1; e <= r; ++e){
						for(int f = e+1; f <= r; ++f){
							for(int g = f+1; g <= r; ++g){
								vector<int> conj = {a, b, c, d, e, f, g};
								if(valid(conj)){
									if(mini == 0 || sum(conj) < mini){
										mini = sum(conj);
										ans = conj;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for(int x : ans){
		cout << x;
	}
	cout << "\n";
	return 0;
}