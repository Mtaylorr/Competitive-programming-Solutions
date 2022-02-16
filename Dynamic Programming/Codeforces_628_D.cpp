//https://codeforces.com/problemset/problem/628/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 + 7 ;


int mul(int u , int v, int mod=MOD){
	return ((u%mod)*1ll*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD){
	return ((u%mod)+0ll+(v%mod)+mod)%mod;
}

int sub(int u, int v , int mod=MOD){
	return ((u%mod)+0ll-(v%mod)+mod)%mod;
}

int powe(int u, int v, int mod=MOD){
	int ans=1;
	int acc=u;
	while(v){
		if(v%2){
			ans=mul(ans,acc,mod);
		}
		acc = mul(acc,acc,mod);
		v/=2;
	}
	return ans;
}


int m,d,l;
string a, b;
int po[2005];

int dp[2005][2005][2];

int solve(int i=0, int mo=0, int iseq=1){
    if(i>=a.size()){
        return mo==0;
    }
    int &rs = dp[i][mo][iseq];
    if(rs!=-1)
        return rs;
    rs = 0;
    if(i%2){
        int newmo = add(mo, mul(po[l-i-1], d,m),m);
        if(!iseq){
            rs = solve(i+1,newmo, iseq);
        }else{
            if((a[i]-'0') <d)
                rs=0;
            else if((a[i]-'0')==d){
                rs = solve(i+1, newmo, iseq);
            }else{
                rs= solve(i+1, newmo, 0);
            }
        }
    }else{
        int up = 9;
        if(iseq)
            up=(a[i]-'0');
        for(int j=1-(i!=0);j<=up;j++){
            if(j==d)
                continue;
            if(j==up && iseq){
                int newmo = add(mo, mul(po[l-i-1], j,m),m);
                rs=add(rs, solve(i+1, newmo, iseq));
            }else{
                int newmo = add(mo, mul(po[l-i-1], j,m),m);
                rs=add(rs, solve(i+1, newmo, 0));
            }
        }
    }
    return rs;
}

int isvalid(){
    int rs=0;
    for(int i=0;i<l;i++){
        rs+=mul((po[l-i-1]), a[i]-'0',m);
        rs%=m;
        if(i%2){
            if((a[i]-'0') !=d)
                return 0;
        }
        if(i%2==0){
            if((a[i]-'0')==d)
                return 0;
        }
    }
    return rs==0;
}

int main(){
    freopen("input.txt", "r",stdin);
    memset(dp, -1,sizeof(dp));
    scanf("%d%d",&m,&d);
    cin >> a;
    l=a.size();
    po[0]=1;
    for(int i=1;i<=l+1;i++){
        po[i]=mul(po[i-1],10,m);
    }
    int ans = sub(solve(), isvalid());

    cin >> a;
    memset(dp, -1,sizeof(dp));
    ans=sub(solve(),ans);
    cout << ans;
    return 0;
}
