#include <iostream>
#include <math.h>

using namespace std;

typedef long long ll;
const int N = int(1e6);

struct node {
	int mi, ma;
};

node tree[N];
int val[N];

void build(int id, int l, int r, int idx, int key)
{
	if (idx < l || r < idx) return;
	if (l == r) return tree[id] = { key, key }, void();

	int mid = (l + r) / 2;
	build(id * 2, l, mid, idx, key);
	build(id * 2 + 1, mid + 1, r, idx, key);

	tree[id] = { min(tree[id * 2].mi, tree[id * 2 + 1].mi), max(tree[id * 2].ma,tree[id * 2 + 1].ma) };
}

int get (int id, int l, int r, int key, int data)
{
	if (l > key && tree[id].ma < data) return r - l + 1;
	if (tree[id].mi >= data || l == r) return 0;

	int mid = (l + r) / 2;
	return get(id * 2, l, mid, key, data) + get(id * 2 + 1, mid + 1, r, key, data);
}

int main()
{
	int n;
	ll res = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> val[i];
		build(1, 1, n, i, val[i]);
	} 

	for (int i = 1; i < n; i++)
		res += get(1, 1, n, i, val[i]);
	cout << res;
	return 0;
}