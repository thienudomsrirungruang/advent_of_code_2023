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

int t = 0;

set<string> important;
map<string, vi> on_times;

struct Node {
    string name;
    bool is_comb; // otherwise is flip
    map<string, bool> inputs;
    vector<string> in;
    vector<string> dest;
    bool state = false;

    void get_signal(pair<string, bool> signal, queue<pair<string, pair<string, bool>>> &q) {
        string ot;
        bool s;
        tie(ot, s) = signal;
        inputs[ot] = s;

        bool out;
        if(name == "broadcaster") {
            out = s;
        } else if(is_comb) {
            out = false;
            // debug(in, inputs);
            for(string p : in) {
                // debug(p, !inputs[p]);
                if(!inputs[p]) {
                    out = true;
                }
            }
        } else {
            if(s) {
                return;
            }
            state = !state;
            out = state;
            // debug(name, state, out);
        }

        // debug(name, important.find(name) != important.end(), !out);
        if(important.find(name) != important.end() && !out) {
            on_times[name].push_back(t);
        }

        for(string d : dest) {
            // debug(name, out, d);
            q.push({d, {name, out}});
        }
    }
};

ll gcd(ll x, ll y) {
    if(min(x, y) == 0) return max(x, y);
    return __gcd(x, y);
}

ll lcm2(ll x, ll y) {
    if(min(x, y) == 0) return max(x, y);
    return (__int128_t) x * y / gcd(x, y);
}

void solve(){
    int n;
    cin >> n;

    map<string, Node> nodes;

    for(int i = 0; i < n; i++) {
        Node n;
        cin >> n.is_comb >> n.name;
        int m;
        cin >> m;
        for(int j = 0; j < m; j++) {
            string t;
            cin >> t;
            // n.inputs[t] = false;
            n.dest.push_back(t);
        }
        nodes[n.name] = n;
    }

    for(auto p : nodes) {
        for(auto n : p.second.dest) {
            nodes[n].in.push_back(p.first);
        }
    }


    important.insert("gr");
    important.insert("vc");
    important.insert("db");
    important.insert("lz");

    queue<pair<string, pair<string, bool>>> q;
    while(true) {
        t++;
        q.push({"broadcaster", {"button", false}});

        while(!q.empty()) {
            string nxt;
            pair<string, bool> signal;
            tie(nxt, signal) = q.front();
            q.pop();
            nodes[nxt].get_signal(signal, q);
        }
        if(t == 10000) break;
    }

    for(auto p : nodes) {
        Node n = p.second;
        cout << n.name << ' ' << n.state << ' ' << n.inputs << endl;
    }

    debug(on_times, on_times.size());

    // you still don't need CRT...

    ll ans = 0;
    for(auto p : on_times) {
        ans = lcm2(ans, p.second[0]);
    }
    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
