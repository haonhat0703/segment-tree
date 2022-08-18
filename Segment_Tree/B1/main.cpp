/*
    *** DE BAI: 
    
    - Co mot mang n phan tu chua cac so nguyen, phan tu dau tien co index = 1
    - Co m thao tac, moi thao tac co hai lenh sau:
        1) Co dang (0 i): xuat ra gia tri cua so o vi tri i trong mang.
        2) Co dang (1 u v x): tang gia tri tu vi tri u den vi tri v trong mang len x (-1e6<=x<=1e6).
*/

// cai dat bai toan bang cay IT voi lazy
#include <iostream>

using namespace std;

const int N = int (1e6);// so phan tu toi da

int tree[N], lazy[N];// tree quan li gia tri, lazy quan li nho

void down(int id)
// chuyen gia tri nho trong lazy xuong lazy node duoi va cong them gia tri nay cho node duoi gan nhat
{
    lazy[id * 2] += lazy[id];
    lazy[id * 2 + 1] += lazy[id];

    tree[id * 2] += lazy[id];
    tree[id * 2 + 1] += lazy[id];

    lazy[id] = 0;// da chuyen xuong nen gan lai node hien tai rong
}

void update(int id, int l, int r, int u, int v, int key)
// ham tang u den v len key gia tri voi lazy
{
    if (v < l || r < u) return;// khoang can tang nam ngoai vung dang xet => thoat (dk dung dq)

    if (u <= l && r <= v) { // khoang dang xet nam hoan toan trong khoang can tang => tang gia tri vung nay va nho lazy cho cac con duoi => thoat (dk dung dq)
        tree[id] += key;// tang gia tri vung nay
        lazy[id] += key;// nho cho cac con duoi
        return;// thoat
    }

    down(id);// truy cap xuong phia duoi => dua gia tri lazy dang luu tai id nay xuong con trai va phai 

    int mid = (l + r) / 2;
    update(id * 2, l, mid, u, v, key);// xuong con trai
    update(id * 2 + 1, mid + 1, r, u, v, key);// xuong con phai
}

int get(int id, int l, int r, int idx)
// ham lay gia tri cua vi tri idx
{
    if (idx < l || idx > r) return 0;// idx nam ngoai khoang dang xet => thoat

    if (l == r) return tree[id];// da toi vi tri cua idx (l == r == idx) => gia tri nay do node id quan li => kq 

    down(id);// truy cap xuong phia duoi => dua gia tri lazy dang luu tai id nay xuong con trai va phai

    int mid = (l + r) / 2;
    return get(id * 2, l, mid, idx) + get(id * 2 + 1, mid + 1, r, idx);// tra ve kq la tong cua con trai va phai dang quan li
}

int main()
{
    int n, x, m;// n so pt, m so thao tac, x la gia tri
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        update(1, 1, n, i, i, x);// voi moi gia tri x ta them vao vi tri i => luc nay (u == v == i)// ban dau tree co gia tri la 0 het
    }
    
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int tt, u, v;
        cin >> tt;// tt la 0 hoac 1 de nhan biet lenh can thuc hien 
        if (tt == 0) {// khi tt = 0 thi lay gia tri cua vt u ra
            cin >> u;
            cout << get(1, 1, n, u) << endl;
        }
        else {// nguoc lai tt = 1 thi them luong x tu vi tri u -> v trong mang
            cin >> u >> v >> x;
            update(1, 1, n, u, v, x);
        }
    }
    return 0;
}