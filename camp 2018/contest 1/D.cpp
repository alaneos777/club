#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli inf = INT_MAX;

template <typename T>
struct SegmentTree{
	SegmentTree *left, *right;
	int start, end, half;
	T value;

	SegmentTree(int start, int end){
		this->start = start;
		this->end = end;
		this->half = start + ((end - start) >> 1);
		this->value = 0;
		if(start == end){
			this->left = this->right = NULL;
		}else{
			this->left = new SegmentTree(start, this->half);
			this->right = new SegmentTree(this->half + 1, end);
		}
	}

	void update(T value, int start, int end){
		if(start > end)
			return;
		if(start == this->start && end == this->end)
			this->value = value;
		else{
			this->left->update(value, start, min(end, this->half));
			this->right->update(value, max(start, this->half + 1), end);
			this->value = this->left->value + this->right->value;
		}
	}

	T query(int start, int end){
		if(start > end)
			return 0;
		if(start == this->start && end == this->end)
			return this->value;
		return this->left->query(start, min(end, this->half)) + this->right->query(max(start, this->half + 1), end);
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector< pair<int, int> > A(n);
	for(int i = 0; i < n; i++){
		cin >> A[i].first;
		A[i].second = i;
	}
	sort(A.begin(), A.end());
	SegmentTree<lli> *ST1 = new SegmentTree<lli>(0, n - 1);
	SegmentTree<lli> *ST2 = new SegmentTree<lli>(0, n - 1);
	lli count = 0;
	int i = 0;
	while(i < n){
		int j = i;
		while(j < n && A[j].first == A[i].first){
			int pos = A[j].second;
			ST2->update(ST1->query(pos + 1, n - 1), pos, pos);
			count += ST2->query(pos + 1, n - 1);
			j++;
		}
		j = i;
		while(j < n && A[j].first == A[i].first){
			int pos = A[j].second;
			ST1->update(1, pos, pos);
			j++;
		}
		i = j;
	}
	cout << count << "\n";
	return 0;
}