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
    // cin >> ttt;
    for (int itt = 1; itt <= ttt; itt++)
    {
        int n;
        cin >> n;
        vi a(n); cin >> a;
        sort(all(a));
        if (n == 1) cout << -1;
        else if (n == 2) {
            vi ans;
            ll diff = a[1] - a[0];
            if (diff % 2 == 0)
                ans.eb(a[0] + diff / 2);
            ans.eb(a[0] - diff);
            ans.eb(a[1] + diff);
            sort(all(ans));
            ans.erase(unique(all(ans)), ans.end());
            cout << ans.size() << endl;
            cout << ans;
        }
        else {
            map<int, int> mp;
            for (int i = 1; i < n; i++)
                mp[a[i] - a[i - 1]]++;
            if (mp.size() == 1) {
                vi ans;
                ll diff = a[1] - a[0];
                ans.eb(a[0] - diff);
                ans.eb(a[n - 1] + diff);
                sort(all(ans));
                ans.erase(unique(all(ans)), ans.end());
                cout << ans.size() << endl;
                cout << ans;
            }
            else if (mp.size() == 2 and mp.rbegin()->ss == 1) {
                ll diff1 = mp.begin()->ff;
                ll diff2 = mp.rbegin()->ff;
                if (diff2 % 2 == 0 and diff2 / 2 == diff1) {
                    for (int i = 1; i < n; i++) {
                        if (a[i] - a[i - 1] == diff2) {
                            cout << 1 << endl;
                            cout << a[i - 1] + diff1 << endl;
                            exit(0);
                        }
                    }
                }
                else cout << 0 << endl;
            }
            else cout << 0 << endl;
        }

    }
    return 0;
}
