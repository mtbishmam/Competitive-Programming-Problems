#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <iomanip>
#include <cassert>
using namespace std;

#define endl "\n"
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define lb lower_bound
#define ub upper_bound

using ll = long long; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vs  = vector<string>;
using vi = vector<int>; using vvi = vector<vi>;
using vl = vector<ll>; using vvl = vector<vl>;
using vb = vector<bool>; using vvb = vector<vb>;
using vc  = vector<char>; using vvc = vector<vc>;
using vpii  = vector<pii>; using vpll = vector<pll>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

const string cq[2] = {"NO", "YES"};
const int MOD = 1e9 + 7;
const int maxn = 1e5 + 1;
const ll LINF = 1e18;

struct node {
    ll val, mn, mx;
    node(ll val = 0, ll mn = 0, ll mx = 0) :
        val(val), mn(mn), mx(mx) {}
    node operator+(node& r) {
        node ret;
        ret.val = val + r.val;
        ret.mn = min(mn, r.mn);
        ret.mx = max(mx, r.mx);
        return ret;
    }
};
template<class T> struct segtree {
    int n;
    vector<T> sg, lazy;
    segtree(int _n) {
        n = _n;
        sg = vector<T>(4 * _n);
        lazy = vector<T>(4 * n);
    }
    void prop(int i, int l, int r) {
        if (lazy[i].val) {
            ll len = (r - l + 1);
            sg[i].val +=  len * lazy[i].val;
            sg[i].mn += lazy[i].val;
            sg[i].mx += lazy[i].val;
            if (l != r) {
                lazy[i * 2].val += lazy[i].val;
                lazy[i * 2 + 1].val += lazy[i].val;
            }
            lazy[i].val = 0;
        }
    }
    void build(int i, int l, int r, vi& a) {
        if (l == r) {
            sg[i] = {a[l], a[l], a[l]}; // ------------------------->
        } else {
            int mid = (l + r) >> 1;
            build(i * 2, l, mid, a);
            build(i * 2 + 1, mid + 1, r, a);
            sg[i] = sg[i * 2] + sg[i * 2 + 1];
        }
    }
    T query(int L, int R, int i, int l, int r) {
        prop(i, l, r);
        if (L > R) return T();
        if (r < L or R < l) return T(0, LINF, -LINF);    // ------------------------->
        if (L <= l and r <= R) return sg[i];
        int mid = (l + r) >> 1;
        T left = query(L, R, i * 2, l, mid);
        T right = query(L, R, i * 2 + 1, mid + 1, r);
        return left + right;
    }
    void set(int L, int R, T cur, int i, int l, int r) {
        prop(i, l, r);
        if (L > R) return;
        if (r < L or R < l) return;
        if (L <= l and r <= R) {
            sg[i] = cur;                // ------------------------->
            prop(i, l, r);
        } else {
            int mid = (l + r) >> 1;
            set(L, R, cur, i * 2, l, mid);
            set(L, R, cur, i * 2 + 1, mid + 1, r);
            sg[i] = sg[i * 2] + sg[i * 2 + 1];
        }
    }
    void update(int L, int R, T cur, int i, int l, int r) {
        prop(i, l, r);
        if (L > R) return;
        if (r < L or R < l) return;
        if (L <= l and r <= R) {
            lazy[i] = lazy[i] + cur;                // ------------------------->
            prop(i, l, r);
        } else {
            int mid = (l + r) >> 1;
            update(L, R, cur, i * 2, l, mid);
            update(L, R, cur, i * 2 + 1, mid + 1, r);
            sg[i] = sg[i * 2] + sg[i * 2 + 1];
        }
    }
    void set(int L, int R, T cur) { set(L, R, cur, 1, 0, n - 1); }
    void set(int L, int R, ll x) { set(L, R, {x, x, x}, 1, 0, n - 1); }
    void update(int L, int R, T cur) { update(L, R, cur, 1, 0, n - 1); }
    void update(int L, int R, ll x) { update(L, R, {x, x, x}, 1, 0, n - 1); }
    T query(int L, int R) { return query(L, R, 1, 0, n - 1); }
};

int main()
{
#ifndef ONLINE_JUDGE
#define bug(x) cerr << #x << endl
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // freopen("error.txt", "a", stderr);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    // cout.tie(NULL);

    int T(1);
    cin >> T;
    for (int Ti = 1; Ti <= T; Ti++)
    {
        string s; cin >> s;
        int n = sz(s);
        int bal = n / 2;
        vi op, cl;
        for (int i = 0; i < n; i++)
            if (s[i] == '(') bal--;
        for (int i = 0; i < n; i++) {
            if (s[i] == '?') {
                s[i] = '(';
                op.eb(i);
                bal--;
            }
            if (!bal) break;
        }
        for (int i = 0; i < n; i++) if (s[i] == '?') s[i] = ')', cl.eb(i);
        vi a(n);
        segtree<node> tree(n);
        for (int i = 0, cur = 0; i < n; i++) {
            cur += (s[i] == ')' ? -1 : 1);
            a[i] = cur;
            tree.update(i, i, cur);
        }
        // cerr << s << endl;
        bool ok = 1;
        for (auto& o : op) {
            tree.update(o, n - 1, -2);
            auto it = lb(all(cl), o);
            if (it != cl.end()) {
                int clp = *it;
                tree.update(clp, n - 1, 2);
                auto nd = tree.query(0, n - 1);
                auto lst = tree.query(n - 1, n - 1);
                if (nd.mn >= 0 and !lst.mn) {
                    ok = 0;
                }
                tree.update(clp, n - 1, -2);
            }
            tree.update(o, n - 1, 2);
        }

        // for (auto& c : cl) {
        //     tree.update(c, n - 1, 2);
        //     auto it = lb(all(op), c);
        //     if (it != op.end()) {
        //         int olp = *it;
        //         tree.update(olp, n - 1, -2);
        //         auto nd = tree.query(0, n - 1);
        //         auto lst = tree.query(n - 1, n - 1);
        //         if (nd.mn >= 0 and !lst.mn) {
        //             ok = 0;
        //         }
        //         tree.update(olp, n - 1, 2);
        //     }
        //     tree.update(c, n - 1, -2);
        // }
        cout << cq[ok] << endl;
    }
    return 0;
}
