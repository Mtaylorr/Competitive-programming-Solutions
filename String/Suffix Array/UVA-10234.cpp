//https://vjudge.net/problem/UVA-10234
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
const int alpha = 128;

char s[N];
int n;
int suff[N], rnk[N], newrnk[N],len, newSuff[N], bst[N];
int LCP[N];


void buildSuffix_N_logN(){
    int *head=newSuff, *nxt = newrnk;
    memset(head, -1, alpha*sizeof(head[0]));
    for(len=0;!len||s[len-1];++len){
        suff[len]=len;
        nxt[len] = head[s[len]];
        head[s[len]]=len;
    }
    int p=0, b=-1;

    for(int i=0;i<alpha;i++){
        if(head[i]==-1)
            continue;
        bst[++b]=p;

        for(int j=head[i];~j;j=nxt[j])
        {
            rnk[j]=b;
            suff[p++] = j;
        }
    }
    int cur=1;
    newrnk[0]=0;
    newSuff[0]=suff[0];
    do{
        auto cmp = [cur](int a , int b){return rnk[a]<rnk[b] || rnk[a]==rnk[b]&& rnk[a+cur]<rnk[b+cur];};

        for(int i=0;i<len;++i){
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

char tmp[15];

int readInt(){
    scanf("%[^\n]", tmp);
    getchar();
    int x;
    sscanf(tmp, "%d", &x);
    return x;
}



struct event{
    int ln , ind;
    enum {LCP,SUFFIX,QUERY}type;
    bool operator<(const event & e)const{
        return make_pair(-ln, type) < make_pair(-e.ln , e.type);
    }
};
event evs[3005];

struct ANS{
    int cnt, st, ln;
};

ANS res[1005];
int x;
int main()
{
    while(~scanf("%[^\n] ",s)){
        for(char *str=s;*str;str++){
            *str = tolower(*str);
        }
        set<pair<int,int> > rss;
        rss.emplace(INT_MIN, INT_MIN);
        rss.emplace(INT_MAX, INT_MAX);
        int n = readInt();
        buildSuffix_N_logN();
        buildLCP();
        for(int i=0;i<len;i++){
            evs[2*i]={LCP[i], i, event::LCP};
            evs[2*i+1]={len-suff[i]-1, i, event::SUFFIX};
        }
        for(int i=0;i<n;i++){
            x=readInt();
            evs[2*len+i] = {x, i, event::QUERY};
        }
        sort(evs, evs+2*len+n);
        pair<int,int> mxp;
        int mxsz =0;
        int mn=len;
        for(int i=0;i<2*len+n;i++){
            if(evs[i].type==event::SUFFIX){
                if(mxsz==0){
                    pair<int,int> mpr = {evs[i].ind, evs[i].ind-1};
                    if(evs[i].ind<mn){
                        mn=evs[i].ind;
                        mxp=mpr;
                    }
                }
            }
            else if(evs[i].type==event::LCP){
                pair<int,int> pr = {evs[i].ind ,evs[i].ind};
                auto it = rss.insert(pr).first;
                auto af =  it;
                af++;
                if(pr.second+1==af->first){
                    pr.second=af->second;
                    rss.erase(af);
                    rss.erase(it);
                    it = rss.insert(pr).first;
                }
                auto be = it;
                be--;
                if(be->second+1==pr.first){
                    pr.first = be->first;
                    rss.erase(be);
                    rss.erase(it);
                    rss.insert(pr);
                }
                if(pr.second-pr.first+1>mxsz || pr.second-pr.first+1==mxsz && pr<mxp){
                    mxsz=pr.second-pr.first+1;
                    mxp = pr;
                }

            }else{
                res[evs[i].ind] = {mxsz, suff[mxp.first], evs[i].ln};
            }
        }
        for(int i=0;i<n;i++){
            char c = s[res[i].st+res[i].ln];
            s[res[i].st+res[i].ln]=0;
            printf("%d %s\n", res[i].cnt+1, s+res[i].st);
            s[res[i].st+res[i].ln]=c;
        }
    }

    return 0;
}
