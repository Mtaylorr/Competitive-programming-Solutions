//https://codeforces.com/problemset/problem/1697/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 1 << 17;
const int MOD =  998244353;

char ans[1005];
int n,m;
int pos[26];
vector<int> tmp;

bool ok(int l, int r){
    int x;
    cout << "? " << 2 << " " <<tmp[l-1]+1 << " " << r+1 << endl;
    cin >> x;
    int y = tmp.size()-(l-1);
    return x==y;
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(pos, -1, sizeof(pos));
    cin >> n;
    for(int i=0;i<n;i++){
        tmp.clear();
        for(int j=0;j<26;j++){
            if(pos[j]!=-1){
                tmp.pb(pos[j]);
            }
        }
        sort(tmp.begin(), tmp.end());
        bool cond=false;
        int l=0;
        int r=tmp.size();
        while(l<r){
            int md = (l+r+1)/2;
            if(ok(md, i)){
                l=md;
            }else{
                r=md-1;
            }
        }
        if(l>0){
            ans[i]=ans[tmp[l-1]];
        }else{
            cout << "? " << 1 <<" "<< i+1 << endl;
            cin >> ans[i];
        }
        pos[ans[i]-'a']=i;
    }
    cout <<"! " <<ans << endl;
    return 0;
}
