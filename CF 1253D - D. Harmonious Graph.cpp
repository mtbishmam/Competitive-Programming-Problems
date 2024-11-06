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

using ll    = long long;
using ld    = long double;
using pii   = pair<int, int>; using pli  = pair<ll, int>;  using pil = pair<int, ll>;
using pll   = pair<ll, ll>;   using vl   = vector<ll>;     using vvl = vector<vl>;
using vi    = vector<int>;    using vb   = vector<bool>;   using vc  = vector<char>;
using vvi   = vector<vi>;     using vvb  = vector<vb>;     using vvc = vector<vc>;
using vpii  = vector<pii>;    using vpll = vector<pll>;    using vs  = vector<string>;
using vvpii = vector<vpii>;   using tiii = tuple<int, int, int>;
using vtiii = vector<tiii>;
template <class A, class B> using umap = unordered_map<A, B>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)

const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1};
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1};
const int INF = 1e6;
const ll LINF = 9223372036854775807;
const int MOD = 1e9 + 7;
const int maxn = 1e5 + 1;

struct dsu {
    int n;
    vi sz, par, mx, mn;
    dsu(int _n) : n(_n), sz(n, 1), par(n, -1), mx(n, -1), mn(n, INF) {}
    int find(int x) { return (par[x] == -1 ? x : par[x] = find(par[x])); }
    int unite(int a, int b) {
        int oa = a, ob = b;
        a = find(a), b = find(b);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b);
            par[b] = a;
            mx[a] = max({mx[a], ob, oa});
            mn[a] = min({mn[a], ob, oa});
            sz[a] += sz[b];
            return 1;
        }
        return 0;
    }
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
        int n, m;
        cin >> n >> m;
        dsu ds(n + 5);
        for (int i = 0, x, y; i < m; i++)
            cin >> x >> y, ds.unite(x, y);

        // vi gr(n + 5);
        // vi grpos(n + 5);
        // vb used(n + 5);
        // vi ass(n + 5);
        // for (int i = 1; i <= n; i++)
        //     if (!used[ds.find(i)]) {
        //         gr[i] = ds.find(i);
        //         grpos[gr[i]] = i;
        //         used[gr[i]] = 1;
        //         // cout << ds.mn[gr[i]] << endl;
        //         ass[ds.mn[gr[i]]] = gr[i];
        //         ass[ds.mx[gr[i]]] = gr[i];
        //     }
        int ans(0);
        set<int> s;
        for (int i = 1; i <= n; i++) s.e(i);
        for (int i = 1; i <= n; i++) {
            int cgr = ds.find(i);
            if (ds.sz[cgr] > 1) {
                int mn = ds.mn[cgr];
                int mx = ds.mx[cgr];
                while (1) {
                    auto it = s.lb(mn);
                    if (it == s.end() or * it > mx) break;
                    ans += ds.unite(cgr, *it);
                    s.erase(it);
                }
            }
        }
        cout << ans;
        // for (int i = 1; i <= n; i++)
        //     if (ass[i]) {
        //         int j = i + 1;
        //         while (j <= n and ass[j] != ass[i]) {
        //             ans += ds.unite(ass[j], ass[i]);
        //             j++;
        //         }
        //         i = j - 1;
        //     }
        // cout << ans;
        // for (int i = 1; i <= n; i++) {
        //     if (used[gr[i]] and used[gr[i + 1]])
        //         if (i + 1 <= n and gr[i] != gr[i + 1] and grpos[gr[i]] >= i + 1)
        //             ans += ds.unite(gr[i], gr[i + 1]);
        // }
        // cout << ans;
        // vvi g(n + 5);
        // for (int i = 1; i <= n; i++) {
        //     int grp = ds.find(i);
        //     int mx = ds.mx[grp], mn = ds.mn[grp];
        //     if(mx - mn + 1 != ds.sz[grp]) {

        //     }
        // }

    }
    return 0;
}
