#include <bits/stdc++.h>
using namespace std;

struct query{
	int l, r, index, S;
	bool operator<(const query & q) const{
		int c_o = l / S, c_q = q.l / S;
		if(c_o == c_q)
			return r < q.r;
		return c_o < c_q;
	}
};

vector<int> MO(const vector<int> & A, vector<query> & queries){
	vector<int> freq(int(1e5) + 1), cnt_freq((int)1e5 + 1);
	cnt_freq[0] = 1;
	vector<int> resp(queries.size());
	int ans = 0;
	int cnt_max = 1;
	sort(queries.begin(), queries.end());
	int prevL = 0, prevR = -1;
	int i, j;
	for(const query & q : queries){
		for(i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
			cnt_freq[freq[A[i]]]--;
			freq[A[i]]--;
			if(freq[A[i]]) cnt_freq[freq[A[i]]]++;
			if(freq[A[i]]+1 == ans){
				if(cnt_max == 1){
					ans = freq[A[i]];
					cnt_max = cnt_freq[freq[A[i]]];
				}else{
					cnt_max--;
				}
			}
		}
		for(i = prevL - 1; i >= q.l; --i){
			if(freq[A[i]]) cnt_freq[freq[A[i]]]--;
			freq[A[i]]++;
			cnt_freq[freq[A[i]]]++;
			if(freq[A[i]] > ans){
				ans = freq[A[i]];
				cnt_max = 1;
			}else if(freq[A[i]] == ans){
				cnt_max++;
			}
		}
		for(i = max(prevR + 1, q.l); i <= q.r; ++i){
			if(freq[A[i]]) cnt_freq[freq[A[i]]]--;
			freq[A[i]]++;
			cnt_freq[freq[A[i]]]++;
			if(freq[A[i]] > ans){
				ans = freq[A[i]];
				cnt_max = 1;
			}else if(freq[A[i]] == ans){
				cnt_max++;
			}
		}
		for(i = prevR; i >= q.r + 1; --i){
			cnt_freq[freq[A[i]]]--;
			freq[A[i]]--;
			if(freq[A[i]]) cnt_freq[freq[A[i]]]++;
			if(freq[A[i]]+1 == ans){
				if(cnt_max == 1){
					ans = freq[A[i]];
					cnt_max = cnt_freq[freq[A[i]]];
				}else{
					cnt_max--;
				}
			}
		}
		prevL = q.l, prevR = q.r;
		resp[q.index] = ans;
	}
	return resp;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	int S = sqrt(n);
	vector<query> queries(q);
	for(int i = 0; i < q; ++i){
		cin >> queries[i].l >> queries[i].r;
		queries[i].S = S;
		queries[i].index = i;
	}
	auto ans = MO(a, queries);
	for(int a : ans){
		cout << a << "\n";
	}
	return 0;
}