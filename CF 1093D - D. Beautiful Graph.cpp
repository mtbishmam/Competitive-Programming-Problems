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

const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1};
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1};
const int INF = 2147483647;
const ll LINF = 9223372036854775807;
const int MOD = 998244353;
const int maxn = 1e5 + 1;

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
    cin >> ttt;
    for (int itt = 1; itt <= ttt; itt++)
    {
        int n, m;
        cin >> n >> m;
        vvi g(n + 1);
        for (int i = 1; i <= m; i++) {
            int a, b;
            cin >> a >> b;
            g[a].eb(b);
            g[b].eb(a);
        }

        vb vis(n + 1);
        vb col(n + 1);
        function<int(int, int)> bipar = [&](int node, int c) {
            vis[node] = 1;
            col[node] = c;
            for (auto& child : g[node]) {
                if (!vis[child]) {
                    if (!bipar(child, c ^ 1)) return false;
                }
                else {
                    if (col[child] == col[node]) return false;
                }
            }
            return true;
        };

        bool ok = 1;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) ok &= bipar(i, 0);
        }

        if (ok) {
            ll ans = 1;
            auto pw = [&](ll a, ll b) {
                ll ret = 1;
                while (b) {
                    if (b & 1) ret = ret * a % MOD;
                    a = a * a % MOD;
                    b >>= 1;
                }
                return ret;
            };
            vis = vb(n + 1);
            vi nodes;
            function<void(int node)> f = [&](int node) {
                vis[node] = 1;
                nodes.eb(node);
                for (auto& child : g[node])
                    if (!vis[child]) f(child);
            };
            for (int i = 1; i <= n; i++) {
                if (!vis[i]) {
                    f(i);
                    int z = 0, o = 0, t = nodes.size();
                    for (auto& node : nodes)
                        z += !col[node];
                    ll cur = (pw(2, z) + pw(2, t - z)) % MOD;
                    ans = ans * cur % MOD;
                    nodes.clear();
                }
            }
            cout << ans;
        } else cout << 0;
        cout << endl;
    }
    return 0;
}

