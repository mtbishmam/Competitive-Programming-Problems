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
        int n, m;
        cin >> n >> m;
        vi p(n + 1), h(n + 1);
        for (int i = 1; i <= n; i++) cin >> p[i];
        for (int i = 1; i <= n; i++) cin >> h[i];
        vvi g(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int a, b; cin >> a >> b;
            g[a].eb(b), g[b].eb(a);
        }
        vi sz(n + 1);
        function<void(int, int)> f = [&](int node, int par) {
            sz[node] = p[node];
            for (auto& child : g[node])
                if (child != par) {
                    f(child, node);
                    sz[node] += sz[child];
                }
        }; f(1, -1);
        // cout << sz << endl;
        bool ok = 1;
        vpii mood(n + 1);
        function<void(int, int, int, int)> chk = [&](int node, int par, int phap, int psed) {
            int tot = sz[node], given = h[node];
            int _2h = tot + given;
            int hap = _2h / 2, sed = tot - hap;
            mood[node] = {hap, sed};

            bool f = 0;
            if (hap < 0 or sed < 0 or _2h % 2 or hap + sed != tot) ok = 0;

            // if (sed > phap) ok = 0 // sure...
            // if (psed >= sed and phap >= psed - sed);
            // else ok = 0;

            // all child sed cnt >= node sed cnt..
            // all child new seds <= node hap cnt...

            // if(sed > phap or hap > phap) {
            //     ok = 0;
            //     debug(phap, psed);
            //     debug(hap, sed);
            // }

            // if (sed > psed) ok = 0;

            int cntsed = 0, cnthap = 0, leaf = 1;
            for (auto& child : g[node]) {
                if (child != par) {
                    chk(child, node, hap, sed);
                    cnthap += mood[child].ff;
                    cntsed += mood[child].ss;
                    leaf = 0;
                }
            }
            if (ok) {f = 1;}
            if (!leaf) {
                if (cntsed - sed <= hap and hap >= cnthap);
                else ok = 0;
            }
            if (f and !ok) {
                // debug(node);
                // debug(cntsed, cnthap);
                // debug(sed, hap);
            }
        }; chk(1, -1, INF, INF);

        cout << cq[ok] << endl;

    }
    return 0;
}
