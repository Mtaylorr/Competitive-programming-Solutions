//https://codeforces.com/problemset/problem/19/C
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
const int alpha = 1e5 + 5;

typedef long long ll;

int suff[N], newsuff[N], rnk[N], newrnk[N], bst[N], head[alpha], nxt[N], len;
int s[N];
int LCP[N];
int spt[26][N];


set<int> ss;
map<int,int> code;
map<int,int> decode;
vector<int> v[N];
int n;

void buildSuffix(){
    int *str =s;
    memset(head, -1, sizeof(head));
    for(len=0;len<n+1;str++, len++){
        rnk[len]=*str;
        nxt[len]=head[*str];
        head[*str]=len;
    }

    int b=-1, p=0;
    for(int i=0;i<alpha;i++){
        if(head[i]==-1)
            continue;
        bst[++b]=p;
        for(int j=head[i];j!=-1;j=nxt[j]){
            rnk[j]=b;
            suff[p++]=j;
        }
    }
    int cur=1;
    newsuff[0]=suff[0];
    newrnk[0]=0;
    do{
        auto cmp = [cur](int a, int b){return (rnk[a]<rnk[b])|| (rnk[a]==rnk[b]&& rnk[a+cur]<rnk[b+cur]);};
        for(int i=0;i<len;i++){
            int j=suff[i]-cur;
            if(j<0)
                continue;
            newsuff[bst[rnk[j]]++]=j;
        }
        for(int i=1;i<len;i++){
            suff[i]=newsuff[i];
            int diff = cmp(suff[i-1], suff[i]);
            newrnk[i]=newrnk[i-1]+diff;
            if(diff)
                bst[newrnk[i]]=i;
        }
        for(int i=0;i<len;i++){
            rnk[suff[i]]=newrnk[i];
        }
        cur*=2;
    }while(newrnk[len-1]!=len-1);
}

void buildLCP(){
    LCP[0]=0;
    int cur=0;
    for(int i=0;i<n;i++){
        int j = suff[rnk[i]-1];
        while(s[i+cur]==s[j+cur])
            cur++;
        LCP[rnk[i]]=cur;
        if(cur)
            --cur;
    }
}

int lg2[N];

void buildspt(){
    lg2[0]=-1;
    for(int i=0;i<len;i++){
        spt[0][i]=LCP[i];
    }
    lg2[1]=0;
    for(int i=2;i<=len;i++){
        lg2[i]=1+lg2[i/2];
    }
    for(int cur=1;(1<<cur)<=len;cur++){
        for(int j=0;j+(1<<cur)<=len;j++){
            spt[cur][j]=min(spt[cur-1][j], spt[cur-1][j+(1<<(cur-1))]);
        }
    }
}
int getmin(int x, int y){
    int lg = lg2[abs(y-x)+1];
    if(x>y)
        swap(x,y);
    return min(spt[lg][x], spt[lg][y-(1<<lg)+1]);
}

int getans(int x, int y){
    x = rnk[x];
    y = rnk[y];
    if(x>y)
        swap(x,y);
    return getmin(x+1,y);

}



int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&s[i]);
        ss.insert(s[i]);
    }
    int cn=1;
    for(auto u:ss){
        code[u]=cn;
        decode[cn]=u;
        cn++;
    }
    for(int i=0;i<n;i++){
        s[i]=code[s[i]];
        v[s[i]].push_back(i);
    }
    buildSuffix();
    buildLCP();
    buildspt();
    int l=0;
    for(int i=0;i<n;i++){
        for(auto u:v[s[i]]){
            if(u>=i || u<l)
                continue;
            int y = getans(i,u);
            if(y>=i-u){
                l=i;
                break;
            }
        }
    }
    cout << n-l << endl;
    for(int i=l;i<n;i++){
        cout << decode[s[i]] << " ";
    }
    return 0;
}
