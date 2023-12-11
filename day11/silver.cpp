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

int get_ans(vi v){
    int n = v.size();

    int num = accumulate(v.begin(), v.end(), 0);
    int cur = -num+1;

    int ans = 0;
    for(int i = 0; i < n; i++) {
        while(v[i]--) {
            ans += cur * i;
            cur += 2;
        }
    }
    return ans;
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

    vi row(n);
    vi col(m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(input[i][j] == '#') {
                row[i]++;
                col[j]++;
            }
        }
    }

    vi row2;
    for(int i = 0; i < n; i++) {
        row2.push_back(row[i]);
        if(row[i] == 0) row2.push_back(0);
    }
    vi col2;
    for(int i = 0; i < m; i++) {
        col2.push_back(col[i]);
        if(col[i] == 0) col2.push_back(0);
    }

    debug(row, col);

    cout << get_ans(row2) + get_ans(col2) << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
