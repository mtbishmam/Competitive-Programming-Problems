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
template <typename T> ostream& operator<<(ostream& os, set<T>& s) { for (auto i : s) os << i << " "; return os; }
// template <typename T> ostream& operator<<(ostream &os, const vector<T>& v) { os << '{'; string s; for (const auto &x : v) os << s << x, s = " "; return os << '}'; }
template <typename A, typename B> istream& operator>>(istream& is, pair<A, B>& i) { return is >> i.ff >> i.ss; }
template <typename A, typename B> ostream& operator<<(ostream& os, pair<A, B>& i) { return os << i.ff << " " << i.ss; }
template <typename A, typename B> ostream& operator<<(ostream& os, map<A, B>& mp) { for (auto i : mp) os << i << ", "; return os; }
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
using vull = vector<ull>     ;
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
const int N = 1e5 + 1;

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
        int n; cin >> n;
        map<char, ll> mpa, mpb;
        multiset<pll> msa;
        multiset<pll, greater<pll>> msb;
        mpa['a']++; mpb['a']++;
        msa.em('a', 1), msb.em('a', 1);
        // for (char c = 'b'; c <= 'z'; c++) {
        //     msa.em(c, 0);
        //     msb.em(c, 0);
        // }
        for (int i = 0; i < n; i++) {
            int op; cin >> op;
            ll k; string x;
            cin >> k >> x;
            map<char, ll> mp;
            for (auto& i : x) mp[i]++;
            if (op == 1) {
                for (auto& i : mp) {
                    auto it = msa.find({i.ff, mpa[i.ff]});
                    if (it != msa.end()) msa.erase(it);
                    mpa[i.ff] += i.ss * k;
                    msa.em(i.ff, mpa[i.ff]);
                }
            } else {
                for (auto& i : mp) {
                    auto it = msb.find({i.ff, mpb[i.ff]});
                    if (it != msb.end()) msb.erase(it);
                    mpb[i.ff] += i.ss * k;
                    msb.em(i.ff, mpb[i.ff]);
                }
            }

            bool ok = 0;
            auto ta = msa;
            auto tb = msb;
            while (sz(ta) and sz(tb)) {
                auto it = *ta.begin(); ta.erase(it);
                auto jt = *tb.begin(); tb.erase(jt);
                if (it.ff <= jt.ff)
                {
                    if (it.ff == jt.ff)
                    {
                        if (it.ss < jt.ss)
                        {
                            if (!sz(ta)) {
                                ok = 1;
                                break;
                            } else {
                                ok = 0;
                                break;
                            }
                        }
                        else
                        {
                            if (it.ss == jt.ss)
                            {
                                if (!sz(ta))
                                {
                                    if (!sz(tb))
                                    {
                                        ok = 0;
                                        break;
                                    }
                                    else
                                    {
                                        // debug("...");
                                        ok = 1;
                                        break;
                                    }
                                }
                                else
                                {   // i have a char to play
                                    ok = 0;
                                    break;
                                }
                            }
                            else
                            {   // bbbb bbb
                                ok = 0;
                                break;
                            }
                        }
                    }
                    else
                    {
                        // debug("....");
                        ok = 1;
                        break;
                    }
                }
                else
                {
                    ok = 0;
                    break;
                }
            }
            cout << cq[ok] << endl;
        }
    }
    return 0;
}
