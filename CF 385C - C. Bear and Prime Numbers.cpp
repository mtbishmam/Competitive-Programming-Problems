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
const int INF = 2147483647;
const ll LINF = 9223372036854775807;
const int MOD = 1e9 + 7;
const int maxn = 1e7 + 100;
// int spf[maxn + 100], cnt[maxn + 100], pre[maxn + 100];
int con[maxn + 100], cnt[maxn + 100];
vb isprime(maxn + 100, 1);

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
        vi a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i], cnt[a[i]]++;
        // for (int i = 0; i < maxn; i++)
        //     spf[i] = i;
        // for (int i = 2; i < maxn; i += 2)
        //     spf[i] = 2;
        // for (int i = 3; i * i < maxn; i += 2) {
        //     if (spf[i] == i) {
        //         for (int j = i * i; j < maxn; j += 2 * i)
        //             if (spf[j] == j)
        //                 spf[j] = i;
        //     }
        // }

        // for (int i = 0; i < n; i++) {
        //     int x = a[i];
        //     while (x != 1) {
        //         cnt[spf[x]]++;
        //         int y = spf[x];
        //         while (x % y == 0)
        //             x /= y;
        //     }
        // }
        isprime[0] = isprime[1] = 0;
        for (int i = 2; i < maxn; i += 2) {
            con[2] += cnt[i];
            if (i != 2) isprime[i] = 0;
        }
        for (int i = 3; i * i < maxn; i += 2)
            if (isprime[i])
                for (int j = i; j < maxn; j += i) {
                    con[i] += cnt[j];
                    if (i != j) isprime[j] = 0;
                }

        // for (int i = 0; i < maxn; ++i)
        //     if (isprime[i]) cout << i << " ";
        // cout << endl;

        // for (int i = 0; i < n; i++)
        //     cout << a[i] << " " << cnt[a[i]] << endl;

        vpii pre;
        sort(all(a));
        pre.eb(0, 0);
        for (int i = 2; i < maxn; i++) {
            if (isprime[i]) {
                int prev = pre.back().ss;
                pre.eb(i, con[i]);
                pre.back().ss += prev;
            }
        }
        // for (int i = 0; i < a.size(); i++)
        //     if (cnt[a[i]]) {
        //         int prev = pre.back().ss;
        //         pre.eb(a[i], con[a[i]]);
        //         pre.back().ss += prev;
        //         cnt[a[i]] = 0;
        //     }

        // for (int i = 0; i < pre.size(); i++)
        //     cout << pre[i].ff << " " << pre[i].ss << endl;

        // for (int i = 1; i <= maxn; ++i)
        //     pre[i] += pre[i - 1] + cnt[i];

        int q;
        cin >> q;
        while (q--) {
            int l, r;
            cin >> l >> r;
            auto it = lower_bound(all(pre), pii{l, 0});
            auto jt = upper_bound(all(pre), pii{r, INF});
            l = it - pre.begin();
            r = jt - pre.begin();
            cout << pre[r - 1].ss - pre[l - 1].ss << endl;
        }
    }
    return 0;
}
