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
        int n; cin >> n;
        int m; cin >> m;
        vi a(n); cin >> a;
        vpii r(m); cin >> r;
        for (auto& i : r) i.ff--, i.ss--;
        // debug(r);

        int ans = -1;
        vi res;
        for (int i = 0; i < n; i++) {
            vi b = a, pre(n + 1), ops;
            for (int j = 0; j < m; j++) {
                if (i < r[j].ff or r[j].ss < i) {
                    pre[r[j].ff]--, pre[r[j].ss + 1]++;
                    ops.eb(j + 1);
                }
            }
            b[0] += pre[0];
            int mn = b[0], mx = b[0];
            for (int j = 1; j < n; j++) {
                pre[j] += pre[j - 1];
                b[j] += pre[j];
                mn = min(mn, b[j]);
                mx = max(mx, b[j]);
            }
            // cout << b << endl;
            int d = mx - mn;
            if (d > ans) {
                ans = d;
                res = ops;
            }
        }
        cout << ans << endl;
        cout << sz(res) << endl;
        cout << res;
    }
    return 0;
}