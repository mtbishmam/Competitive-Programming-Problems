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
// template <typename T> ostream& operator<<(ostream &os, const vector<T>& v) { os << '{'; string s; for (const auto &x : v) os << s << x, s = " "; return os << '}'; }
template <typename A, typename B> istream& operator>>(istream& is, pair<A, B>& i) { return is >> i.ff >> i.ss; }
template <typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& i) { return os << i.ff << " " << i.ss; }
// template <typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& i) { return os << '{' << i.ff << ", " << i.ss << '}'; }
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using ll    = long long;
using ld    = long double;
using pii   = pair<int, int>; using pli  = pair<ll, int>; using pil = pair<int, ll>;
using pll   = pair<ll, ll>  ; using vl   = vector<ll>   ; using vvl = vector<vl>;
using vi    = vector<int>   ; using vb   = vector<bool> ; using vc  = vector<char>;
using vvi   = vector<vi>    ; using vvb  = vector<vb>   ; using vvc = vector<vc>;
using vpii  = vector<pii>   ; using vpll = vector<pll>  ; using vs  = vector<string>;
using vvpii = vector<vpii>  ; using vvvi = vector<vvi>  ; using vvvl = vector<vvl>;
using tiii = tuple<int, int, int>;                      ; using vtiii = vector<tiii>;
template <class A, class B> using umap = unordered_map<A, B>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)

const string cq[2] = {"NO", "YES"};
const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1};
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1};
const int INF = 2147483647;
const ll LINF = 9223372036854775807;
const int MOD = 1e9 + 7;
const int maxn = 1e6 + 1;

struct node {
    ll sum, mn, mx;
    node(ll sum = 0, ll mn = 0, ll mx = 0) :
        sum(sum), mn(mn), mx(mx) {}
    node operator+(node& r) {
        node ret;
        ret.sum = sum + r.sum;
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
    T query(int L, int R, int i, int l, int r) {
        if (r < L or R < l) return T(0, LINF, -LINF);    // ------------------------->
        if (L <= l and r <= R) return sg[i];
        int mid = (l + r) >> 1;
        T left = query(L, R, i * 2, l, mid);
        T right = query(L, R, i * 2 + 1, mid + 1, r);
        return left + right;
    }
    void update(int L, int R, T cur, int i, int l, int r) {
        if (r < L or R < l) return;
        if (L <= l and r <= R) sg[i] = sg[i] + cur;  // ------------------------->
        else {
            int mid = (l + r) >> 1;
            update(L, R, cur, i * 2, l, mid);
            update(L, R, cur, i * 2 + 1, mid + 1, r);
            sg[i] = sg[i * 2] + sg[i * 2 + 1];
        }
    }
    T query(int L, int R) { return query(L, R, 1, 1, n - 1); }
    void update(int L, int R, T cur) { update(L, R, cur, 1, 1, n - 1); }
};
int a[maxn + 5], pre[maxn + 5], cnt[maxn + 5], ncnt[maxn + 5], un[maxn + 5];
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
    // cin >> T;
    for (int Ti = 1; Ti <= T; Ti++)
    {
        int n, sz = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            un[sz++] = a[i];
        }
        sort(un, un + sz);
        sz = unique(un, un + sz) - un;
        for (int i = 0; i < n; i++) {
            a[i] = lb(un, un + sz, a[i]) - un + 1;
            cnt[a[i]]++;
        }
        for (int i = 1; i <= maxn + 1; i++) {
            pre[1]++;
            pre[cnt[i] + 1]--;
        }
        segtree<node> tree(n + 1);
        for (int i = 1; i <= maxn; i++) {
            pre[i] += pre[i - 1];
            tree.update(i, i, pre[i]);
        }

        ll ans = 0;
        for (int i = 0; i < n; i++) {
            int prev = cnt[a[i]]--;
            ncnt[a[i]]++;
            tree.update(prev, prev, -1);
            ll cur = tree.query(1, ncnt[a[i]] - 1).sum;
            // debug(a[i], cur);
            ans += cur;
        }
        cout << ans;
    }
    return 0;
}
