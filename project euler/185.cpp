#include <bits/stdc++.h>
using namespace std;

const int sz = 16;
const vector<string> cads = {
	"5616185650518293",
	"3847439647293047",
	"5855462940810587",
	"9742855507068353",
	"4296849643607543",
	"3174248439465858",
	"4513559094146117",
	"7890971548908067",
	"8157356344118483",
	"2615250744386899",
	"8690095851526254",
	"6375711915077050",
	"6913859173121360",
	"6442889055042768",
	"2321386104303845",
	"2326509471271448",
	"5251583379644322",
	"1748270476758276",
	"4895722652190306",
	"3041631117224635",
	"1841236454324589",
	"2659862637316867"
};

const vector<int> correct = {2, 1, 3, 3, 3, 1, 2, 3, 1, 2, 3, 1, 1, 2, 0, 2, 2, 3, 1, 3, 3, 2};

void getSubsets(int r, int idx, int i, vector<vector<int>> & vec, vector<int> & acum){
	if(idx == r){
		vec.push_back(acum);
	}else if(i < sz){
		acum[idx] = i;
		getSubsets(r, idx + 1, i + 1, vec, acum);
		getSubsets(r, idx, i + 1, vec, acum);
	}
}

auto getSubsets(){
	vector<vector<vector<int>>> conj(4);
	for(int i = 0; i < 4; ++i){
		vector<int> acum(i, -1);
		getSubsets(i, 0, 0, conj[i], acum);
	}
	return conj;
}

const auto options = getSubsets();

string ans(sz, '$');

void dfs(int pos){
	if(pos == cads.size()){
		cout << ans << "\n";
		exit(0);
	}else{
		for(const auto & idxs : options[correct[pos]]){
			bool test = true;
			for(int i : idxs){
				test &= (ans[i] == '$' || ans[i] == cads[pos][i]);
			}
			if(test){
				vector<bool> goBack(sz);
				for(int i : idxs){
					goBack[i] = (ans[i] == '$');
					ans[i] = cads[pos][i];
				}
				test = true;
				for(int j = 0; j < pos; ++j){
					int match = 0;
					for(int i = 0; i < sz; ++i){
						match += (cads[j][i] == ans[i]);
					}
					test &= (match == correct[j]);
				}
				if(test) dfs(pos + 1);
				for(int i : idxs){
					if(goBack[i]) ans[i] = '$';
				}
			}
		}
	}
}

int main(){
	dfs(0);
	return 0;
}