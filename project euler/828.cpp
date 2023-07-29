#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1005075251;

int main(){
	ifstream in("p828_number_challenges.txt");
	string line;
	lli three = 3;
	lli ans = 0;
	while(getline(in, line)){
		int n = 6;
		vector<int> nums(n);
		int target;
		sscanf(line.c_str(), "%d:%d,%d,%d,%d,%d,%d", &target, &nums[0], &nums[1], &nums[2], &nums[3], &nums[4], &nums[5]);
		vector<bool> used(n);
		stack<lli> st;
		int mini = 1e9;
		function<void(int, int, int)> go = [&](int pushes, int pops, int sum){
			if(st.size() == 1 && st.top() == target) mini = min(mini, sum);
			if(pushes < n){
				for(int i = 0; i < n; ++i){
					if(!used[i]){
						used[i] = true;
						st.push(nums[i]);
						go(pushes + 1, pops, sum + nums[i]);
						st.pop();
						used[i] = false;
					}
				}
			}
			if(st.size() > 1 && pops < n-1){
				lli b = st.top(); st.pop();
				lli a = st.top(); st.pop();
				if(a <= b) {st.push(a+b); go(pushes, pops + 1, sum); st.pop();}
				if(a-b > 0) {st.push(a-b); go(pushes, pops + 1, sum); st.pop();}
				if(a <= b) {st.push(a*b); go(pushes, pops + 1, sum); st.pop();}
				if(b != 0 && a%b == 0) {st.push(a/b); go(pushes, pops + 1, sum); st.pop();}
				st.push(a);
				st.push(b);
			}
		};
		go(0, 0, 0);
		if(mini == 1e9) mini = 0;
		cout << mini << "\n";
		ans = (ans + three*mini) % mod;
		three = three * 3 % mod;
	}
	cout << ans << "\n";
	return 0;
}