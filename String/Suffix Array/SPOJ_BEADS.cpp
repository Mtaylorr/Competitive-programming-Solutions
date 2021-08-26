//https://www.spoj.com/problems/BEADS/
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
const int alpha = 128;

char s[N];
int head[N], rnk[N], newSuff[N], suff[N],newrnk[N], bst[N], nxt[N];
int len;
int LCP[N];

void buildSuffixArray(){
    char * str = s;
    memset(head, -1, sizeof(head));
    for(len=0;!len||s[len-1];len++, str++){
        nxt[len] = head[*str];
        head[*str]=len;
        rnk[len]=*str;
    }
    int b=-1;
    int p=0;
    for(int i=0;i<alpha;i++){
        if(head[i]==-1)
            continue;
        bst[++b]=p;
        for(int j=head[i];j!=-1; j=nxt[j]){
            rnk[j]=b;
            suff[p++]=j;
        }
    }
    newrnk[0]=0;
    newSuff[0]=suff[0];
    int cur=1;
    do{
        b=0;
        p=0;
        auto cmp = [cur](int a, int b){return rnk[a]<rnk[b] || rnk[a]==rnk[b] && rnk[a+cur]<rnk[b+cur]; };
        for(int i=0;i<len;i++){
            int j = suff[i]-cur;
            if(j<0)
                continue;
            newSuff[bst[rnk[j]]++]=j;
        }
        for(int i=1;i<len;i++){
            suff[i]=newSuff[i];
            int diff = cmp(suff[i-1],suff[i]);
            newrnk[i]=newrnk[i-1]+diff;
            if(diff){
                bst[newrnk[i]]=i;
            }
        }
        for(int i=0;i<len;i++)
            rnk[suff[i]]=newrnk[i];
        cur*=2;
    }while(newrnk[len-1]!=len-1);
}

void buildLCP(){
    LCP[0]=0;
    int cur=0;
    for(int i=0;s[i];i++){
        int j = suff[rnk[i]-1];
        while(s[j+cur]==s[i+cur]){
            cur++;
        }
        LCP[rnk[i]]=cur;
        if(cur)
            cur--;
    }
}

int t;
int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%s",s);
        int ln = strlen(s);
        memcpy(s+ln, s, ln);
        memcpy(s+2*ln, s, ln-1);
        s[3*ln-1]=0;
        buildSuffixArray();
        buildLCP();
        for(int i=0;i<len;i++){
            if(suff[i]<ln){
                int mn=suff[i];
                int j=i+1;
                for(j=i+1;LCP[j]>=2*ln;j++ ){
                    mn=min(mn, suff[j]);
                }
                cout << mn+1 << endl;
                break;
            }
        }
    }
    return 0;
    return 0;
}
