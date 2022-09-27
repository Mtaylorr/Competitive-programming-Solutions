//https://codeforces.com/problemset/problem/1147/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 1e9 + 7   ;
const double eps = 1e-7;


set<int> pos[N];
int n,m;
int a,b;

bool solve(int u){
    if(u==n)
        return 0;
    for(int i=0;i<=n;i++){
        for(auto v:pos[i]){
            if(pos[i].count((v+u)%n)==0){
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> a >> b;
        a--,b--;
        if(a>b){
            swap(a,b);
        }
        pos[b-a].insert(a);
        pos[n-(b-a)].insert(b);
    }
    for(int j=1;j*j<=n;j++){
        if(n%j==0){
            if(solve(j)){
                cout << "Yes\n";
                return 0;
            }
            if(solve(n/j)){
                cout << "Yes\n";
                return 0;
            }
        }
    }
    cout << "No\n";


    return 0;
}
