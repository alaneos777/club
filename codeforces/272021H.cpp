#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli M = 1ll << 40;

inline lli f(lli s){
	return (s + (s >> 20) + 12345) & (M-1);
}

const lli s0 = 1611516670ll;

int main(){
	cout << "#include <bits/stdc++.h>\n";
	cout << "using namespace std;\n";
	cout << "using lli = long long int;\n";

	lli t = f(s0);
	lli h = f(f(s0));
	while(t != h){
		t = f(t);
		h = f(f(h));
	}
	int len_start = 0;
	t = s0;
	while(t != h){
		t = f(t);
		h = f(h);
		len_start++;
	}
	int len_period = 1;
	h = f(t);
	while(t != h){
		h = f(h);
		len_period++;
	}

	cout << "const int len_start = " << len_start << ";\n";
	cout << "const int len_period = " << len_period << ";\n\n";

	int block_step = 1<<20;

	lli s = s0;
	lli sum_start = 1 - (s & 1);
	vector<lli> values_start;
	cout << "const vector<int> blocks_start = {0";
	int sz = 1;
	while(sz < len_start){
		s = f(s);
		sum_start += 1 - (s & 1);
		sz++;
		if((sz & (block_step - 1)) == 0){
			values_start.push_back(s);
			cout << ", " << sum_start;
		}
	}
	cout << "};\n";
	cout << "const vector<lli> values_start = {-1";
	for(lli x : values_start){
		cout << ", " << x;
	}
	cout << "};\n\n";

	s = f(s);
	lli sum_period = 1 - (s & 1);
	vector<lli> values_period;
	cout << "const vector<int> blocks_period = {0";
	sz = 1;
	while(sz < len_period){
		s = f(s);
		sum_period += 1 - (s & 1);
		sz++;
		if((sz & (block_step - 1)) == 0){
			values_period.push_back(s);
			cout << ", " << sum_period;
		}
	}
	cout << "};\n";
	cout << "const vector<lli> values_period = {-1";
	for(lli x : values_period){
		cout << ", " << x;
	}
	cout << "};\n\n";

	cout << "const int sum_start = " << sum_start << ";\n";
	cout << "const int sum_period = " << sum_period << ";\n";
	cout << "const int block_step = " << block_step << ";\n\n";

	return 0;
}