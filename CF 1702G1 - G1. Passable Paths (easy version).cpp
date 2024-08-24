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
// #include <functional>
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

using ll    = long long      ; using ld    = long double  ; using ull = unsigned ll    ;
using pii   = pair<int, int> ; using pli  = pair<ll, int> ; using pil = pair<int, ll>  ;
using pll   = pair<ll, ll>   ; using vl   = vector<ll>    ; using vvl = vector<vl>     ;
using vi    = vector<int>    ; using vb   = vector<bool>  ; using vc  = vector<char>   ;
using vvi   = vector<vi>     ; using vvb  = vector<vb>    ; using vvc = vector<vc>     ;
using vpii  = vector<pii>    ; using vpll = vector<pll>   ; using vs  = vector<string> ;
using vvpii = vector<vpii>   ; using vvvi = vector<vvi>   ; using vvvl = vector<vvl>   ;
using tiii = tuple<int, int, int>;                        ; using vtiii = vector<tiii> ;
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
    // cin >> T;
    for (int Ti = 1; Ti <= T; Ti++)
    {
        int n;
        cin >> n;
        vvi g(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            g[x].eb(y);
            g[y].eb(x);
        }
        vi need, dep(n + 1), dp; bool ok = 0;
        function<void(int, int)> find = [&](int node, int par) {
            for (auto& child : g[node]) {
                if (child != par) {
                    dep[child] = dep[node] + 1;
                    find(child, node);
                }
            }
        }; find(1, -1);
        function<int(int, int)> f = [&](int node, int par) {
            int ret = 0, lower = 0;
            for (auto& child : g[node]) {
                if (child != par) {
                    ret += f(child, node);
                    lower |= dp[child];
                }
            }
            if (need[node] and !lower) ret = 1;
            dp[node] |= lower | need[node];
            return ret;
        };

        int q; cin >> q;
        while (q--) {
            int k, x; cin >> k; ok = 0;
            need = dp = vi(n + 1);
            int start = -1, mx = -1;
            for (int i = 0; i < k; i++) {
                cin >> x;
                need[x] = 1;
                if (dep[x] > mx) {
                    mx = dep[x];
                    start = x;
                }
            }
            int cnt = f(start, -1);
            cout << cq[cnt == 1] << endl;
        }

    }
    return 0;
}
