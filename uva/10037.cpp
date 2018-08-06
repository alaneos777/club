#include <bits/stdc++.h>
using namespace std;

void process(vector<int> & times, int n, stringstream & ss, int & total){
	if(n == 1){
		total += times[0];
		ss << times[0] << "\n";
	}else if(n == 2){
		total += times[1];
		ss << times[0] << " " << times[1] << "\n";
	}else if(n == 3){
		total += times[0] + times[1] + times[2];
		ss << times[0] << " " << times[1] << "\n";
		ss << times[0] << "\n";
		ss << times[0] << " " << times[2] << "\n";
	}else{
		int A = times[0], B = times[1]; //the two fastest, A <= B
		int c = times[n - 1], d = times[n - 2]; //the two slowest, c >= d
		int case1 = c + A + d + A; //A takes both c and d to the other side, and returns
		int case2 = B + A + c + B; //A and B go to the other side, A returns, c and d go to the other side, B returns
		if(case1 < case2){
			ss << A << " " << c << "\n";
			ss << A << "\n";
			ss << A << " " << d << "\n";
			ss << A << "\n";
			total += case1;
		}else{
			ss << A << " " << B << "\n";
			ss << A << "\n";
			ss << d << " " << c << "\n";
			ss << B << "\n";
			total += case2;
		}
		process(times, n - 2, ss, total);
	}
}

int main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> times(n);
		for(int i = 0; i < n; i++){
			cin >> times[i];
		}
		sort(times.begin(), times.end());
		int total = 0;
		stringstream ss;
		process(times, n, ss, total);
		cout << total << "\n" << ss.str();
		if(t > 0) cout << "\n";
	}
	return 0;
}