#include <bits/stdc++.h>

using namespace std;

#define u_map unordered_map
#define u_set unordered_set
#define u_multiset unordered_multiset

using ll = long long;
using vvi = vector<vector<int>>;
using vi = vector<int>;
using vvll = vector<vector<long long>>;
using vll = vector<long long>;
using vd = vector<double>;
using vvd = vector<vector<double>>;
using pii = pair<int, int>;
using vpii = vector<pair<int, int>>;

template<typename C> struct rge{C l, r;};
template<typename C> rge<C> range(C i, C j) { return rge<C>{i, j}; }
template<typename C> ostream& operator<<(ostream &os, rge<C> &r) { os << '{'; for(auto it = r.l; it != r.r; it++) os << "," + (it == r.l) << *it; os << '}'; return os; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '{' << p.first << "," << p.second << '}'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ","; return os << '}'; }
void dbg_out() { cerr << ']' << endl; }
template<typename A> void dbg_out(A H) { cerr << H; dbg_out(); }
template<typename A, typename B, typename... C> void dbg_out(A H, B G, C... T) { cerr << H << ","; dbg_out(G, T...); }
#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = [", dbg_out(__VA_ARGS__)
#else
#define debug(...)
#endif

pii operator+(pii p, pii q) {
    return {p.first + q.first, p.second + q.second};
}

map<char, vector<pii>> dirs;

int ans = 0;

void search(vector<string> &g, int n, int m, pii cur, pii target, vector<vector<bool>> &vis, int d) {
    if(cur == target) {
        ans = max(ans, d);
        return;
    }
    for(pii dir : dirs[g[cur.first][cur.second]]) {
        pii nxt = cur + dir;
        if(nxt.first < 0) continue;
        if(!vis[nxt.first][nxt.second]) {
            vis[nxt.first][nxt.second] = true;
            search(g, n, m, nxt, target, vis, d+1);
            vis[nxt.first][nxt.second] = false;
        }
    }
}

void solve(){
    dirs['<'] = vector<pii>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    dirs['>'] = vector<pii>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    dirs['^'] = vector<pii>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    dirs['v'] = vector<pii>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    dirs['.'] = vector<pii>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    vector<string> g;
    while(true) {
        string s;
        cin >> s;
        if(!cin) break;
        g.push_back(s);
    }
    int n = g.size();
    int m = g[0].size();

    g[0][1] = 'v';

    vector<vector<bool>> vis(n, vector<bool>(m));
    search(g, n, m, {0, 1}, {n-1, m-2}, vis, 0);

    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
