#include <bits/stdc++.h>
using namespace std;

struct info{
	int usage = 0, rest = 0, start = 0;

	int avaliable(int time, int duration){
		int ans = 0;
		if(time < start){
			ans = time;
			start = max(start, ans + duration);
		}else{
			int d = usage + rest;
			int n = 1 + (time - start) / d;
			if(d * (n - 1) + start <= time && time <= d * (n - 1) + start + usage - 1){
				ans = d * (n - 1) + start + usage;
			}else{
				ans = time;
			}
			start = max(d * n + start, ans + duration);
		}
		return ans;
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	int n = 10, cycles = 3, total = 0;
	vector<info> jim(n), machines(n);
	for(int i = 0; i < n; i++){
		cin >> jim[i].usage >> jim[i].rest;
	}
	for(int i = 0; i < n; i++){
		cin >> machines[i].usage >> machines[i].rest >> machines[i].start;
	}
	for(int cycle = 0; cycle < cycles; cycle++){
		for(int i = 0; i < n; i++){
			total = machines[i].avaliable(total, jim[i].usage) + jim[i].usage + jim[i].rest;
			//cout << "Ciclo: " << cycle << ", Maquina: " << i << ", Tiempo: " << total << "\n";
		}
	}
	total -= jim[n - 1].rest;
	cout << total;
	return 0;
}