//https://codeforces.com/problemset/problem/1017/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5, E = 1 << 17;
const int MOD =  998244353 ;


int n,m,q,k;

int freq[N];
int dp[5000][105];
int w[N];
string s;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> q;
    for(int i=0;i<n;i++){
        cin >> w[i];
    }
    for(int i=0;i<m;i++){
        cin >> s;
        int x = 0;
        for(int j=0;j<n;j++){
            x+=(s[j]-'0')*(1<<j);
        }
        freq[x]++;
    }
    for(int pat=0;pat<(1<<n);pat++){
        for(int src=0;src<(1<<n);src++){
            if(freq[src]==0)
                continue;
            int sm=0;
            int cur=1;
            for(int i=0;i<n;i++){
                int nx = pat&cur;
                int ny = src&cur;
                if(nx==ny){
                    sm+=w[i];
                }
                cur*=2;
            }
            if(sm<=100){
                dp[pat][sm]+=freq[src];
            }
        }
    }
    for(int pat=0;pat<(1<<n);pat++){
        for(int j=1;j<=100;j++){
            dp[pat][j]+=dp[pat][j-1];
        }
    }
    while(q--){
        cin >> s >> k;
        int x = 0;
        for(int j=0;j<n;j++){
            x+=(s[j]-'0')*(1<<j);
        }
        cout << dp[x][k] << "\n";
    }
    return 0;
}
