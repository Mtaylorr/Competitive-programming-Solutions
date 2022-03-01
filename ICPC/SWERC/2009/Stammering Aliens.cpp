#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5, K=128;
const int MOD = 1e9 + 7 ;

int suff[N], nxt[N], head[K], bst[N];
char s[N];
int rnk[N];
int len=0;
int newrnk[N], newSuff[N];

void suffixArray(){
    memset(head, -1, K*sizeof(head[0]));
    for(len=0;(!len)|| s[len-1];len++){
        suff[len]=len;
        nxt[len]=head[s[len]];
        head[s[len]]=len;
    }
    int p=0, b=-1;
    for(int i=0;i<K;i++){
        if(head[i]==-1)
            continue;
        bst[++b]=p;
        for(int j=head[i];~j;j=nxt[j]){
            rnk[j]=b;
            suff[p++]=j;
        }
    }
    int cur=1;
    newrnk[0]=0;
    newSuff[0]=suff[0];
    do{
        auto cmp = [cur](int a, int b){return rnk[a]<rnk[b] || rnk[a]==rnk[b]&& rnk[a+cur]<rnk[b+cur] ;};
        for(int i=0;i<len;i++){
            int j = suff[i]-cur;
            if(j<0)
                continue;
            newSuff[bst[rnk[j]]++]=j;
        }
        for(int i=1;i<len;++i){
            suff[i] = newSuff[i];
            bool cmpres =  (cmp(suff[i-1], suff[i]));
            newrnk[i] = newrnk[i-1] + cmpres ;
            if(cmpres)
                bst[newrnk[i]]=i;
        }
        for(int i=0;i<len;++i){
            rnk[suff[i]] = newrnk[i];
        }
        cur<<=1;
    }while(newrnk[len-1]!=len-1);
}
int LCP[N];
void buildLCP(){
    int cnt=0;
    for(int i=0;s[i];++i){
        int j = suff[rnk[i]-1];
        while(s[i+cnt]==s[j+cnt])
            cnt++;
        LCP[rnk[i]] = cnt;
        if(cnt)
            cnt--;
    }
}

int ansl, ansp;
void solve(int m){
    if(m==1){
        ansp=0;
        ansl=len-1;
        return ;
    }
    deque<int> l;
    deque<int> p;
    ansl=0;
    p.push_back(suff[0]);
    for(int i=1;i<=1+m-2;i++){

        while(!l.empty() && LCP[i]<LCP[l.back()]){
            l.pop_back();
        }

        l.push_back(i);
        while(!p.empty() && suff[i]>p.back()){
            p.pop_back();
        }

        p.push_back(suff[i]);
    }
    for(int i=1;i+m-1<len;i++){
        while(!l.empty() && LCP[i+m-1]<LCP[l.back()]){
            l.pop_back();
        }
        l.push_back(i+m-1);
        while(!p.empty() && suff[i+m-1]>p.back()){
            p.pop_back();
        }
        p.push_back(suff[i+m-1]);
        if(l.front()==i)
            l.pop_front();
        if(p.front()==suff[i-1])
            p.pop_front();
        if(LCP[l.front()]>ansl){
            ansl=LCP[l.front()];
            ansp = p.front();
        }
        if(ansl==LCP[l.front()]){
            ansp = max(ansp, p.front());
        }
    }
}

int m;

int main(){
   // freopen("input.txt", "r",stdin);
    while(1){
        scanf("%d",&m);
        if(m==0)
            break;
        scanf("%s",s);
        suffixArray();
        buildLCP();
        if(m>=len){
            continue;
        }
        solve(m);
        if(ansl)
            cout << ansl << " " << ansp << endl;
        else
            cout << "none" << endl;

    }
    return 0;
}
