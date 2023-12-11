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

int rank_hand(vi c) {
    vi cnt(13);
    for(int i : c) {
        cnt[i]++;
    }
    vi freq;
    for(int i = 0; i < 13; i++) {
        freq.push_back(cnt[i]);
    }
    sort(freq.begin(), freq.end());
    if(freq[12] == 5) {
        return 10;
    } else if(freq[12] == 4) {
        return 9;
    } else if(freq[12] == 3 && freq[11] == 2) {
        return 8;
    } else if(freq[12] == 3) {
        return 7;
    } else if(freq[12] == 2 && freq[11] == 2) {
        return 6;
    } else if(freq[12] == 2) {
        return 5;
    } else {
        return 4;
    }
}

void solve(){
    vector<pair<string, int>> input;
    while(true) {
        string s;
        cin >> s;
        if(!cin) break;
        int x;
        cin >> x;
        input.push_back({s, x});
    }
    int n = input.size();

    debug(n);

    string cards = "23456789TJQKA";

    vector<pair<vi, int>> hands;

    for(auto p : input) {
        string s;
        int v;
        tie(s, v) = p;
        vi h;
        for(char c : s) {
            for(int i = 0; i < 13; i++) {
                if(c == cards[i]) {
                    h.push_back(i);
                    break;
                }
            }
        }
        hands.push_back({h, v});
    }

    sort(hands.begin(), hands.end(), [&](pair<vi, int> p1, pair<vi, int> p2) {
        vi h1 = p1.first;
        vi h2 = p2.first;
        int r1 = rank_hand(h1);
        int r2 = rank_hand(h2);
        if(r1 < r2) {
            return true;
        } else if(r1 > r2) {
            return false;
        } else {
            for(int i = 0; i < 5; i++) {
                if(h1[i] < h2[i]) {
                    return true;
                } else if(h1[i] > h2[i]){
                    return false;
                }
            }
        }
        return false;
    });

    // debug(hands[0].first, hands[999].first);

    ll ans = 0;
    for(int i = 0; i < n; i++) {
        // debug(hands[i].first, hands[i].second);
        ans += hands[i].second * (i+1);
    }
    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
