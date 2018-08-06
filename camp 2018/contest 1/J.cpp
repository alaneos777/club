#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli inf = INT_MAX;

template <typename T>
struct info{
	T minimo, maximo;
	info(int minimo, int maximo){
		this->minimo = minimo, this->maximo = maximo;
	}
};

template <typename T>
struct SegmentTree{
	SegmentTree *left, *right;
	int start, end, half;
	info<T> *ans;

	info<T> *combine(info<T> *a, info<T> *b){
		return new info<T>(min(a->minimo, b->minimo), max(a->maximo, b->maximo));
	}

	SegmentTree(int start, int end){
		this->start = start;
		this->end = end;
		this->half = start + ((end - start) >> 1);
		this->ans = new info<T>(0, 0);
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
			this->ans = new info<T>(value, value);
		else{
			this->left->update(value, start, min(end, this->half));
			this->right->update(value, max(start, this->half + 1), end);
			this->ans = this->combine(this->left->ans, this->right->ans);
		}
	}

	info<T> *query(int start, int end){
		if(start > end)
			return new info<T>(inf, -inf);
		if(start == this->start && end == this->end)
			return this->ans;
		return combine(this->left->query(start, min(end, this->half)), this->right->query(max(start, this->half + 1), end));
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	SegmentTree<lli> *ST = new SegmentTree<lli>(1, 1e5);
	for(lli n = 1; n <= 1e5; n++){
		ST->update((n * n) % 12345 + (n * n * n) % 23456, n, n);
	}
	int k, x, y;
	cin >> k;
	while(k--){
		cin >> x >> y;
		if(x > 0){
			info<lli> *q = ST->query(x, y);
			cout << q->maximo - q->minimo << "\n";
		}else{
			ST->update(y, -x, -x);
		}
	}
	return 0;
}