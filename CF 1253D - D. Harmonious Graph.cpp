#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <iomanip>
#include <cstring>

// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//template<typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using namespace std;
//using namespace __gnu_pbds;

#define pb push_back
#define eb emplace_back
#define endl "\n"
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define ff first
#define ss second

template <class T>
using pq = priority_queue<T>;
template <class T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define add(a, b) (a + b >= MOD ? a + b - MOD : a + b)
#define all(x) (x).begin(), (x).end()
#define unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define tolower(x) transform(all(x), (x).begin(), ::tolower)
#define toupper(x) transform(all(x), (x).begin(), ::toupper)
#define remove_all(x, y) (x).erase(remove(all(x), char(y)), (x).end());

#define input(in) freopen(in, "r", stdin)
#define output(out) freopen(out, "w", stdout)

const int INF = 1e9;
const ll LINF = 1e17;
// const double EPS = 1e-10;
// const double gam = 0.5772156649015328606; //euler's constant
// const double PI = acos(-1.0);
const int dx[8] = {-1, 0, 0, 1, 1, 1, -1, -1};
const int dy[8] = {0, -1, 1, 0, 1, -1, 1, -1};
// const int dxx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
// const int dyy[8] = {2, -2, 1, -1, 2, -2, 1, -1};
const int MOD = 1000000007;
const int maxn = 2e5 + 10;
//mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

vector<int> par(maxn), mn(maxn), mx(maxn);
vector<bool> vis(maxn);

int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }

void unite(int x, int y)
{
    x = find(x), y = find(y);
    if (x != y)
    {
        par[x] = y;
        mn[y] = min(mn[x], mn[y]);
        mx[y] = max(mx[x], mx[y]);
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        par[i] = mn[i] = mx[i] = i;

    for (int i = 1, x, y; i <= m; i++)
        cin >> x >> y, unite(x, y);

    int ans(0);
    for (int i = 1; i <= n; i++)
    {
        int x = find(i);
        if (!vis[x])
        {
            vis[x] = 1;
            for (int j = mn[x]; j <= mx[x]; j++)
                if (x != find(j))
                    unite(j, x), ans++;
        }
    }

    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int t(1);
    // cin >> t;
    while (t--)
        solve();

    return 0;
}
