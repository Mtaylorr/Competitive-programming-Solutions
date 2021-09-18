//https://www.spoj.com/problems/ADACLEAN/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e6 +2;
const int alpha = 128;

int suff[N], newsuff[N], rnk[N], newrnk[N], bst[N], head[alpha], nxt[N];
char s[N];
int LCP[N];
int len;
void buildsuffix(){
    memset(head, -1, sizeof(head));
    char *str  = s;
    for(len=0;!len ||s[len-1]; len++, str++){
        rnk[len]=*str;
        nxt[len]=head[*str];
        head[*str]=len;
    }
    int b=-1;
    int p=0;
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
        auto cmp = [cur](int a, int b){return rnk[a]<rnk[b] || (rnk[a]==rnk[b]&& rnk[a+cur]<rnk[b+cur]);};
        for(int i=0;i<len;i++){
            int j = suff[i]-cur;
            if(j<0)
                continue;
            newsuff[bst[rnk[j]]++]=j;
        }
        for(int i=1;i<len;i++){
            suff[i]=newsuff[i];
            int diff  = cmp(suff[i-1], suff[i]);
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
        int  j = suff[rnk[i]-1];
        while(s[i+cur]==s[j+cur])
            ++cur;
        LCP[rnk[i]]=cur;
        if(cur)
            --cur;
    }
}
int t,n,k;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        scanf("%s",s);
        buildsuffix();
        buildLCP();
        int ans=0;
        for(int i=1;i<len;i++){
            int sz = len-1-suff[i];
            if(k>LCP[i] && k<=sz){
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
