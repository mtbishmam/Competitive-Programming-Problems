#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <iomanip>
#include <cassert>
using namespace std;

#define endl "\n"
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define lb lower_bound
#define ub upper_bound

using ll = long long; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vs  = vector<string>;
using vi = vector<int>; using vvi = vector<vi>;
using vl = vector<ll>; using vvl = vector<vl>;
using vb = vector<bool>; using vvb = vector<vb>;
using vc  = vector<char>; using vvc = vector<vc>;
using vpii  = vector<pii>; using vpll = vector<pll>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

const string cq[2] = {"NO", "YES"};
const int MOD = 1e9 + 7;
const int maxn = 1e5 + 1;

int main()
{
#ifndef ONLINE_JUDGE
#define bug(x) cerr << #x << "=" << x << endl
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
        int n; cin >> n;
        vvi g(n + 1);
        for (int i = 1, x, y; i < n; ++i) {
            cin >> x >> y;
            g[x].eb(y);
            g[y].eb(x);
        }
        int k; cin >> k;
        vl a(k); for (auto& i : a) cin >> i;
        vl sub(n + 1, 1);
        function<void(int, int)> f = [&](int node, int par) {
            for (auto& child : g[node])
                if (child != par) {
                    f(child, node);
                    sub[node] += sub[child];
                }
        }; f(1, -1);
        vl nt;
        function<void(int, int)> fk = [&](int node, int par) {
            if (node != 1) nt.eb(sub[node] * (n - sub[node]));
            for (auto& child : g[node])
                if (child != par) {
                    fk(child, node);
                }
        }; fk(1, -1);
        while (sz(a) < sz(nt)) a.eb(1);
        sort(all(a));
        while (sz(a) > sz(nt)) {
            ll x = a.back(); a.pop_back();
            a.back() = a.back() * x % MOD;
        }
        sort(all(nt));
        // for (auto& i : nt) cerr << i << " "; cerr << endl;
        // for (auto& i : a) cerr << i << " "; cerr << endl;
        ll ans = 0;
        for (int i = 0; i < sz(nt); i++) {
            ans = (ans + (nt[i] % MOD) * a[i] % MOD) % MOD;
        }
        cout << ans << endl;

    }
    return 0;
}
