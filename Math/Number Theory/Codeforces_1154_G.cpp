//https://codeforces.com/problemset/problem/1154/G
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e6 + 100, M = 1000 + 5, E = 1e7 + 5;
const int MOD = 1e9 + 7;

int n, m;
int freq[E];
int a[N];


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        freq[a[i]]++;
    }
    ll ans =1e18;
    ll x=-1;
    ll y=-1;
    for(int i=1;i<=1e7;i++){
        vector<int> v;
        for(int j=i;j<=1e7;j+=i){
            int sz = v.size();
            for(int k=0;k<min((int)(2-sz), freq[j]);k++){
                v.pb(j);
            }
            if(v.size()==2)
                break;
        }
        if(v.size()==2){
            if(ans>(v[0]*1ll*v[1]/i)){
                ans=v[0]*1ll*v[1]/i;
                x=v[0];
                y=v[1];
            }
        }
    }
    for(int i=0;i<n;i++){
        if(a[i]==x){
            cout << i+1 << " ";
            x=-1;
            a[i]=-2;
        }
        if(a[i]==y){
            cout << i+1 << " ";
            y=-1;
            a[i]=-2;
        }
    }
    return 0;

}
