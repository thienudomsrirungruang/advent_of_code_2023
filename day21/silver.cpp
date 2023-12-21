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

pii DIRS[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

pii operator+(pii x, pii y) {
    return {x.first+y.first, x.second+y.second};
}

const int STEPS = 64;

void solve(){
    vector<string> g;
    while(true) {
        string s;
        cin >> s;
        if(!cin) break;
        g.push_back(s);
    }

    int n = g.size();
    int m = g[0].size();

    pii start;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] == 'S') {
                start = {i, j};
            }
        }
    }

    vvi dist(n, vi(m));

    debug(n, m);

    vector<vector<bool>> vis(n, vector<bool>(m));
    queue<pii> q;
    q.push(start);
    vis[start.first][start.second] = true;

    auto inside = [&](pii p) {
        return 0 <= p.first && p.first < n && 0 <= p.second && p.second < m;
    };

    while(!q.empty()) {
        pii u = q.front();
        q.pop();
        for(int j = 0; j < 4; j++) {
            pii d = DIRS[j];
            pii v = u + d;
            if(inside(v) && g[v.first][v.second] != '#' && !vis[v.first][v.second]) {
                vis[v.first][v.second] = true;
                dist[v.first][v.second] = dist[u.first][u.second] + 1;
                q.push(v);
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(vis[i][j]) {
                int d = dist[i][j];
                if(d % 2 == STEPS % 2 && d <= STEPS) {
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
