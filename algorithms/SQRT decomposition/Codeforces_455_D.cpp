//https://codeforces.com/contest/455/problem/D
#include <bits/stdc++.h>

using namespace std;

const int N = int(1e5) + 5;

#define pb push_back

int parts=0;
int r,l,k;
unordered_map<int,int> cnt[int(1e3)];
int li[int(1e3)],ri[int(1e3)];
vector<int> v[int(1e3)];
int block;
int a[N];
int n;
int q;

void builarr(){
    int i=0;
    for(int j=0;j<parts;j++){
        for(auto u:v[j])
            a[i++]=u;
        v[j].clear();
        cnt[j].clear();
    }
}

void buildsqt(){
    for(int i=0;i<n;i++){
        v[i/block].pb(a[i]);
        cnt[i/block][a[i]]++;
    }
    int sz=0;
    for(int i=0;i<parts;i++){
        li[i]=sz;
        ri[i]=sz+v[i].size()-1;
        sz+=v[i].size();
    }

}
vector<int> tmp;

void ins(int pt,int pos, int val){
    tmp.clear();
    for(int i=0;i<pos;i++)
        tmp.pb(v[pt][i]);
    tmp.pb(val);
    for(int i=pos;i<v[pt].size();i++){
        tmp.pb(v[pt][i]);
    }
    v[pt].clear();
    for(auto u:tmp){
        v[pt].pb(u);
    }
    tmp.clear();
}

void rem(int pt, int pos, int val){
    tmp.clear();
    for(int i=0;i<pos;i++)
        tmp.pb(v[pt][i]);
    for(int i=pos+1;i<v[pt].size();i++){
        tmp.pb(v[pt][i]);
    }
    v[pt].clear();
    for(auto u:tmp){
        v[pt].pb(u);
    }
    tmp.clear();
}

void ins(int pos, int val){
    bool done=false;
    for(int i=0;i<parts;i++){
        if(v[i].size()==0)
            continue;
        if(li[i]<=pos && ri[i]+1>=pos && !done){
            ins(i,pos-li[i], val);
            cnt[i][val]++;
            ri[i]++;
            done=true;
        }else if(done){
            li[i]++;
            ri[i]++;
        }
    }
}

void rem(int pos, int val){
    bool done=false;
    for(int i=0;i<parts;i++){
        if(v[i].size()==0)
            continue;
        if(li[i]<=pos && ri[i]>=pos && !done){
            rem(i,pos-li[i],val);
            cnt[i][val]--;
            ri[i]--;
            done=true;
        }else if(done){
            li[i]--;
            ri[i]--;
        }
    }
}

int getval(int pos){
    for(int i=0;i<parts;i++){
        if(li[i]<=pos &&ri[i]>=pos){
            return v[i][pos-li[i]];
        }
    }
}

int query(int l, int r, int k){
    int ans=0;
    for(int i=0;i<parts;i++){
        if(li[i]>=l && ri[i]<=r){
            ans+=(cnt[i].count(k)?cnt[i][k]:0);
        }else if(li[i]>r || ri[i]<l){
            continue;
        }else{
            for(int j=0;j<v[i].size();j++){
                if(li[i]+j>=l && li[i]+j<=r){
                    ans+=(v[i][j]==k);
                }
            }
        }
    }
    return ans;
}

void upd(int l, int r){
    int val = getval(r);
    ins(l,val);
    rem(r+1, val);
}

int ty;

void show(){
    for(int i=0;i<parts;i++){
        for(auto u:v[i]){
            cout << u << " ";
        }
        cout << endl;
    }
}



int main()
{
    ios::sync_with_stdio(0);
    cin >> n;
    block=sqrt(n);
    parts=(n-1)/block +1;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    buildsqt();
    int ans=0;
    cin >> q;
    int tot=0;
    for(int i=1;i<=q;i++){
        if(tot%block==0){
            builarr();
            buildsqt();
            tot++;
        }
        cin >> ty >> l >> r;
        l = (l+ans-1)%n;
        r = (r+ans-1)%n;
        if(l>r)
            swap(l,r);
        if(ty==1){
            tot++;
            upd(l,r);
        }else{
            cin >> k;
            k=(k+ans-1)%n +1;
            ans=query(l,r,k);
            cout << ans << endl;
        }
    }
    return 0;
}

