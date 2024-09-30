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
#include <cassert>
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
#define bug cerr << "!Bugged..." << endl
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)

const string cq[2] = {"NO", "YES"};
const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1};
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1};
const int INF = 2147483647;
const ll LINF = 9223372036854775807;
const int MOD = 1e9 + 7;
const int maxn = 1e5 + 1;

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
        int n; cin >> n; int p2 = log(n) + 5; vi depth(n + 1);
        vvi g(n + 1), lca(n + 1, vi(p2, -1)); vl a(n + 1), b(n + 1);
        for (int i = 2, p; i <= n; i++) {
            cin >> p >> a[i] >> b[i];
            g[i].eb(p);
            g[p].eb(i);
            lca[i][0] = p;
        }
        function<void(int, int)> f = [&](int node, int par) {
            for (auto& child : g[node])
                if (child != par) {
                    depth[child] = depth[node] + 1;
                    a[child] += a[node];
                    b[child] += b[node];
                    f(child, node);
                }
        }; f(1, -1);

        for (int j = 1; j < p2; j++) {
            for (int i = 1; i <= n; i++) {
                if (lca[i][j - 1] != -1) {
                    lca[i][j] = lca[lca[i][j - 1]][j - 1];
                }
            }
        }

        auto find = [&](int node, int k) {
            int ret = node;
            for (int i = p2 - 1; i >= 0; i--) {
                if ((1 << i) <= k) {
                    k -= (1 << i);
                    ret = lca[ret][i];
                    if (ret == -1) break;
                }
            }
            return ret;
        };

        vl ans(n + 1);
        for (int i = 2; i <= n; i++) {
            if (a[i] >= b[i]) {
                ans[i] = depth[i];
            } else {
                int l = 0, r = n + 5, bans = 0;
                while (l <= r) {
                    int mid = l + r >> 1;
                    int anc = find(i, mid);
                    if (anc == -1) {
                        r = mid - 1;
                        continue;
                    }
                    if (anc != -1 and a[i] >= b[anc]) {
                        bans = anc; r = mid - 1;
                    } else l = mid + 1;
                }
                ans[i] = depth[bans];
            }
            cout << ans[i] << " ";
        }
        cout << endl;

    }
    return 0;
}
