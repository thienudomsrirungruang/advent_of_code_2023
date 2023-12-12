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

void solve(){
    int tc;
    cin >> tc;
    ll ans = 0;
    while(tc--) {
        string s;
        cin >> s;
        s = s + '?' + s + '?' + s + '?' + s + '?' + s;
        s += '.';
        int n = s.size();
        int m;
        cin >> m;
        vi v(5 * m);
        for(int i = 0; i < m; i++) {
            cin >> v[i];
            for(int j = 1; j < 5; j++) {
                v[i+j*m] = v[i];
            }
        }
        m *= 5;
            
        ll ways = 0;

        vvll dp(n+1, vll(m+1)); // dp[i][j] - ways to get first j of v in s[:i]

        debug(n, m);

        dp[0][0] = 1;

        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= m; j++) {
                if(s[i-1] != '#') {
                    dp[i][j] = dp[i-1][j];
                    if(j > 0) {
                        debug(i, j);
                        bool good = true;
                        for(int k = 0; k < v[j-1]; k++) {
                            if(i-k-2 < 0) {
                                good = false;
                                break;
                            }
                            if(s[i-k-2] == '.') {
                                good = false;
                                break;
                            }
                        }
                        if(good) {
                            debug(i, j, i-v[j-1]-1, j-1);
                            dp[i][j] += dp[i-v[j-1]-1][j-1];
                        }
                    }
                }
                
            }
        }

        debug(dp);

        ans += dp[n][m];
    }
    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
