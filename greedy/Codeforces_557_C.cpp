//https://codeforces.com/problemset/problem/557/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 +5 , E = 1<<17;
const int MOD = 1e9 + 7;

int n;
int l[N];
int d[N];
vector<int> v;
int freql[N], freqd[N];

bool cmp(int x, int y){
    if(l[x]==l[y]){
        return d[x]<d[y];
    }else{
        return l[x]>l[y];
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> l[i];
    }
    for(int i=0;i<n;i++){
        cin >> d[i];
        freqd[d[i]]++;
        v.pb(i);
    }
    sort(v.begin(),v.end(),cmp);
    int lf=0;
    int rem=n;
    int sum=0;
    int ans=1e9;
    for(int i=0;i<n;i++){

        if(lf<i)
            lf=i;
        while(lf<n && l[v[lf]]==l[v[i]]){
            freqd[d[v[lf]]]--;
            rem--;
            lf++;
        }
        int res=0;
        int nbmax = lf-i;
        int nbinf = nbmax-1;
        for(int j=1;j<=200;j++){
            int t = max(0,rem-nbinf);
            t = min(t,freqd[j]);
            res+=t*j;
            nbinf+=t;
        }
        ans=min(ans, sum+res);
        sum+=d[v[i]];
    }
    cout << ans << endl;
    return 0;

}
