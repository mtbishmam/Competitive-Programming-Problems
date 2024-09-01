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
        string s; cin >> s;
        map<char, int> mp;
        string suf; int n = sz(s);
        for (int i = n - 1; i >= 0; i--) {
            mp[s[i]]++;
            if (suf.find(s[i]) == -1) suf = s[i] + suf;
        }
        bool fok = 1;
        vpii a; string ord = suf;
        while (sz(suf)) {
            char c = suf.back();
            // fok &= mp[c] % sz(suf) == 0;
            a.eb(c, mp[c] / sz(suf));
            suf.pop_back();
        }
        map<char, int> ot;
        for (auto& p : a)
            ot[p.ff] = p.ss;
        bool ok = 0;
        string cur, ans;
        int i = 0;
        while (i < sz(s)) {
            cur += s[i];
            ans += s[i];
            ot[s[i]]--;
            if (ot[s[i]] < 0) ok = 0;
            i++;
            bool done = 1;
            for (auto& j : ot) done &= !j.ss;
            if (done) {
                ok = 1;
                break;
            }
        } fok &= ok;
        int j = 0; string t;
        while (j < sz(ord)) {
            t += cur;
            string ncur;
            for (auto& c : cur)
                if (c != ord[j]) ncur += c;
            cur = ncur;
            j++;
        }
        if (t == s) cout << ans << " " << ord;
        else cout << -1;
        cout << endl;
    }
    return 0;
}
