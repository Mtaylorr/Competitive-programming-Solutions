//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1986
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;


int t,n,m;
string s;
vector<int> v[50];
int cnt[6];
int rem[50], remsz;
int getv(){
    if(s=="XS")
        return 0;
    if(s=="S")
        return 1;
    if(s=="M")
        return 2;
    return 2 + s.size();
}

bool swim(int dpth=0){
    if(dpth==m)
        return true;
    int mnv = 1e9;
    int mni =0;
    for(int i=0;i<remsz;i++){
        int y = cnt[v[rem[i]][0]] + cnt[v[rem[i]][1]];
        if(y==0){
            return 0;
        }
        if(y<mnv){
            mnv=y;
            mni=i;
        }
    }
    swap(rem[mni], rem[--remsz]);
    int x = rem[remsz];
    if(cnt[v[x][0]]){
        cnt[v[x][0]]--;
        if( swim(dpth+1))
            return true;
        cnt[v[x][0]]++;
    }
    if(cnt[v[x][1]]){
        cnt[v[x][1]]--;
        if(swim(dpth+1))
            return true;
        cnt[v[x][1]]++;
    }
    swap(rem[mni], rem[remsz++]);
    return 0;
}


int main(){
    freopen("input.txt", "r",stdin);
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<6;i++){
            cnt[i]=n/6;
        }
        for(int i=0;i<m;i++){
            v[i].clear();
            cin >> s;
            v[i].pb(getv());
            cin >> s;
            v[i].pb(getv());
        }
        remsz=m;
        for(int i=0;i<remsz;i++){
            rem[i]=i;
        }
        bool rs = swim();
        if(rs)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
