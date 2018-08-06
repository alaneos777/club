#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli subnum(lli n, int start, int count){
	stringstream ss;
	ss << n;
	string str = ss.str().substr(start, count);
	lli ans;
	stringstream(str) >> ans;
	return ans;
}

int main(){
	vector<lli> digits;
	for(int i = 0; i <= 9; i++){
		digits.push_back(i);
	}
	vector<lli> divs = {2, 3, 5, 7, 11, 13, 17};
	lli sum = 0;
	do{
		if(digits[0] != 0){
			lli num = 0;
			for(lli d : digits){
				num = num * 10 + d;
			}
			bool test = true;
			for(int i = 0; i < divs.size(); i++){
				if(subnum(num, i + 1, 3) % divs[i] != 0){
					test = false;
					break;
				}
			}
			if(test){
				sum += num;
				cout << num << "\n";
			}
		}
	}while(next_permutation(digits.begin(), digits.end()));
	cout << "\n" << sum << "\n";
	return 0;
}