#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct node{
	lli prefMax, suffMax, maxSum, sum;
	node(): prefMax(0), suffMax(0), maxSum(0), sum(0){}
	node(lli a): prefMax(a), suffMax(a), maxSum(a), sum(a){}

	node operator+(const node& b) const{
		node c;
		c.sum = sum + b.sum;
		c.prefMax = max(prefMax, sum + b.prefMax);
		c.suffMax = max(b.suffMax, b.sum + suffMax);
		c.maxSum = max({c.prefMax, c.suffMax, maxSum, b.maxSum, suffMax + b.prefMax});
		return c;
	}
};

struct SegmentTree{
	int N;
	vector<node> ST;

	SegmentTree(const vector<lli>& a){
		this->N = a.size();
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i){
			ST[i + N] = node(a[i]);
		}
		for(int i = N - 1; i > 0; --i){
			ST[i] = ST[i << 1] + ST[i << 1 | 1];
		}
	}

	void update(int pos, lli value){
		ST[pos += N] = node(value);
		while(pos >>= 1){
			ST[pos] = ST[pos << 1] + ST[pos << 1 | 1];
		}
	}

	lli query(int l, int r){
		node left, right;
		bool le = false, ri = false;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1) {
			if(l & 1){
				if(le) left = left + ST[l++];
				else left = ST[l++], le = true;
			}
			if(!(r & 1)){
				if(ri) right = ST[r--] + right;
				else right = ST[r--], ri = true;
			}
		}
		if(le && ri) return (left + right).maxSum;
		else if(le) return left.maxSum;
		else return right.maxSum;
	}
};

int main(){
	int n = 1e7+3, L = 1e7, R = 1e7+2e5;
	vector<int> t = {0, 0, 1};
	while(t.size() < 2*R){
		int k = t.size();
		t.push_back((t[k-1] + t[k-2] + t[k-3]) % n);
	}
	lli ans = 0;
	SegmentTree* st;
	vector<lli> a(n);
	for(int i = 1; i <= R; ++i){
		int pos = t[2*i-2];
		a[pos] += 2*t[2*i-1] - n + 1;
		if(i == L){
			st = new SegmentTree(a);
		}
		if(i > L){
			st->update(pos, a[pos]);
			ans += st->query(0, n-1);
		}
	}
	cout << ans << "\n";
	return 0;
}