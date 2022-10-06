//https://codeforces.com/problemset/problem/1214/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int n;
int d[N];
vector<int> v;
int atdist[N];
vector<pair<int,int> > edges;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> d[i];
        v.pb(i);
    }
    sort(v.begin(),v.end(), [](int a, int b){return d[a]>d[b];});
    int branch = v[d[v[0]]-1];
    int branchpos = d[v[0]]-1;
    atdist[0]=2*branch;
    for(int i=0;i<n;i++){
        if(i>=0 && i+1<n){
            edges.pb({2*v[i], 2*v[i+1]});
        }
        if(abs(branchpos-i)<=d[v[i]]-1){
            int rem = d[v[i]]-1-abs(branchpos-i);
            edges.pb({2*v[i]-1, atdist[rem]});
            atdist[rem+1]=2*v[i]-1;
        }else{
            if(i+d[v[i]]-1<n){
                edges.pb({2*v[i]-1, 2*v[i+d[v[i]]-1]});
            }else{
                edges.pb({2*v[i]-1, 2*v[i-d[v[i]]+1]});
            }
        }
    }
    for(auto u:edges){
        cout << u.fi << " " << u.se << endl;
    }
    return 0;

}
