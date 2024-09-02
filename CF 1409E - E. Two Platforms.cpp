
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
#define bug(x) cerr << #x << endl
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
        int n, k;
        cin >> n >> k;
        vi a(n), b(n);
        for (auto& i : a) cin >> i;
        for (auto& i : b) cin >> i;
        sort(all(a));
        vvi dp(n + 5, vi(5, -1));
        for (int i = n; i >= 0; i--)
            for (int j = 2; j >= 0; j--) {
                int& ret = dp[i][j];
                if (j >= 2) ret = 0;
                else if (i >= n) {
                    if (j >= 1) ret = 0;
                    else ret = -INT_MAX / 1000;
                }
                else {
                    ret = 0;
                    auto it = ub(all(a), a[i] + k);
                    int len = it - (a.begin() + i);
                    ret = max(ret, len + (i + len <= n ? dp[i + len][j + 1] : 0));
                    ret = max(ret, dp[i + 1][j]);
                }
            }

        cout << dp[0][0] << endl;
    }
    return 0;
}
