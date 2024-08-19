#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <array>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <iomanip>
#include <cstring>
using namespace std;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename T, size_t size> ostream& operator<<(ostream &os, const array<T, size> &arr) { os << '{'; string sep; for (const auto &x : arr) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#define endl "\n"
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define lb lower_bound
#define ub upper_bound

typedef long long ll;
typedef long double ld;
template <class T> using v = vector<T>;
template <class T> using pql = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
template <class T1, class T2> using p = pair<T1, T2>;
template <class T1, class T2, class T3> using t = tuple<T1, T2, T3>;
template <class T1, class T2> using umap = unordered_map<T1, T2>;

#define add(a, b) (a + b >= MOD ? a + b - MOD : a + b)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define size(x) int(x.size())

const int dx[8] = { -1, 0, 0, 1, 1, 1, -1, -1};
const int dy[8] = {0, -1, 1, 0, 1, -1, 1, -1};
const int INF = 2147483647;
const ll LINF = 9223372036854775807;
const int MOD = 1000000007;
const int maxn = 2e5 + 1;

v<int> sg(4 * maxn), lazy(4 * maxn);
void combine(int i) { sg[i] = sg[i * 2] + sg[i * 2 + 1]; }
void propagate(int i, int start, int end) {
	sg[i] += lazy[i];
	if (start != end) {
		lazy[i * 2] += lazy[i], lazy[i * 2 + 1] += lazy[i];
	}
	lazy[i] = 0;
}
int query(int l, int r, int i, int start, int end) {
	propagate(i, start, end);
	if (l <= start and end <= r)
		return sg[i];
	else if (end < l or r < start)
		return 0;
	int mid = start + end >> 1;
	int ll = query(l, r, i * 2, start, mid);
	int rr = query(l, r, i * 2 + 1, mid + 1, end);
	return ll + rr;
}
void update(int val, int l, int r, int i, int start, int end) {
	propagate(i, start, end);
	if (l <= start and end <= r) {
		lazy[i] += val;
		propagate(i, start, end);
		return;
	}
	if (end < l or r < start)
		return;
	int mid = start + end >> 1;
	update(val, l, r, i * 2, start, mid);
	update(val, l, r, i * 2 + 1, mid + 1, end);
	combine(i);
}

int main()
{
#ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	freopen("error.txt", "a", stderr);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	int ttt(1);
	// cin >> ttt;
	for (int itt = 1; itt <= ttt; itt++)
	{
		int n;
		string s, t;
		cin >> n >> s;
		v<int> a[26];
		for (int i = n - 1; i >= 0; i--) {
			a[s[i] - 'a'].eb(i);
			t += s[i];
		}
		ll ans(0);
		for (int i = 0; i < n; i++) {
			int pos = a[t[i] - 'a'].back() + 1; // 1-indexing it
			a[t[i] - 'a'].pop_back();
			int offset = query(pos, n, 1, 1, n);
			ans += pos - i + offset - 1; // decrementing the extra +1
			update(1, pos, pos, 1, 1, n);
		}
		cout << ans;
	}
	return 0;
}
