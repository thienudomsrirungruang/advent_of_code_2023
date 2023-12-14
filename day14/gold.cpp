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

const int LIM = 1000000000;

vector<vector<char>> rotate(vector<vector<char>> v) {
    int n = v.size();
    int m = v[0].size();
    vector<vector<char>> out(m, vector<char>(n));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            out[i][j] = v[j][m-i-1];
        }
    }
    return out;
}

void push(vector<vector<char>> &v) {
    int n = v.size();
    int m = v[0].size();
    for(int i = -1; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == -1 || v[i][j] == '#') {
                int k = i + 1;
                int cnt = 0;
                while(k < n && v[k][j] != '#') {
                    if(v[k][j] == 'O') {
                        cnt++;
                    }
                    v[k][j] = '.';
                    k++;
                }

                for(int k = i+1; k <= i+cnt; k++) {
                    v[k][j] = 'O';
                }
            }
        }
    }
}

int comp(vector<vector<char>> &v) {
    int n = v.size();
    int m = v[0].size();
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(v[i][j] == 'O') {
                ans += n-i;
            }
        }
    }
    // cout << ans << endl;
    return ans;
}

void solve(){
    vector<vector<char>> input;
    while(true) {
        string s;
        cin >> s;
        if(!cin) break;
        vector<char> row;
        for(int j = 0; j < s.size(); j++) {
            row.push_back(s[j]);
        }
        input.push_back(row);
    }
    int n = input.size();
    int m = input[0].size();

    vector<vector<vector<char>>> cache;
    vi vals;
    int cyc_start;
    int cyc_len;
    for(int cyc = 0;; cyc++) {
        // debug(cache.size(), vals, cyc);
        // ans.push_back(cyc);
        for(int i = 0; i < 4; i++) {
            push(input);
            input = rotate(input);
            input = rotate(input);
            input = rotate(input);
        }
        // ans.push_back(comp(input));
        if(find(cache.begin(), cache.end(), input) != cache.end()) {
            cyc_start = find(cache.begin(), cache.end(), input) - cache.begin();
            cyc_len = cyc - cyc_start;
            break;
        }
        cache.push_back(input);
        vals.push_back(comp(input));
    }
    debug(vals, cyc_start, cyc_len);
    if(LIM - 1 < cyc_start) {
        cout << vals[LIM - 1] << endl;
    } else {
        cout << vals[cyc_start + (LIM - 1 - cyc_start) % cyc_len] << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
