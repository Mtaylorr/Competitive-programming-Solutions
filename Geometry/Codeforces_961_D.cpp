//https://codeforces.com/problemset/problem/961/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 1 << 17;
const int MOD =  998244353;

int n;
ll x[N], y[N];

bool valid(vector<int> &other){
    ll dx1 = x[other[1]]-x[other[0]];
    ll dy1 = y[other[1]]-y[other[0]];
    for(auto i:other){
        ll dx2 = x[i]-x[other[0]];
        ll dy2  = y[i]-y[other[0]];
        if(dx1*dy2 != dy1*dx2){
            return 0;
        }
    }
    return 1;
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
    }
    if(n<=4){
        cout << "YES\n";
        return 0;
    }

    for(int j=1;j<=2;j++){
        ll dx1 = x[j]-x[0];
        ll dy1 = y[j]-y[0];
        vector<int> otherpoints;
        for(int i=0;i<n;i++){
            ll dx2 = x[i]-x[0];
            ll dy2  = y[i]-y[0];
            if(dx1*dy2 != dy1*dx2){
                otherpoints.pb(i);
            }
        }
        if(otherpoints.size()<=2){
            cout << "YES\n";
            return 0;
        }
        if(valid(otherpoints)){
            cout << "YES\n";
            return 0;
        }
    }
    for(int j=2;j<=2;j++){
        ll dx1 = x[j]-x[1];
        ll dy1 = y[j]-y[1];
        vector<int> otherpoints;
        for(int i=0;i<n;i++){
            ll dx2 = x[i]-x[1];
            ll dy2  = y[i]-y[1];
            if(dx1*dy2 != dy1*dx2){
                otherpoints.pb(i);
            }
        }
        if(otherpoints.size()<=2){
            cout << "YES\n";
            return 0;
        }
        if(valid(otherpoints)){
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}
