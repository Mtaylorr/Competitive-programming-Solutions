#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5;
const int MOD = 1e9 +7 ;

int catalan[N];

void mul(int &u , int v, int mod=MOD){
	u=((u%mod)*1ll*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD){
	return ((u%mod)+0ll+(v%mod)+mod)%mod;
}

int sub(int u, int v , int mod=MOD){
	return ((u%mod)+0ll-(v%mod)+mod)%mod;
}

int powe(int u, ll v, int mod=MOD){
	int ans=1;
	int acc=u;
	while(v){
		if(v%2){
			mul(ans,acc,mod);
		}
		mul(acc,acc,mod);
		v/=2;
	}
	return ans;
}

int  inv(int u,int mod=MOD){
	return powe(u,mod-2,mod);
}


int a[N];
int n;
int id[N];
int pos[N];
int nxt[N];

int getid(int u){
    return (u==id[u]?u:id[u]=getid(id[u]));
}

void uni(int u, int v){
    u=getid(u);
    v=getid(v);
    if(u==v)
        return ;
    id[u]=v;
}



bool samset(int u, int v){
    return getid(u)==getid(v);
}

int main()
{
    //freopen("input.txt", "r",stdin);
    memset(pos, -1, sizeof(pos));
    catalan[0]=catalan[1]=1;
    for(int i=2;i<=1000000;i++){
        catalan[i]=catalan[i-1];
        mul(catalan[i],2*i);
        mul(catalan[i],2*i-1);
        mul(catalan[i],inv(i));
        mul(catalan[i],inv(i+1));
    }

    scanf("%d",&n);
    if(n==0){
        cout << 1;
        return 0;
    }
    for(int i=0;i<n;i++){
        id[i]=i;
        scanf("%d",&a[i]);
    }
    for(int i=n-1;i>=0;i--){
        if(pos[a[i]]==-1){
            nxt[i]=n+1;
        }else{
            nxt[i]=pos[a[i]];
        }
        pos[a[i]]=i;
    }
    int ans=1;
    for(int i=1000000;i>=0;i--){
        if(pos[i]==-1)
            continue;
        for(int j=pos[i];j<n;j=nxt[j]){
            if(j-1>=0 && a[j-1]>=i){
                uni(j-1,j);
            }
            if(j+1<n && a[j+1]>=i){
                uni(j,j+1);
            }
        }
        int sz=0;
        int bf=-1;
        for(int j=pos[i];j<n;j=nxt[j]){
            if(getid(j)==bf){
                sz++;
            }else{
                mul(ans, catalan[sz]);
                sz=1;
            }
            bf=id[j];
        }

        mul(ans, catalan[sz]);
    }
    cout << ans;


    return 0;
}
