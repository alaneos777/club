#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SegmentTreeEst{
	int size;
	vector<T> sum, lazy;

	SegmentTreeEst(int n): size(n){
		int h = ceil(log2(n));
		sum.resize((1 << (h + 1)) - 1);
		lazy.resize((1 << (h + 1)) - 1, -1);
	}
 
	void propagate(int pos, int l, int r, T dif){
		sum[pos] = (r - l + 1) * dif;
		if(l != r){
			lazy[2*pos+1] = dif;
			lazy[2*pos+2] = dif;
		}
	}
 
	T sum_query_rec(int start, int end, int pos, int l, int r){
		if(lazy[pos] != -1){
			propagate(pos, l, r, lazy[pos]);
			lazy[pos] = -1;
		}
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum[pos];
		else{
			int half = l + ((r - l) >> 1);
			return sum_query_rec(start, end, 2*pos+1, l, half) + sum_query_rec(start, end, 2*pos+2, half+1, r);
		}
	}

	T sum_query(int start, int end){
		return sum_query_rec(start, end, 0, 0, size - 1);
	}
 
	void update_range_rec(int start, int end, int pos, int l, int r, T dif){
		if(lazy[pos] != -1){
			propagate(pos, l, r, lazy[pos]);
			lazy[pos] = -1;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(pos, l, r, dif);
		else{
			int half = l + ((r - l) >> 1);
			update_range_rec(start, end, 2*pos+1, l, half, dif);
			update_range_rec(start, end, 2*pos+2, half+1, r, dif);
			sum[pos] = sum[2*pos+1] + sum[2*pos+2];
		}
	}

	void update_range(int start, int end, T dif){
		update_range_rec(start, end, 0, 0, size - 1, dif);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, l, r, k;
	cin >> n >> q;
	string s;
	cin >> s;
	vector<SegmentTreeEst<int>> st(26, SegmentTreeEst<int>(n));
	for(int i = 0; i < n; ++i){
		st[s[i] - 'a'].update_range(i, i, 1);
	}
	while(q--){
		cin >> l >> r >> k;
		--l, --r;
		vector<int> freq(26);
		for(int i = 0; i < 26; ++i){
			freq[i] = st[i].sum_query(l, r);
			st[i].update_range(l, r, 0);
		}
		int start = l;
		if(k == 1){
			for(int i = 0; i < 26; ++i){
				if(freq[i] > 0){
					st[i].update_range(start, start + freq[i] - 1, 1);
					start += freq[i];
				}
			}
		}else{
			for(int i = 25; i >= 0; --i){
				if(freq[i] > 0){
					st[i].update_range(start, start + freq[i] - 1, 1);
					start += freq[i];
				}
			}
		}
	}
	string ans(n, ' ');
	for(int j = 0; j < n; ++j){
		for(int i = 0; i < 26; ++i){
			if(st[i].sum_query(j, j) == 1){
				ans[j] = i + 'a';
				break;
			}
		}
	}
	cout << ans << "\n";
	return 0;
}