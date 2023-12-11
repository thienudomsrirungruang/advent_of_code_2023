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

map<char, vector<pii>> mp;

const pii NORTH = {-1, 0};
const pii SOUTH = {1, 0};
const pii WEST = {0, -1};
const pii EAST = {0, 1};

void gen_map() {
    mp['|'] = vpii({NORTH, SOUTH});
    mp['-'] = vpii({WEST, EAST});
    mp['L'] = vpii({NORTH, EAST});
    mp['J'] = vpii({NORTH, WEST});
    mp['7'] = vpii({SOUTH, WEST});
    mp['F'] = vpii({SOUTH, EAST});
    mp['.'] = vpii({});
    mp['S'] = vpii({NORTH, SOUTH, EAST, WEST});
}

pii operator+(pii p1, pii p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}

void solve(){
    vector<string> input;
    while(true) {
        string s;
        cin >> s;
        if(!cin) break;
        input.push_back(s);
    }

    int n = input.size();
    int m = input[0].size();

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<vector<int>> dist(n, vi(m, -1));

    pii start;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(input[i][j] == 'S') {
                start = {i, j};
            }
        }
    }

    queue<pii> q;
    q.push(start);
    vis[start.first][start.second] = true;
    dist[start.first][start.second] = 0;

    auto inside = [&](pii p) {
        return 0 <= p.first && p.first < n && 0 <= p.second && p.second < m;
    };

    while(!q.empty()) {
        pii u = q.front();
        q.pop();
        char c = input[u.first][u.second];
        for(pii off : mp[c]) {
            pii v = u + off;
            if(!inside(v)) continue;
            pii rev = {-off.first, -off.second};
            char d = input[v.first][v.second];
            if(find(mp[d].begin(), mp[d].end(), rev) == mp[d].end()) continue;
            if(!vis[v.first][v.second]) {
                vis[v.first][v.second] = 1;
                dist[v.first][v.second] = dist[u.first][u.second] + 1;
                q.push(v);
            }
        }
    }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++ ){
    //         cout << dist[i][j] << '\t';
    //     }
    //     cout << endl;
    // }

    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ans = max(ans, dist[i][j]);
        }
    }
    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    gen_map();
    solve();
    return 0;
}
