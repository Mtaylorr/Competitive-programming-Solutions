//100%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 +5 ;
const int MOD = 1e9 +7, B= 37;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

vector<int> x,y;
char grid[505][505];
char pat[505][505];

int t,r,c,a,b;
int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        x.clear();
        y.clear();
        scanf("%d%d",&r,&c);
        for(int i=0;i<r;i++){
            scanf("%s",grid[i]);
            for(int j=0;j<c;j++){
                if(grid[i][j]=='.')
                    x.pb(1);
                else
                    x.pb(-1);
            }
        }

        scanf("%d%d",&a,&b);
        int cnt=0;
        for(int i=0;i<a;i++){
            scanf("%s",&pat[i]);
            int last = c;
            if(i==a-1)
                last=b;
            for(int j=0;j<last;j++){
                if(j<b){
                    if(pat[i][j]=='.')
                        y.pb(1);
                    else if(pat[i][j]=='#')
                        y.pb(-1);
                    else{
                        y.pb(0);
                        cnt++;
                    }
                }else{
                    y.pb(0);
                    cnt++;
                }
            }
        }
        reverse(y.begin(),y.end());
        vector<int> res = multiply(x,y);
        int m = y.size();
        int ans=0;
        for(int i=0;i+a<=r;i++){
            for(int j=0;j+b<=c;j++){
                int id = i*c + j;
                //cout << id << " " << res[id] << endl;
                if(res[m-1+id]==m-cnt){
                    ans++;
                }
            }
        }
        cout << ans << endl;

    }
    return 0;
}
