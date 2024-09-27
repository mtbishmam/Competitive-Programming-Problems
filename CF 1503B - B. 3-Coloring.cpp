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

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//template<typename T> using ordered_set = tree<T, null_type , less<T> , rb_tree_tag , tree_order_statistics_node_update>;

using namespace std;
//using namespace __gnu_pbds;

#define pb push_back
#define eb emplace_back
#define endl "\n"
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

#define add(a, b) (a + b >= MOD ? a + b - MOD : a + b)
#define all(x) (x).begin(), (x).end()
#define unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define tolower(x) transform(all(x), x.begin(), ::tolower)
#define toupper(x) transform(all(x), x.begin(), ::toupper)
#define remove_all(x, y) x.erase(remove(all(x), char(y)), x.end());

#define input(in) freopen(in, "r", stdin)
#define output(out) freopen(out, "w", stdout)

const int INF = 1e9;
const ll LINF = 1e17;
const double EPS = 1e-10;
const double gam = 0.5772156649015328606; //euler's constant
const double PI = acos(-1.0);
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int dxx[] = {1, 0, -1, 0, 1, -1, -1, 1};
int dyy[] = {0, 1, 0, -1, 1, 1, -1, -1};
const int MOD = 1000000007;

//mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

template <typename type>
inline type gcd(type a, type b)
{
    if (b)
        while ((a %= b) && (b %= a))
            ;
    return a + b;
}
template <typename type>
inline type lcm(type a, type b) { return a / gcd(a, b) * b; }
inline long long binexpo(long long x, long long y, long long mod = MOD)
{
    long long res = 1ll;
    while (y)
    {
        if (y & 1)
            res = ((res % mod) * (x % mod)) % mod;
        x = ((x % mod) * (x % mod)) % mod, y >>= 1;
    }
    return res;
}

template <typename istream, typename type>
inline istream &operator>>(istream &cin, vector<type> &x)
{
    for (int i = 0; i < x.size(); i++)
        cin >> x[i];
    return cin;
}
template <typename ostream, typename type>
inline ostream &operator<<(ostream &cout, const vector<type> &x)
{
    for (int i = 0; i < x.size(); i++)
        cout << x[i] << " \n"[i + 1 == x.size()];
    return cout;
}

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

#define deb(x)                                                  \
    int idx = 0;                                                \
    for (auto i : x)                                            \
    {                                                           \
        cout << #x << '[' << idx << "] = " << i << endl, idx++; \
    }
template <typename T, typename V>
void __print(const pair<T, V> &x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T &x)
{
    int f = 0;
    cerr << '{';
    for (auto &i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}
#define debug(x...)               \
    cerr << "[" << #x << "] = ["; \
    _print(x)

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> vp[2];
    vector<int> col{1, 2, 3};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            vp[(i + j) % 2].eb(i, j);

    for (int i = 1, x, col; i <= n * n; i++)
    {
        cin >> x;
        if (x == 1)
        {
            if (vp[0].size())
                col = 0, x = 2;
            else
                col = 1, x = 3;
        }
        else if (x == 2)
        {
            if (vp[1].size())
                col = 1, x = 1;
            else
                col = 0, x = 3;
        }
        else
        {
            if (vp[0].size())
                col = 0, x = 2;
            else
                col = 1, x = 1;
        }

        cout << x << " " << vp[col].back().first << " " << vp[col].back().second << endl
             << endl;
        vp[col].pop_back();
        cout.flush();
    }
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
