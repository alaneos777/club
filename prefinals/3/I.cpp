#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	if(n == 1){
		cout << "1\n";
	}else if(n <= 8 || n % 2 == 0){
		cout << "-1\n";
	}else{
		n = (n - 9) / 2;
		vector<lli> base = {3, 5, 7, 9, 11, 15, 35, 45, 231};
		while(n--){
			lli x = (base.back() - 1) / 2;
			base.pop_back();
			if(x % 2 == 1){
				base.push_back((2*x+3)*(x+1)-1);
				base.push_back((2*x+3)*(2*x+1)*(x+2));
			}else{
				base.push_back((2*x+3)*(x+1));
				base.push_back((2*x+3)*(2*x+1)*(x+1));
			}
			base.push_back(2*x+3);
		}
		for(int i = 0; i < base.size(); ++i){
			if(i) cout << " ";
			cout << base[i];
		}
		cout << "\n";
	}
	return 0;
}