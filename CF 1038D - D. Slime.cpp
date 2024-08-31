#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <array>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <iomanip>
#include <cstring>
#include <string> // for getline
using namespace std;

#define endl "\n"
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define lb lower_bound
#define ub upper_bound
#define e emplace

template <typename T> istream& operator>>(istream &is, vector<T>& a) { for (auto& i : a) is >> i; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<T>& a) { for (auto& i : a) os << i << " "; return os; };
// template <typename T> ostream& operator<<(ostream &os, const vector<T>& v) { os << '{'; string s; for (const auto &x : v) os << s << x, s = " "; return os << '}'; }
template <typename A, typename B> istream& operator>>(istream& is, pair<A, B>& i) { return is >> i.ff >> i.ss; }
template <typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& i) { return os << i.ff << " " << i.ss; }
// template <typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& i) { return os << '{' << i.ff << ", " << i.ss << '}'; }
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using ll = long long;
using ld = long double;
using pii = pair<int, int>; using pli = pair<ll, int>; using pil = pair<int, ll>;
using pll = pair<ll, ll>;   using vl = vector<ll>;     using vvl = vector<vl>;
using vi = vector<int>;     using vb = vector<bool>;   using vc = vector<char>;
using vvi = vector<vi>;     using vvb = vector<vb>;    using vvc = vector<vc>;
using vpii = vector<pii>;   using vpll = vector<pll>;  using vs = vector<string>;
using tiii = tuple<int, int, int>; using vtiii = vector<tiii>;
template <class A, class B> using umap = unordered_map<A, B>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define bug cerr << "!Bugged..." << endl
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)

const vs cq = { "NO", "YES"};
const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1};
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1};
const int INF = 2147483647;
const ll LINF = 9223372036854775807;
const int MOD = 1e9 + 7;
const int maxn = 1e5 + 1;

struct node {
    ll sum, mn, mx, asum;
    node(ll sum = 0, ll mn = 0, ll mx = 0) :
        sum(sum), mn(mn), mx(mx), asum(abs(sum)) {}
    node operator+(node& r) {
        node ret;
        ret.sum = sum + r.sum;
        ret.asum = asum + r.asum;
        ret.mn = min(mn, r.mn);
        ret.mx = max(mx, r.mx);
        return ret;
    }
};
vi a;
template<class T> struct segtree {
    int n;
    vector<T> sg;
    segtree(int _n) {
        n = _n;
        sg = vector<T>(4 * _n);
    }
    void build(int i, int l, int r) {
        if (l == r) {
            sg[i] = {a[l], a[l], a[l]}; // ------------------------->
        } else {
            int mid = (l + r) >> 1;
            build(i * 2, l, mid);
            build(i * 2 + 1, mid + 1, r);
            sg[i] = sg[i * 2] + sg[i * 2 + 1];
        }
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
        if (L <= l and r <= R) sg[i] = cur;  // ------------------------->
        else {
            int mid = (l + r) >> 1;
            update(L, R, cur, i * 2, l, mid);
            update(L, R, cur, i * 2 + 1, mid + 1, r);
            sg[i] = sg[i * 2] + sg[i * 2 + 1];
        }
    }
    T query(int L, int R) { return query(L, R, 1, 0, n - 1); }
    void update(int L, int R, T cur) { update(L, R, cur, 1, 0, n - 1); }
};


int main()
{
#ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    freopen("error.txt", "a", stderr);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    // cout.tie(NULL);

    int ttt(1);
    // cin >> ttt;
    for (int itt = 1; itt <= ttt; itt++)
    {
        int n;
        cin >> n;
        vl a(n); segtree<node> tree(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            tree.update(i, i, {a[i], a[i], a[i]});
        }
        if (n == 1) {
            cout << a[0] << endl;
            continue;
        }

        ll ans = -LINF, mid, l, r, cur;
        auto node = tree.query(1, n - 1);
        if (node.mn < 0) r = node.asum;
        else r = node.sum - 2 * node.mn;
        ans = a[0] + r;

        node = tree.query(0, n - 2);
        if (node.mn < 0) l = node.asum;
        else l = node.sum - 2 * node.mn;
        ans = max(ans, a[n - 1] + l);
        for (int i = 1; i < n - 1; i++) {
            auto nodel = tree.query(0, i - 1);
            auto noder = tree.query(i + 1, n - 1);
            mid = a[i];
            if (nodel.mn < 0) l = nodel.asum;
            else l = nodel.sum - 2 * nodel.mn;
            if (noder.mn < 0) r = noder.asum;
            else r = noder.sum - 2 * noder.mn;
            cur = l + mid + r;
            if (cur > ans) {
                ans = cur;
                // cout << i << endl;
            }
        }
        cout << ans;


    }
    return 0;
}
