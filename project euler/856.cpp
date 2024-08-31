#include <bits/stdc++.h>
using namespace std;

const int power[] = {1, 14, 196, 2744};

int get(int msk, int i){
	return msk/power[i]%14;
}

int put(int msk, int i, int x){
	return msk - get(msk, i)*power[i] + x*power[i];
}

vector<vector<double>> mem(10, vector<double>(38416, -1));

double f(int r, int last){
	int cnt = 0;
	for(int i = 1; i <= 4; ++i){
		cnt += i*get(r, i-1);
	}
	if(cnt == 0) return 0;
	double& ans = mem[last+1][r];
	if(ans != -1) return ans;
	ans = 0;
	for(int i = 1; i <= 4; ++i){
		if(get(r, i-1) == 0) continue;
		double p = (double)i*get(r, i-1)/cnt;
		int nxt_r = put(r, i-1, get(r, i-1) - 1);
		if(i >= 2) nxt_r = put(nxt_r, i-2, get(nxt_r, i-2) + 1);
		if(i == last-1){
			ans += (1 + f(nxt_r, i) * (1 - 1.0/get(r, i-1))) * p;
		}else{
			ans += (1 + f(nxt_r, i)) * p;
		}
	}
	return ans;
}

int main(){
	cout << fixed << setprecision(8) << f(put(0, 4-1, 13), -1) << "\n";
	return 0;
}