//https://codeforces.com/contest/1548/problem/B
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll, ll> pl;
typedef long double ld;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(1e6) + 3;
const int MOD = int(1e9) + 7;


ll gcd(ll x, ll y){
    if(y==0)
        return x;
    return gcd(y, x%y);
}

int T;
ll a[N];
int n;
ll diff[N];
ll spt[20][N];

int lg[N];



int l;
int get(int pos){
    ll cur=0;
    int sz = 0;
    for(int j=l;j>=0;j--){
        ll  x = gcd(cur, spt[j][pos]);
        if(pos>=n)
            break;
        if(x==1){
            continue;
        }else{
            cur =x;
            sz+=lg[j];
            pos+=(lg[j]);
        }
    }
    return sz;
}

int main() {
    FAST;
    cin >> T;
    lg[0]=1;
    for(int i=1;i<=20;i++){
        lg[i]=2*lg[i-1];
    }
    while(T--){
        cin >> n;
        for(int i=0;i<n;i++){
            cin >> a[i];
        }
        for(int i=1;i<n;i++){
            diff[i-1]=abs(a[i]-a[i-1]);
        }
        n--;
        l=0;
        for(int i=0;i<n;i++){
            spt[0][i]=diff[i];
        }
        for(int j=1;(1<<j)<=n;j++){
            l=j;
        }
        for(int i=1;i<=l;i++){
            for(int j=0;j<n;j++)
                spt[i][j]=1;
        }
        for(int j=1;lg[j]<=n;j++){
            for(int i=0;i+lg[j]<=n;i++){
                spt[j][i] = gcd(spt[j-1][i], spt[j-1][i+(1<<(j-1))]);
            }
        }
        int ans=0;
        for(int i=0;i<n;i++){
            int x = get(i);
            ans=max(ans, x);
        }
        cout << ans+1 << endl;
    }
    return 0;
}
