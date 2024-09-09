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
#define bug cerr << "!Bugged..." << endl
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)

const vs cq = { "NO", "YES"};
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

        vi ans;
        if (n == 3 or n == 5) {
            if (n == 3) {
                ans.eb(3);
            } else ans.eb(2), ans.eb(3);
        }
        else {
            if (n & 1) ans.eb(3), n -= 3;
            int lim = 4e5 + 5;
            vb isprime(lim, 1);
            isprime[0] = isprime[1] = 0;
            for (int i = 4; i < lim; i += 2) isprime[i] = 0;
            for (int i = 3; i * i < lim; i += 2) {
                if (isprime[i])
                    for (int j = i * i; j < lim; j += 2 * i)
                        isprime[j] = 0;
            }
            auto chk = [&](int x) {
                if (x == 1) return 0;
                for (int i = 2; i * i <= x; i++)
                    if (x % i == 0) return 0;
                return 1;
            };
            for (int i = 2; i < lim; i++)
                if (isprime[i]) {
                    int rem = n - i;
                    if (chk(rem)) {
                        ans.eb(i);
                        ans.eb(rem);
                        break;
                    }
                }
        }
        cout << ans.size() << endl;
        cout << ans;

    }
    return 0;
}
