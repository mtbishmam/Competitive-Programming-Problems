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
    cin >> T;
    for (int Ti = 1; Ti <= T; Ti++)
    {
        int n, m;
        cin >> n >> m;
        vs a(n); cin >> a;
        string s; cin >> s;
        vi dp(m, -1);
        vector<tiii> res;
        function<int(int)> f = [&](int i) -> int {
            if (i == m) return 1;
            int& ret = dp[i];
            if (~ret) return ret;
            ret = 0; int curres = 0, css = 0, can = 0;
            if (i + 1 < m)
                for (auto& cs : a) {
                    css++;
                    for (int j = 1; j < m; j++) {
                        if (cs[j - 1] == s[i] and cs[j] == s[i + 1]) {
                            curres = f(i + 2);
                            if (curres) {
                                res.eb(j, j + 1, css);
                                can = 1;
                                break;
                            }
                            if (i + 2 < m and j + 1 < m) {
                                if (cs[j + 1] == s[i + 2]) {
                                    curres = f(i + 3);
                                    if (curres) {
                                        res.eb(j, j + 2, css);
                                        can = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (can) break;
                }
            ret |= curres;
            return ret;
        };
        int ans = f(0);
        if (!ans) cout << -1;
        else {
            // function<void(int, int)> build = [&](int i, int cur) {
            //     if (i == m) return;

            //     int css = 0, can = 0;
            //     if (i + 1 < m)
            //         for (auto& cs : a) {
            //             css++;
            //             for (int j = 1; j < m; j++) {
            //                 if (cs[j - 1] == s[i] and cs[j] == s[i + 1]) {
            //                     if (1 + f(i + 2) == cur) {
            //                         res.eb(j, j + 1, css);
            //                         build(i + 2, cur - 1);
            //                         can = 1;
            //                         break;
            //                     }
            //                     if (i + 2 < m and j + 1 < m) {
            //                         if (cs[j + 1] == s[i + 2] and 1 + f(i + 3) == cur) {
            //                             res.eb(j, j + 2, css);
            //                             build(i + 3, cur - 1);
            //                             can = 1;
            //                             break;
            //                         }
            //                     }
            //                 }
            //             }
            //             if (can) break;
            //         }
            // };
            // build(0, ans);
            cout << res.size() << endl;
            reverse(all(res));
            for (auto&[l, r, i] : res)
                cout << l << " " << r << " " << i << endl;
        }
        cout << endl;
    }
    return 0;
}
