#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 1e9 + 7 ;


int n;
string s;
int m;

int main(){
    //freopen("input.txt", "r",stdin);
    while(1){
        scanf("%d",&n);
        if(!n)
            break;
        int sum1=0;
        int sum2=0;
        for(int i=0;i<n;i++){
            cin >> s >> m;
            if(s[0]=='T'){
                if(sum1<m){
                    if(sum1)
                        cout << "TAKE " <<1<<" "<< sum1 << endl;
                    cout << "MOVE 2->1 "<< sum2 << endl;
                    m-=sum1;
                    sum1=sum2;
                    sum2=0;
                }
                cout << "TAKE " <<1<<" "<< m << endl;
                sum1-=m;

            }else{
                cout << "DROP 2 "<< m << endl;
                sum2+=m;
            }
        }
        cout << endl;

    }
    return 0;
}
