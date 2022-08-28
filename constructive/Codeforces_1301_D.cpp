//https://codeforces.com/problemset/problem/1301/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e6 + 5, E = 1 << 17;
const int MOD =  998244353;

int n,m,k;

vector<pair<int,string> > ans;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> k;
    if(k>4*n*m-2*n-2*m){
        cout << "NO\n";
        return 0;
    }
    int cur = m-1;
    int cursz = 1;
    if(k>=cur){
        k-=cur;
        if(cur)
            ans.pb({cur, "R"});
    }else{
        if(k)
            ans.pb({k, "R"});
        k=0;
    }
    if(k>=cur){
        k-=cur;
        if(cur)
            ans.pb({cur, "L"});
    }else{
        if(k)
            ans.pb({k,"L"});
        k=0;
    }
    for(int i=1;i<n;i++){
        if(k){
            k--;
            ans.pb({1,"D"});
        }
        int cur = m-1;
        int cursz= 3;
        if(k>=cur*cursz){
            if(cur)
                ans.pb({cur, "RUD"});
            k-=cur*cursz;
        }else{
            if(k/3){
                ans.pb({k/3, "RUD"});
            }
            string curs="RUD";
            if(k%3){
                ans.pb({1, curs.substr(0, k%3)});
            }
            k=0;
        }
        cur = m-1;
        cursz = 1;
        if(k>=cur*cursz){
            if(cur)
                ans.pb({cur, "L"});
            k-=cur*cursz;
        }else{
            if(k){
                ans.pb({k, "L"});
            }
            k=0;
        }
    }
    cur = n-1;
    cursz = 1;
    if(k>=cur){
        k-=cur;
        if(cur)
            ans.pb({cur, "U"});
    }else{
        if(k)
            ans.pb({k, "U"});
        k=0;
    }
    cout << "YES\n";
    cout << ans.size() << endl;
    for(auto u:ans){
        cout << u.fi << " " << u.se << endl;
    }

    return 0;
}
