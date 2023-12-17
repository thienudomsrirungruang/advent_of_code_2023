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

pii DIRS[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct State {
    int last_dir;
    int times;
    pii pos;
};

bool operator< (State x, State y) {
    return x.pos < y.pos || (x.pos == y.pos && (x.times < y.times || (x.times == y.times && x.last_dir < y.last_dir)));
}

pii operator+(pii p, pii q) {
    return {p.first+q.first, p.second+q.second};
}

void solve(){
    vector<string> input;
    while(true){
        string s;
        cin >> s;
        if(!cin) break;
        input.push_back(s);
    }
    int n = input.size();
    int m = input[0].size();

    map<State, int> dist;

    set<State> vis;

    set<pair<int, State>> q;

    State start;
    start.last_dir = 0;
    start.times = 0;
    start.pos = {0, 0};

    q.insert({0, start});

    int ans = 1e9;

    auto inside = [&](pii p) {
        return 0 <= p.first && p.first < n && 0 <= p.second && p.second < m;
    };

    while(!q.empty()) {
        State s;
        int d;

        tie(d, s) = *q.begin();

        debug(s.pos, d);

        q.erase(q.begin());
        if(vis.find(s) != vis.end()) continue;
        vis.insert(s);

        if(s.pos.first == n-1 && s.pos.second == m-1) {
            ans = min(ans, d);
        }

        for(int i = 0; i < 4; i++) {
            if(i == (s.last_dir ^ 2)) continue;
            State nxts;
            nxts.pos = s.pos + DIRS[i];
            if(s.last_dir == i) {
                nxts.times = s.times + 1;
            } else {
                nxts.times = 1;
            }
            nxts.last_dir = i;
            if(!inside(nxts.pos)) continue;
            if(nxts.times > 3) continue;
            q.insert({d + (input[nxts.pos.first][nxts.pos.second] - '0'), nxts});
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
