//https://vjudge.net/problem/OpenJ_Bailian-1165
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;

vector<vector<int> > adj(11*11*11*11*11);

int n,f;

int si[12]={0, 4,0,1,2,3,4,0,0,0,0,0};
int sj[12]={0, 0,0,0,0,0,0,0,1,2,3,4};
int di[12]={1,-1,0,0,0,0,0,1,1,1,1,1};
int dj[12]={1, 1,1,1,1,1,1,0,0,0,0,0};
bool vis[12];
int grid[5][5];
int rem[12], remsz=12;
vector<vector<vector<int> > > sol;

bool isprime(int u){
    if(!(u&1))
        return u==2;
    for(int i=3;i*i<=u;i+=2){
        if(u%i==0)
            return 0;
    }
    return 1;
}


int digsum(int x){
    int sm=0;
    while(x){
        sm+=x%10;
        x/=10;
    }
    return sm;
}



void addNumber(int x){
    for(int msk=0;msk<(1<<5);msk++){
        int y = x, s=0,p=1;
        for(int i=0;i<5;i++){
            int d = ((msk>>i)&1)? 10: y%10;
            y/=10;
            s+=d*p;
            p*=11;
        }
        adj[s].pb(x);
    }
}

int read(int ind){
    int rt=0;
    for(int i=si[ind], j=sj[ind],k=0;k<5;k++,i+=di[ind], j+=dj[ind]){
        rt*=11;
        rt+=grid[i][j];
    }
    return rt;
}

void write(int ind ,int val, int b){
    int p = b*b*b*b;
    int rt=0;
    for(int i=si[ind], j=sj[ind],k=0;k<5;k++,i+=di[ind], j+=dj[ind]){
        grid[i][j] =(val/p)%b;
        p/=b;
    }
}
vector<vector<int> > getGrid(){
    vector<vector<int> > res(5);
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            res[i].pb(grid[i][j]);
        }
    }
    return res;
}


void swim(int depth){
    if(depth==12){
        sol.pb(getGrid());
        return ;
    }
    int mn = 1e9;
    int mni=-1;
    int mnx;
    for(int i=0;i<remsz;i++){
        int x = read(rem[i]);
        if(adj[x].size()<mn){
            mn=adj[x].size();
            mni = i;
            mnx = x;
        }
    }
    swap(rem[mni], rem[--remsz]);
    for(auto u:adj[mnx]){
        write(rem[remsz], u, 10);
        swim(depth+1);
    }
    write(rem[remsz], mnx,11);
    swap(rem[mni], rem[remsz++]);

}

int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&f);
    for(int i=10001;i<100000;i+=2){
        if(digsum(i)==n && isprime(i)){

            addNumber(i);
        }
    }
    for(int i=0;i<remsz;i++){
        rem[i]=i;
    }

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            grid[i][j]=10;
        }
    }
    grid[0][0]=f;
    swim(0);
    sort(sol.begin(),sol.end());
    for(int i=0;i<sol.size();i++){
        for(int j=0;j<5;j++){
            for(int k=0;k<5;k++){
                printf("%d",sol[i][j][k]);
            }
            puts("");
        }
        if(i<sol.size()-1)
            puts("");
    }
    return 0;
}

