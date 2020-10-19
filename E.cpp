#include <bits/stdc++.h>
using namespace std;

string prog[2];
int j = 0, pos = 0;
vector<int> arr;

pair<int, int> eval(int i, bool rev, bool ignore, bool reset){
	if(reset) j = 0, pos = 0;
	if(prog[i][j] == 'c'){
		j += 7;
		auto lst1 = eval(i, rev, false, false);
		assert(prog[i][j] == ',');
		++j;
		auto lst2 = eval(i, rev, false, false);
		assert(prog[i][j] == ')');
		++j;
		assert(lst1.second == lst2.first);
		return {lst1.first, lst2.second};
	}else if(prog[i][j] == 's' && prog[i][j+1] == 'h'){
		j += 8;
		auto lst = eval(i, rev, true, false);
		assert(prog[i][j] == ')');
		++j;
		if(rev){
			if(!ignore) sort(arr.begin() + lst.first, arr.begin() + lst.second, greater<int>());
		}else{
			if(!ignore) sort(arr.begin() + lst.first, arr.begin() + lst.second);
		}
		return lst;
	}else if(prog[i][j] == 's' && prog[i][j+1] == 'o'){
		j += 7;
		auto lst = eval(i, rev, true, false);
		assert(prog[i][j] == ')');
		++j;
		if(!ignore) sort(arr.begin() + lst.first, arr.begin() + lst.second);
		return lst;
	}else if(prog[i][j] == '['){
		++j;
		int start = pos;
		int acum = 0;
		while(prog[i][j] != ']'){
			if(isdigit(prog[i][j])) acum = acum * 10 + (prog[i][j] - '0');
			else{
				arr.push_back(acum);
				++pos;
				acum = 0;
			}
			++j;
		}
		++j;
		arr.push_back(acum);
		++pos;
		return {start, pos};
	}else{
		assert(0);
		return {0, 0};
	}
}

vector<int> eval(int i, bool rev){
	arr = vector<int>();
	auto lst = eval(i, rev, false, true);
	assert(lst.first == 0);
	vector<int> ans(arr.begin(), arr.begin() + lst.second);
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> prog[0] >> prog[1];
	auto x = eval(0, false), y = eval(1, false);
	auto z = eval(0, true), w = eval(1, true);
	if(x == y && z == w){
		cout << "equal\n";
	}else{
		cout << "not equal\n";
	}
	return 0;
}