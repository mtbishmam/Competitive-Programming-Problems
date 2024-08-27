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
// template <typename T> ostream& operator<<(ostream& os, vector<T>& a) { for (auto& i : a) os << i << " "; return os; };
template <typename T> ostream& operator<<(ostream& os, const vector<T>& v) { os << '{'; string s; for (const auto& x : v) os << s << x, s = " "; return os << '}'; }
template <typename A, typename B> istream& operator>>(istream& is, pair<A, B>& i) { return is >> i.ff >> i.ss; }
// template <typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& i) { return os << i.ff << " " << i.ss; }
template <typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& i) { return os << '{' << i.ff << ", " << i.ss << '}'; }
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
        int n;
        cin >> n; n *= 2;
        vi a(n);
        cin >> a;
        a.insert(a.begin(), 0);

        using ob = pair<int, vi>;
        vector<ob> sets; vb vis(n + 1);
        for (int i = n; i >= 1; i--) {
            if (vis[i]) continue;
            vi cur; int j;
            for (j = 1; j <= n; j++) {
                if (a[j] == i) break;
            }
            for (int k = j; k <= n; k++) {
                if (vis[a[k]]) break;
                vis[a[k]] = 1;
                cur.eb(a[k]);
            }
            sets.pb({n - i + 1, cur});
        }
        vvi dp(sets.size(), vi(n / 2 + 5, -1));
        function<int(int, int)> f = [&](int i, int j) -> int {
            if (j >= n / 2) return j == n / 2;
            if (i >= sets.size()) return 0;
            int& ret = dp[i][j];
            if (~ret) return ret;
            ret = 0;
            ret |= f(i + 1, sets[i].ss.size() + j);
            ret |= f(i + 1, j);
            return ret;
        };
        cout << cq[f(0, 0)] << endl;
        // debug(sets);
        // int an = 0, bn = 0;
        // for (int i = 0, j = int(sets.size()) - 1; i <= j; i++, j--) {
        //     if (i == j) {
        //         if (an <= bn) an += sets[i].ss.size();
        //         else bn += sets[i].ss.size();
        //     }
        //     else an += sets[i].ss.size(), bn += sets[j].ss.size();
        // }
        // debug(sets);
        // sort(all(sets), [](ob & a, ob & b) {
        //     if (a.ss.size() == b.ss.size()) return a.ff < b.ff;
        //     else return a.ss.size() > b.ss.size();
        // });

        // vector<ob> aa, bb; int an, bn; an = bn = 0;
        // for (auto& cs : sets) {
        //     if (an <= bn) aa.pb(cs), an += cs.ss.size();
        //     else bb.pb(cs), bn += cs.ss.size();
        // }
        // sort(all(aa), [](ob & a, ob & b) { return a.ff > b.ff; });
        // sort(all(bb), [](ob & a, ob & b) { return a.ff > b.ff; });
        // vi fa, fb, fans;
        // for (auto& i : aa) for (auto& j : i.ss) fa.eb(j);
        // for (auto& i : bb) for (auto& j : i.ss) fb.eb(j);
        // // debug(fa);
        // // debug(fb);
        // if (fa.size() == fb.size())
        //     for (int i = 0, j = 0;;) {
        //         if (i >= fa.size() and j >= fb.size()) break;
        //         if (i < fa.size() and j < fb.size()) {
        //             if (fa[i] < fb[j]) fans.eb(fa[i]), i++;
        //             else fans.eb(fb[j]), j++;
        //         } else {
        //             if (i < fa.size()) fans.eb(fa[i]), i++;
        //             else fans.eb(fb[j]), j++;
        //         }
        //     }
        // // debug(a, n);
        // // debug(fans, fans.size());
        // bool ok = 1;
        // if (fans.size() == n)
        //     for (int i = 1; i <= n; i++)
        //         ok &= fans[i - 1] == a[i];
        // else ok = 0;
        // cout << cq[ok] << endl;
        // cout << cq[an == bn] << endl;
        // // cout << endl;
    }
    return 0;
}
