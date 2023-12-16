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

int n, m;

pii DIRS[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

vi nxt(char c, int x) {
    if(c == '/') {
        return vector<int>{x ^ 1};
    }
    if(c == '\\') {
        return vector<int>{x ^ 3};
    }
    if(c == '-' && (x == 0 || x == 2)) {
        return vector<int>{1, 3};
    }
    if(c == '|' && (x == 1 || x == 3)) {
        return vector<int>{0, 2};
    }
    return vector<int>{x};
}

using pipii = pair<int, pii>;

pii operator+(pii p, pii q) {
    return {p.first+q.first, p.second+q.second};
}

void solve(){
    vector<string> grid;
    while(true){
        string s;
        cin >> s;
        if(!cin) break;
        grid.push_back(s);
    }
    n = grid.size();
    m = grid[0].size();

    auto inside = [&](pii p) {
        return 0 <= p.first && p.first < n && 0 <= p.second && p.second < m;
    };

    set<pipii> vis;
    vis.insert({1, {0, 0}});
    queue<pipii> q;
    q.push({1, {0, 0}});
    vector<vector<bool>> ok(n, vector<bool>(m));
    ok[0][0] = true;
    int ans = 1;
    while(!q.empty()) {
        int dir;
        pii pos;
        tie(dir, pos) = q.front();
        q.pop();
        for(int nd : nxt(grid[pos.first][pos.second], dir)) {
            pii np = pos + DIRS[nd];
            if(!inside(np)) continue;
            pipii state = {nd, np};
            if(vis.find(state) == vis.end()) {
                q.push(state);
                vis.insert(state);
                if(!ok[np.first][np.second]) {
                    ans++;
                    ok[np.first][np.second] = true;
                }
            }
        }
    }
    debug(ok);
    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
