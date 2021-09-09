//https://codeforces.com/problemset/problem/128/B
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 2;
const int alpha = 256;

typedef long long ll;

char s[N];
int suff[N], newsuff[N], rnk[N], newrnk[N], bst[N], nxt[N], head[alpha];
int len;
int k;
int LCP[N];
void buildSuffix(){
    memset(head, -1, sizeof(head));
    char *str=s;
    for(len=0;!len || s[len-1];len++, str++){
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
        auto cmp = [cur](int a, int b){return (rnk[a]<rnk[b])|| (rnk[a]==rnk[b] && rnk[a+cur]<rnk[b+cur]);};
        for(int i=0;i<len;i++){
            int j = suff[i]-cur;
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
    int cur=0;
    LCP[0]=0;
    for(int i=0;s[i];i++){
        int j=suff[rnk[i]-1];
        while(s[i+cur]==s[j+cur])
            cur++;
        LCP[rnk[i]]=cur;
        if(cur)
            --cur;
    }
}

ll cnt[N];
string ans="";
multiset<int> ss;
int main(){
    freopen("input.txt", "r", stdin);
    scanf("%s",s);
    scanf("%d",&k);
    buildSuffix();
    buildLCP();
    ll total = ((len)*1LL * (len-1))/2;
    if(total<k){
        puts("No such line.");
        return 0;
    }

    int res=0;
    for(int i=1;i<len;i++){
        int j=i+1;
        while(j<len && LCP[j]>=LCP[i]+1){
            ss.insert(LCP[j]);
            j++;
        }
        int sz = len-1-suff[i];
        for(int o=LCP[i]+1;o<=sz;o++){
            if(res+ss.size()+1>=k){
                for(int u=suff[i];u<suff[i]+o;u++){
                    cout << s[u];
                }
                return 0;
            }
            res+=(ss.size()+1);
            while(!ss.empty()&& (*ss.begin())<o+1){
                ss.erase(ss.find(LCP[--j]));
            }
        }

    }
    return 0;
}
