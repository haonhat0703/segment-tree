#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

typedef long long ll;
const int N = int(1e6);

struct node {
	int x, l, r, type;
};

struct seg
{
	int cnt, len;
};

ll ans = 0;
int n, m, k;
node a[N];
seg tree[N];

bool cmp(node u, node v)
{
	return (u.x < v.x || (u.x == v.x && u.type < v.type));
}

void update(int id, int l, int r, int u, int v, int type)
{
	if (v < l || r < u || l > r) return;
	if (u <= l && r <= v) {
		tree[id].cnt += type;
		if (type == 1) tree[id].len = r - l + 1;
		else if (tree[id].cnt==0) {
			if (l == r) tree[id].len = 0;
			else tree[id].len = tree[id * 2].len + tree[id * 2 + 1].len;
		}
		return;
	}

	int mid = (l + r) / 2;
	update(id * 2, l, mid, u, v, type);
	update(id * 2 + 1, mid + 1, r, u, v, type);

	if (tree[id].cnt == 0)
		tree[id].len = tree[id * 2].len + tree[id * 2 + 1].len;

}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		a[++m] = { x1, y1 + 1, y2, 1 };
		a[++m] = { x2, y1 + 1, y2, -1 };
		k = max(k, y2);
	}

	sort(a + 1, a + 1 + m, cmp);

	for (int i = 1; i <= m; i++) {
		ans += (ll)tree[1].len * (ll)(a[i].x - a[i - 1].x);
		update(1, 1, k, a[i].l, a[i].r, a[i].type);
	}

	cout << ans;

	return 0;
}