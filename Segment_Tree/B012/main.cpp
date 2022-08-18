/*
	DE BAI:
	Cho mot xau co do dai N chi gom ki tu '(' va ')', danh so tu 1 -> N. Cho M truy van, moi truy van thuoc 1 trong 2 loai sau:
		1) (0 i c): thay doi ki tu o vi tri i thanh ki tu c (c la '(' hoac ')'). 
		2) (1 u v):	in ra 1 neu xau con tu u->v la mot day ngoac dung, nguoc lai in ra 0.

							INPUT									OUTPUT
							8 7				
							()))(())								10110
							1 1 2
							1 3 4
							0 3 (
							1 1 4
							1 5 8
							0 6 )
							1 5 8
*/

#include <iostream>
#include <math.h>

using namespace std;

const int N = int(1e6);

struct node
{
	int open, close;
	//open so ngoac sai dang mo, close so ngoac sai dang dong, khong tinh cac ngoac mo dung va dong dung
};

node tree[N];// tree quan li doan tuong ung

node comp(node l, node r)
//ham tinh so ngoac mo, dong sai, l la node trai va r la node phai
{
	int loss = min(l.open, r.close);//so day ngoac dung la min cua mo trai va dong phai
	return { l.open + r.open - loss, l.close + r.close - loss };
	// tra ve thong tin so ngoac trai sai va phai sai
}

void update(int id, int l, int r, int idx, char ch)
// ham cap nhat ki tu o vi tri idx thanh ch
{
	if (idx < l || r < idx) return;// doan dang xet nam ngoai vi tri idx => thoat
	if (l==r) {// da den idx => l==r hay la la
		if (ch == '(') tree[id] = { 1, 0 };//vi chi co 1 phan tu nen ta co nhu ben
		else tree[id] = { 0, 1 };
		return;// thoat
	}

	//di xuong duoi de tinh

	int mid = (l + r) / 2;
	update(id * 2, l, mid, idx, ch);//trai
	update(id * 2 + 1, mid + 1, r, idx, ch);//phai

	// di nguoc len tren de tinh node cha dua vao cac con da co kq

	tree[id] = comp(tree[id * 2], tree[id * 2 + 1]);
}

node get(int id, int l, int r, int u, int v)
// ham tra ve so ngoac mo dung va sai trong doan u->v 
{
	if (v < l || r < u) return{ 0, 0 };// nam ngoai nhau (khong giao) => return (0, 0) de khong anh huong ket qua
	if (u <= l && r <= v) return tree[id];// la doan con => ta tinh duoc ngay kq

	int mid = (l + r) / 2;
	return comp(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		char ch;
		cin >> ch;
		update(1, 1, n, i, ch);
	}

	for (int i=1; i <= m; i++) {
		int tt;
		cin >> tt;
		if (tt == 0) {
			int u;
			char ch;
			cin >> u >> ch;
			update(1, 1, n, u, ch);
		}else {
			int u, v;
			cin >> u >> v;
			node res = get(1, 1, n, u, v);
			if (res.open == 0 && res.close == 0) cout << 1;
			else cout << 0;
		}
	}
	return 0;
}