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

struct Point {
    int x;
    int y;
    int z;
};

ostream& operator<<(ostream& os, Point p) {
    return os << '{' << p.x << ' ' << p.y << ' ' << p.z << '}';
}

struct Block {
    Point a;
    Point b;

    int min_z() {
        return min(a.z, b.z);
    }
    
    int max_z() {
        return max(a.z, b.z);
    }

    vector<Point> pts() {
        vector<Point> out;
        for(int x = min(a.x, b.x); x <= max(a.x, b.x); x++) {
            for(int y = min(a.y, b.y); y <= max(a.y, b.y); y++) {
                for(int z = min(a.z, b.z); z <= max(a.z, b.z); z++) {
                    Point p;
                    p.x = x;
                    p.y = y;
                    p.z = z;
                    out.push_back(p);
                }
            }
        }
        return out;
    }

    // ot over self
    int xy_collide(Block ot) {
        int ans = 1;
        for(Point p : pts()) {
            for(Point q : ot.pts()) {
                if(p.x == q.x && p.y == q.y && p.z < q.z) {
                    ans = max(ans, p.z + 1);
                }
            }
        }
        return ans;
    }

    // does self support ot?
    bool support(Block ot) {
        return xy_collide(ot) == ot.min_z();
    }

    void fall_to(int z) {
        int dz = min(a.z - z, b.z - z);
        assert(dz >= 0);
        a.z -= dz;
        b.z -= dz;
    }
};

void solve(){
    int n;
    cin >> n;

    vector<Block> blocks;
    for(int i = 0; i < n; i++) {
        Block b;
        cin >> b.a.x >> b.a.y >> b.a.z >> b.b.x >> b.b.y >> b.b.z;
        blocks.push_back(b);
    }

    sort(blocks.begin(), blocks.end(), [&](Block p, Block q) {return p.min_z() < q.min_z(); });

    for(int i = 0; i < n; i++) {
        int fall = 1;
        for(int j = 0; j < i; j++) {
            fall = max(fall, blocks[j].xy_collide(blocks[i]));
        }
        blocks[i].fall_to(fall);
    }

    for(int i = 0; i < n; i++) {
        debug(i, blocks[i].a, blocks[i].b);
    }

    vector<bool> good(n, true);
    for(int i = 0; i < n; i++) {
        vi supports;
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            if(blocks[j].support(blocks[i])) {
                supports.push_back(j);
            }
        }
        debug(i, supports);
        if(supports.size() == 1) {
            good[supports[0]] = false;
        }
    }
    debug(good);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(good[i]) ans++;
    }
    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
