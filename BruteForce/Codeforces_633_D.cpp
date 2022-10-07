//https://codeforces.com/contest/633/problem/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = (1e5) + 100, M = 1000 + 5, E = 2e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int n;
int a[N];
unordered_map<int,int> freq;
int freq0;

vector<int> tmp;
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
    freq0 = freq[0];
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j)
                continue;
            tmp.clear();
            freq[a[i]]--;
            freq[a[j]]--;
            tmp.pb(a[i]);
            tmp.pb(a[j]);
            int x = a[i]+0ll+a[j];
            int y = a[j];
            int nb=2;
            while((x!=0 || y!=0) && abs(x)<=1e9 && freq[x]!=0){
                nb++;
                tmp.pb(x);
                freq[x]--;
                int z = x+y;
                y=x;
                x=z;
            }
            if(x==0 && y==0){
                nb+=(freq[0]);
            }
            ans=max(ans, nb);
            for(auto u:tmp){
                freq[u]++;
            }
            freq[0]=freq0;
        }
    }
    cout << ans;
    return 0;

}
