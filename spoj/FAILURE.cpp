#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}
	bool operator<(const point&p) const{
		if(x != p.x) return x < p.x;
		return y < p.y;
	}
	point operator-(const point&p) const{
		return point(x - p.x, y - p.y);
	}
	lli norm() const{
		return x*x + y*y;
	}
	double abs() const{
		return hypot(x, y);
	}
};

struct vantage_point_tree
{
	struct node
	{
		point p;
		double th;
		node *l, *r;
	}*root;

	vector<pair<double, point>> aux;

	vantage_point_tree(vector<point> &ps)
	{
		for (int i = 0; i < ps.size(); ++i)
			aux.push_back({ 0, ps[i] });
		root = build(0, ps.size());
	}

	node *build(int l, int r)
	{
		if (l == r)
			return 0;
		swap(aux[l], aux[l + rand() % (r - l)]);
		point p = aux[l++].second;
		if (l == r)
			return new node({ p });
		for (int i = l; i < r; ++i)
			aux[i].first = (p - aux[i].second).norm();
		int m = (l + r) / 2;
		nth_element(aux.begin() + l, aux.begin() + m, aux.begin() + r);
		return new node({ p, sqrt(aux[m].first), build(l, m), build(m, r) });
	}

	priority_queue<pair<double, node*>> que;

	void k_nn(node *t, point p, int k)
	{
		if (!t)
			return;
		double d = (p - t->p).abs();
		if (que.size() < k)
			que.push({ d, t });
		else if (que.top().first > d)
		{
			que.pop();
			que.push({ d, t });
		}
		if (!t->l && !t->r)
			return;
		if (d < t->th)
		{
			k_nn(t->l, p, k);
			if (t->th - d <= que.top().first)
				k_nn(t->r, p, k);
		}
		else
		{
			k_nn(t->r, p, k);
			if (d - t->th <= que.top().first)
				k_nn(t->l, p, k);
		}
	}

	vector<point> k_nn(point p, int k)
	{
		k_nn(root, p, k);
		vector<point> ans;
		for (; !que.empty(); que.pop())
			ans.push_back(que.top().second->p);
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<point> points(n);
		for(int i = 0; i < n; ++i){
			cin >> points[i].x >> points[i].y;
		}
		vantage_point_tree T(points);
		for(int i = 0; i < n; ++i){
			cout << (T.k_nn(points[i], 2)[1] - points[i]).norm() << "\n";
		}
	}
	return 0;
}