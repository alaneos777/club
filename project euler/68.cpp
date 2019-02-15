#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	lli ans = -1;
	vector<int> A(10);
	for(int i = 0; i < 10; ++i){
		A[i] = i+1;
	}
	do{
		vector<tuple<int, int, int>> lines(5);
		lines[0] = {A[0], A[5], A[9]};
		lines[1] = {A[4], A[9], A[8]};
		lines[2] = {A[3], A[8], A[7]};
		lines[3] = {A[2], A[7], A[6]};
		lines[4] = {A[1], A[6], A[5]};
		set<int> S;
		S.insert(A[0]+A[5]+A[9]);
		S.insert(A[1]+A[6]+A[5]);
		S.insert(A[2]+A[7]+A[6]);
		S.insert(A[3]+A[8]+A[7]);
		S.insert(A[4]+A[9]+A[8]);
		if(S.size() == 1){
			rotate(lines.begin(), min_element(lines.begin(), lines.end()), lines.end());
			string str;
			for(auto & line : lines){
				str += to_string(get<0>(line)) + to_string(get<1>(line)) + to_string(get<2>(line));
			}
			if(str.size() == 16){
				lli n = stoll(str);
				if(ans == -1 || n > ans){
					ans = n;
				}
			}
		}
	}while(next_permutation(A.begin(), A.end()));
	cout << ans << "\n";
	return 0;
}