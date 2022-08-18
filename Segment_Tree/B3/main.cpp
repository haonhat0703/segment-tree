//{}[]
/*
Co the thuc hien bang cach dung hai mang trai phai quan li min
Nhung bai nay minh xin trinh bay cach dung cay phan doan nhu mot hinh thuc luyen tap
*/
#include <iostream>
#include <math.h>

using namespace std;

const int N = int(1e6);
const int MAX_INT = int(1e9);

int n, treeMin[N], treeMax[N], indexArrMin[N], a[N];
int vt = 1, ma, mi;

void input()
// Ham nhap vao mang a 
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
}

void build(int id, int l, int r)
// Xay dung cay nhi phan
{
	if (l == r) {// l == r => la la => gan gia tri luon
		treeMin[id] = treeMax[id] = a[l]; // la la => max = min = a 
		indexArrMin[id] = l; // luu lai vi tri min do doan nay quan li 
		return;// thoat => dk dung
	}

	int mid = (l + r) / 2;
	build(id * 2, l, mid);//trai
	build(id * 2 + 1, mid + 1, r);//phai

	// tinh lai ket qua dua vao hai doan con trai phai

	treeMax[id] = max(treeMax[id * 2], treeMax[id * 2 + 1]);// cap nhat max 

	// cap nhat min va vi tri cua min luon
	if (treeMin[id * 2] <= treeMin[id * 2 + 1]) {// co dau bang vi uu tien phan tu xuat hien truoc!!
		treeMin[id] = treeMin[id * 2];
		indexArrMin[id] = indexArrMin[id * 2];
	}
	else {
		treeMin[id] = treeMin[id * 2 + 1];
		indexArrMin[id] = indexArrMin[id * 2 + 1];
	}
}

void getMin(int id, int l, int r, int u, int v)
// lay ra gia tri va vi tri nho nhat trong mang tu vi tri u->v
{
	if (v < l || r < u) return;//nam ngoai doan dang xet

	if (u <= l && r <= v) {// doan dang xet nam hoan toan ben trong doan can tim
		if (treeMin[id] < mi) {// cap nhat min neu co the (ca vi tri xuat hien)
			mi = treeMin[id];
			vt = indexArrMin[id];
		}
		return;// *thoat
	}

	// neu la doan giao => tim xuong duoi de cap nhat min   
	int mid = (l + r) / 2;
	getMin(id * 2, l, mid, u, v);
	getMin(id * 2 + 1, mid + 1, r, u, v);
}

void getMax(int id, int l, int r, int u, int v)
// lay ra gia tri lon nhat trong mang tu vi tri u->v
// nhu min nhung khong can luu lai vi tri cua max trong mang
{
	if (v < l || r < u) return;

	if (u <= l && r <= v) {
		ma = max(ma, treeMax[id]);
		return;
	}

	int mid = (l + r) / 2;
	getMax(id * 2, l, mid, u, v);
	getMax(id * 2 + 1, mid + 1, r, u, v);
}

void pr()
// xu li yeu cau de bai
{
	build(1, 1, n);// xay dung cay phan doan voi treeMax giu gia tri max cua doan dang xet
	// treeMin giu gia tri min cua doan dang xet va indexArrMin luu vi tri cua no trong mang 
	int res = 0, ll = 1;
	while (ll <= n) {
		mi = MAX_INT;
		getMin(1, 1, n, ll, n);

		ma = -MAX_INT;
		getMax(1, 1, n, 1, ll - 1);

		res += ma <= mi;
		ll = vt + 1;
	}
	cout << res;
}

int main()
{
	input();
	pr();
	return 0;
}
