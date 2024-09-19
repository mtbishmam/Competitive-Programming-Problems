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
using vvpii = vector<vpii>  ; using tiii = tuple<int, int, int>;
using vtiii = vector<tiii>  ;
template <class A, class B> using umap = unordered_map<A, B>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)

const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1};
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1};
const int INF = 2147483647;
const ll LINF = 9223372036854775807;
const int MOD = 1e9 + 7;
// const int maxn = 10 + 1;
const int imaxn = 1000;
const int jmaxn = 50;
const int kmaxn = 300;
int dp[imaxn][jmaxn][kmaxn];

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
        ll a, b, c;
        cin >> a >> b >> c;
        memset(dp, -1, sizeof dp);
        function<int(int, int, int)> f = [&](int i, int j, int k) {
            int& ret = dp[i][j][k];
            if (~ret) return ret;

            ret = 0;
            if (i >= 2 and j >= 1) ret = max(ret, 1 + f(i - 2, j - 1, k));
            if (i >= 2 and k >= 1) ret = max(ret, 1 + f(i - 2, j, k - 1));

            if (j >= 2 and i >= 1) ret = max(ret, 1 + f(i - 1, j - 2, k));
            if (j >= 2 and k >= 1) ret = max(ret, 1 + f(i, j - 2, k - 1));

            if (k >= 2 and i >= 1) ret = max(ret, 1 + f(i - 1, j, k - 2));
            if (k >= 2 and j >= 1) ret = max(ret, 1 + f(i, j - 1, k - 2));

            if (i and j and k) ret = max(ret, 1 + f(i - 1, j - 1, k - 1));
            return ret;
        };
        auto solve = [](ll r, ll g, ll b) -> ll {
            vl a = {r, g, b}; sort(all(a));
            if (!a[0] and !a[1]) return 0;
            if (!a[0]) return min((a[1] + a[2]) / 3, a[1]);
            ll ret = (r + g + b) / 3;
            ret = min(ret, a[0] + a[1]);
            return ret;
            // return min({(r + g + b) / 3, a[2] / 2, a[0] + a[1]});
        };
        // for (int i = 0; i < imaxn; i++)
        //     for (int j = 0; j < jmaxn; j++)
        //         for (int k = 0; k < kmaxn; k++) {
        //             int x = solve(i, j, k);
        //             int y = f(i, j, k);
        //             if (x != y) {
        //                 cout << i << " " << j << " " << k << " -> " << x << " " << y << endl;
        //             }
        //             // cout << solve(i, j, k) << " " << f(i, j, k) << endl;
        //         }

        cout << solve(a, b, c) << endl;
    }
    return 0;
}
