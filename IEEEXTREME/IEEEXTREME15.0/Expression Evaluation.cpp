//100%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e6 +5 ;
const int MOD = 1e9 + 7;

ll mul(ll u , ll v, ll mod=MOD){
	return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
	return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
	return ((u%mod)-(v%mod)+mod)%mod;
}


int t;
char s[N];
int n;


bool issign(char c){
    return (c=='+') || (c=='-') || (c=='*');
}
bool isnum(char c){
    return (c<='9' && c>='0');
}

int getsign(char c){
    if(c=='+')
        return -1;
    if(c=='-')
        return -2;
    if(c=='*')
        return -3;
}
vector<int> vals[N];
stack<int> id;

int getans(int curid){
    int res=0;
    vector<bool> vis(vals[curid].size());
    for(int i=2;i<vals[curid].size();i++){
        if(vals[curid][i-1]==-3){
            vis[i-1]=1;
            vis[i-2]=1;
            vals[curid][i] = mul(vals[curid][i-2], vals[curid][i]);
        }
    }
    int curmul=1;
    for(int i=0;i<vals[curid].size();i++){
        if(vis[i])
            continue;
        if(vals[curid][i]==-2){
            curmul=-1;
        }else if(vals[curid][i]==-1)
            curmul=1;
        else{
            res=add(res, mul(curmul , vals[curid][i]));
        }
    }
    return res;
}

int main(){
    //freopen("input.txt", "r", stdin);
    cin >> t;
    while(t--){
        while(!id.empty())
            id.pop();
        s[0]='(';
        scanf("%s",s+1);
        n = strlen(s);
        s[n]=')';
        n++;
        s[n]=0;
        bool cond=true;
        for(int i=1;i<n;i++){
            if(s[i-1]=='(' && s[i]==')')
                cond=false;
            if(s[i-1]==')' && s[i]=='(')
                cond=false;
            if(issign(s[i-1]) && issign(s[i]))
                cond=false;
            if(s[i-1]=='(' && issign(s[i]))
                cond=false;
            if(issign(s[i-1]) && s[i]==')')
                cond=false;
            if(isnum(s[i-1]) && s[i]=='(')
                cond=false;
            if(s[i-1]==')' && isnum(s[i]))
                cond=false;
        }
        if(!cond){
            puts("invalid");
            continue;
        }
        int opens=0;
        id.push(0);
        vals[0].clear();
        int curid=0;
        for(int i=0;i<n;){
            if(s[i]=='('){
                opens++;
                curid++;
                vals[curid].clear();
                id.push(curid);
                i++;
                continue;
            }else if(s[i]==')'){
                if(opens==0){
                    cond=false;
                    break;
                 }
                opens--;
                int ans = getans(id.top());
                id.pop();
                vals[id.top()].pb(ans);
                i++;
                continue;
            }
            if(issign(s[i])){
                //cout << s[i] << " "<< id.top() << endl;
                vals[id.top()].pb(getsign(s[i]));
                i++;
                continue;
            }
            int j=i;
            int res=0;
            while(isnum(s[j])){
                res=mul(res, 10);
                res=add(res, (s[j]-'0'));
                j++;
            }
            vals[id.top()].pb(res);
            i=j;
        }

        if(!cond || opens){
            puts("invalid");
            continue;
        }
        cout << vals[0][0] << endl;

    }
    return 0;
}
