#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <iomanip>
#include <cstring>
// #include <cassert>
#include <functional>
using namespace std;

#define endl "\n"
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define lb lower_bound
#define ub upper_bound
#define em emplace

template <typename T> istream& operator>>(istream& is, vector<T>& a) { for (auto& i : a) is >> i; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<T>& a) { for (auto& i : a) os << i << " "; return os; };
template <typename T> ostream& operator<<(ostream& os, set<T>& s) { for (auto i : s) os << i << " "; return os; }
// template <typename T> ostream& operator<<(ostream &os, const vector<T>& v) { os << '{'; string s; for (const auto &x : v) os << s << x, s = " "; return os << '}'; }
template <typename A, typename B> istream& operator>>(istream& is, pair<A, B>& i) { return is >> i.ff >> i.ss; }
template <typename A, typename B> ostream& operator<<(ostream& os, pair<A, B>& i) { return os << i.ff << " " << i.ss; }
template <typename A, typename B> ostream& operator<<(ostream& os, map<A, B>& mp) { for (auto i : mp) os << i << ", "; return os; }
// template <typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& i) { return os << '{' << i.ff << ", " << i.ss << '}'; }
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using ll    = long long      ; using ld    = long double  ; using ull = unsigned ll    ;
using pii   = pair<int, int> ; using pli  = pair<ll, int> ; using pil = pair<int, ll>  ;
using pll   = pair<ll, ll>   ; using vl   = vector<ll>    ; using vvl = vector<vl>     ;
using vi    = vector<int>    ; using vb   = vector<bool>  ; using vc  = vector<char>   ;
using vvi   = vector<vi>     ; using vvb  = vector<vb>    ; using vvc = vector<vc>     ;
using vpii  = vector<pii>    ; using vpll = vector<pll>   ; using vs  = vector<string> ;
using vvpii = vector<vpii>   ; using vvvi = vector<vvi>   ; using vvvl = vector<vvl>   ;
using vull = vector<ull>     ;
using tiii = tuple<int, int, int>;                        ; using vtiii = vector<tiii> ;
template <class A, class B> using umap = unordered_map<A, B>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define bug cerr << "!Bugged..." << endl
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)
#define sz(x) (int)(x).size()

const string cq[2] = {"NO", "YES"};
const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1};
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1};
const int INF = 2147483647;
const ll LINF = 9223372036854775807;
const int MOD = 1e9 + 7;
const int N = 1e5 + 1;

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
    vector<T> sg;
    segtree(int _n) {
        n = _n;
        sg = vector<T>(4 * _n);
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
        if (r < L or R < l) return T(0, LLONG_MAX, -LLONG_MAX);    // ------------------------->
        if (L <= l and r <= R) return sg[i];
        int mid = (l + r) >> 1;
        T left = query(L, R, i * 2, l, mid);
        T right = query(L, R, i * 2 + 1, mid + 1, r);
        return left + right;
    }
    void update(int L, int R, T cur, int i, int l, int r) {
        if (r < L or R < l) return;
        if (L <= l and r <= R) sg[i] = sg[i] + cur; // ------------------------->
        else {
            int mid = (l + r) >> 1;
            update(L, R, cur, i * 2, l, mid);
            update(L, R, cur, i * 2 + 1, mid + 1, r);
            sg[i] = sg[i * 2] + sg[i * 2 + 1];
        }
    }
    void set(int L, int R, T cur, int i, int l, int r) {
        if (r < L or R < l) return;
        if (L <= l and r <= R) sg[i] = cur; // ------------------------->
        else {
            int mid = (l + r) >> 1;
            set(L, R, cur, i * 2, l, mid);
            set(L, R, cur, i * 2 + 1, mid + 1, r);
            sg[i] = sg[i * 2] + sg[i * 2 + 1];
        }
    }
    T query(int L, int R) { return query(L, R, 1, 0, n - 1); }
    void update(int L, int R, T cur) { update(L, R, cur, 1, 0, n - 1); }
    void update(int L, int R, ll x) { update(L, R, {x, x, x}, 1, 0, n - 1); }
    void set(int L, int R, T cur) { set(L, R, cur, 1, 0, n - 1); }
    void set(int L, int R, ll x) { set(L, R, {x, x, x}, 1, 0, n - 1); }
};


int main()
{
#ifndef ONLINE_JUDGE
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
        int n; cin >> n;
        int q; cin >> q;
        vl a(n); cin >> a;
        segtree<node> tree(n + 1); vl p(n + 5);
        for (int i = 1; i <= n; i++)
            tree.set(i, i, a[i - 1]), p[i] = p[i - 1] + a[i - 1];

        while (q--) {
            int k;
            cin >> k;
            int l = 1, r = n, ans = 0;
            while (l <= r) {
                int mid = l + r >> 1;
                auto nd = tree.query(1, mid);
                if (k >= nd.mx) {
                    l = mid + 1;
                    ans = mid;
                } else r = mid - 1;
            }
            cout << p[ans] << " ";
        }
        cout << endl;
    }
    return 0;
}
