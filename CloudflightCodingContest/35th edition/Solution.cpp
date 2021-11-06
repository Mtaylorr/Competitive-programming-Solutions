// level 3 

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5  +5 ;

int n;
string s1,s2,s3;
set<string> varnames;
map<string,string> vals;

set<string> reservedwords = {"var", "set", "print", "if", "else", "end", "start",
                                "return"};

void err(){
    cout << "ERROR\n";
}

string toprint;


string getval(string s){
    if(varnames.count(s)){
        return vals[s];
    }
    return s;
}

int applyif(bool wr);
int applyprint(bool x);
int work(string s , bool x);
int applyvar(bool x);
int applyfunc(bool x);
int applyset(bool x);

int work(string s , bool x){
    if(s=="print")
        return applyprint(x);
    if(s=="end")
        return 1;
    if(s=="return"){
        string s;
        cin >> s;
        return 0;
    }
    if(s=="if")
        return applyif(x);
    if(s=="var")
        return applyvar(x);
    if(s=="set")
        return applyset(x);
    if(s=="start")
        return applyfunc(1);
}

int applyfunc(bool x){
    varnames.clear();
    vals.clear();
    bool gotcut=0;
    bool erro=0;
    toprint="";
    while(1){
        cin >> s1;
        int res = work(s1,(!gotcut)&& (!erro));
        if(res==1)
            break;
        if((!gotcut) && (!erro)){
            if(res==0)
                gotcut=1;
            if(res==-1)
                erro=1;

        }
    }
    if((!erro))
        cout << toprint<<"\n";
}

int applyvar(bool x){
    cin >> s2 >> s3;
    if(x==0)
        return -2;
    if(varnames.count(s2) || reservedwords.count(s2)  || reservedwords.count(s3)){
        err();
        toprint="";
        return -1;
    }else{
        varnames.insert(s2);
        vals[s2]=getval(s3);
    }
    return -2;
}

int applyset(bool x){
    cin >> s2 >> s3;
    if(x==0)
        return -2;
    if(varnames.count(s2)==0 || reservedwords.count(s2)  || reservedwords.count(s3)){
        err();
        toprint="";
        return -1;
    }else{
        vals[s2]=getval(s3);
    }
    return -2;
}

int applyprint(bool x){
    cin >> s2;
    if(x){
        toprint+=getval(s2);
    }
    return -2;
}


int applyif(bool wr){
    string s;
    cin >> s ;
    s=getval(s);
    bool x = s=="true";
    bool gotcut=0;
    bool erro=0;
    if(wr && s!="true" && s!="false"){
        erro=1;
        err();
    }
    string s1;
    while(1){
        cin >> s1;
        int res = work(s1,wr&&x&&(!gotcut)&&(!erro));
        if(res==1)
            break;
        if(wr && x==1 && !gotcut  && (!erro)){
            if(res==-1){
                erro=true;
            }
            if(res==0){
                gotcut=true;
            }
        }
    }
    cin >> s;
    while(1){
        cin >> s1;
        int res = work(s1,wr&&(!x)&&(!gotcut)&&(!erro));
        if(res==1)
            break;
        if(wr && x==0 && (!gotcut) && (!erro)){
            if(res==-1){
                erro=true;
            }
            if(res==0){
                gotcut=true;
            }

        }
    }
    if(erro)
        return -1;
    if(gotcut)
        return 0;
    return -2;
}




int main(){
    //freopen("input.txt", "r", stdin);
    freopen("level3_4.in", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    string s;
    while(cin >> s){
        work(s,1);
    }

    return 0;
}
