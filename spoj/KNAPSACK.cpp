#include <bits/stdc++.h>
using namespace std;

int ans(int pos, int avaliable, vector<int> & weight, vector<int> & value, vector<vector<int>> & mem){
	if(pos == -1){
		return 0;
	}else{
		if(mem[pos][avaliable] == -1){
			int tmp = ans(pos - 1, avaliable, weight, value, mem);
			if(weight[pos] <= avaliable){
				tmp = max(tmp, ans(pos - 1, avaliable - weight[pos], weight, value, mem) + value[pos]);
			}
			mem[pos][avaliable] = tmp;
		}
		return mem[pos][avaliable];
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	int s, n;
	cin >> s >> n;
	vector<int> weight(n), value(n);
	vector<vector<int>> mem(n, vector<int>(s + 1, -1));
	for(int i = 0; i < n; i++){
		cin >> weight[i] >> value[i];
	}
	cout << ans(n - 1, s, weight, value, mem);
	return 0;
}