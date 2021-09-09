//https://codeforces.com/problemset/problem/113/B
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 2;
const int alpha = 256;

typedef long long ll;
int suff[N], newSuff[N], rnk[N], newrnk[N], nxt[N], head[alpha], bst[N];
char s[N];
int len;
int LCP[N];
string st, en;

void builSuffix(){
    len=0;
    char *str = s;
    memset(head, -1, sizeof(head));
    for(len=0;!len || s[len-1];str++, len++){
        rnk[len]=*str;
        nxt[len]=head[*str];
        head[*str]=len;
    }
    int b=-1, p=0;
    for(int i=0;i<alpha;i++){
        if(head[i]==-1)
            continue;
        bst[++b]=p;
        for(int j=head[i];j!=-1; j=nxt[j]){
            rnk[j]=b;
            suff[p++]=j;
        }
    }
    int cur=1;
    newrnk[0]=0;
    newSuff[0]=suff[0];
    do{
        auto cmp = [cur](int a, int b){return (rnk[a]<rnk[b])||(rnk[a]==rnk[b]&& rnk[a+cur]<rnk[b+cur]);};
        for(int i=0;i<len;i++){
            int j = suff[i]-cur;
            if(j<0)
                continue;
            newSuff[bst[rnk[j]]++]=j;
        }
        for(int i=1;i<len;i++){
            suff[i]=newSuff[i];
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
        int j = suff[rnk[i]-1];
        while(s[i+cur]==s[j+cur])
            cur++;
        LCP[rnk[i]]=cur;
        if(cur)
            --cur;
    }
}
int dp[N];

int main(){
    scanf("%s",s);
    builSuffix();
    buildLCP();
    cin >> st;
    cin >> en;
    int cur=0;
    for(int i=1;i<len;i++){
        cur=0;
        while(cur<en.size() && s[suff[i]+cur]==en[cur])
            cur++;
        if(cur>=en.size()){
            dp[suff[i]+en.size()-1]=1;
        }
    }
    for(int i=len-1;i>=0;i--){
        dp[i]+=dp[i+1];
    }
    cur=0;
    int ans=0;
    int bef=0;
    for(int i=1;i<len;i++){
        cur=0;
        while(cur<st.size() && s[suff[i]+cur]==st[cur])
            cur++;
        if(cur>=st.size()){
            int ps = max((int)(suff[i]+max(en.size(), st.size())-1),suff[i]+LCP[i]);
            ans+=dp[ps];
        }
    }
    printf("%d",ans);
    return 0;
}
