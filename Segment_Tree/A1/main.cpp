/*
	DE BAI:
	Cho mang A gom n phan tu (danh so tu 1). Co q truy van thuoc 2 loai:
		1) (1 u v): cong v vao A[u].
		2) (2 u v): tinh tong cac phan tu tu u->v.
	
*/
#include<iostream>

using namespace std;

const int N = int(1e6);
typedef long long ll;

ll bit[N];
int n;

ll getSum(int u, int v) 
{
	int idx = v;
	ll t1 = 0;
	while (idx > 0) {
		t1 += bit[idx];
		idx -= (idx & (- idx));
	}

	idx = u - 1;
	ll t2 = 0;
	while (idx > 0) {
		t2 += bit[idx];
		idx -= (idx & (-idx));
	}
	return t1 - t2;
}

void update(int u, int v)
{
	int idx = u;
	while (idx <= n) {
		bit[idx] += v;
		idx += (idx & (-idx));
	} 
}

int main()
{
	int x, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		update(i, x);
	} 
	
	for (int i = 1; i <= m; i++) {
		int tt, u, v;
		cin >> tt >> u >> v;
		if (tt == 1) 
			update(u, v);
		else
			cout << getSum(u, v) << endl;
	} 

	return 0;
}