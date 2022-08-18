#include <iostream>
#include <math.h>

using namespace std;

const int N = int(1e6);//So phan tu toi da cua cay
const int MIN_INT = -99999999;// gia tri nho nhat min do ta khoi tao (-oo)

struct Auth {
	int left, right, val;
};// Auth quan li thong tin gom tong max trai, max phai va max tong co tinh den node hien tai

Auth tree[N];// cay IT quan thi cac thong tin nhu tren 
int sum[N], a[N];// sum quan li tong tu 1 -> i (1<=i<=n, n la so phan tu cua mang ban dau)

void build(int id, int l, int r)
//ham xay dung cay phan doan
{
	if (l==r) {// la la => l = r
		tree[id].left = tree[id].right = tree[id].val = a[l];// chi chua mot phan tu => tat ca thong tin la a(l)
		return;// thoat
	} 

	//khong la la => tinh theo con duoi trai va phai 

	int mid = (l + r) / 2;
	build(id * 2, l, mid);// trai
	build(id * 2 + 1, mid + 1, r);// phai

	//tinh theo con duoi trai phai

	tree[id].left = max(tree[id * 2].left, tree[id * 2 + 1].left + sum[mid] - sum[l - 1]);
	//max trai se bang max (max trai cua trai, tong cay trai + max trai cua con phai)
	tree[id].right = max(tree[id * 2 + 1].right, tree[id * 2].right + sum[r] - sum[mid]);
	//tuong tu max trai nhung ap dung cho phai

	tree[id].val = max(max(tree[id * 2].val, tree[id * 2 + 1].val), tree[id * 2].right + tree[id * 2 + 1].left );
	//max cay se la max (cay trai, phai, hoac max trai cua phai + max phai cua trai)
}

Auth get(int id, int l, int r, int u, int v)
// ham tra ve thong tin cac max ma cay quan li lay tu doan u -> v
{
	Auth t = {MIN_INT, MIN_INT, MIN_INT};// khoi tao result vi tinh max nen khoi tao MIN_INT cho lun co kq 
	if (v < l || r < u) return t;// nam ngoai nhau => tra ve t khoi tao
	if (u <= l && r <= v) return tree[id];// nguoc lai tra ve thong tin cay id neu la giao nhau

	//la hai doan giao nhau => tinh xuong cac con 
	//tuong tu nhu ham build
	int mid = (l + r) / 2;
	Auth x = get(id * 2, l, mid, u, v), y = get(id * 2 + 1, mid + 1, r, u, v);

	t.left = max(x.left, y.left + sum[mid] - sum[l - 1]);
	t.right = max(y.right, x.right + sum[r] - sum[mid]);

	t.val = max(x.val, y.val);
	t.val = max(t.val, x.right + y.left);

	return t;// kq tra ve cho ham get
}


int main()
{
	int n; 
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];// mang cong don tong tu 1->i
	} 

	build(1, 1, n);// xay dung cay IT quan li

	int m;
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		cout << get(1, 1, n, u, v).val << endl;//lay kq bai toan
	} 

	return 0;
}