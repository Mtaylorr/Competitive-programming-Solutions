#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
#define INV_2 499122177
#define INF 1000000000
#define PI 3.14159265358979323846
#define eps 1e-9
#define MOD1 998244353
#define MOD2 1000000007

using namespace std;

vector<string>a;
vector<int> v[2][700005];
int trie[2][700005][28];
int nxt[2];
string s;

void init()
{
    for(int k = 0; k < 2; k++)
    	for(int i = 0; i <= 700000; i++)
    		for(int j = 0; j < 28; j++)
    			trie[k][i][j]=-1;
}

void insert(int id_trie, int idx, int s_idx, int cu)
{
	v[id_trie][idx].push_back(cu);
	//if(idx)
	//	cout << id_trie << ' ' << s[s_idx-1] << '\n';
	//cout << "currently here: ";
	if(s_idx == s.length())
		return;
	
	//for(int i = 0; i < v[id_trie][idx].size(); i++)
	//	cout << a[v[id_trie][idx][i]] << ' ';
	//cout << '\n';
	if(trie[id_trie][idx][s[s_idx]-'a'] == -1)
	{
		trie[id_trie][idx][s[s_idx]-'a'] = nxt[id_trie];
		nxt[id_trie]++;
	}
	insert(id_trie, trie[id_trie][idx][s[s_idx]-'a'], s_idx+1, cu);

}


int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	nxt[0]=1;
	nxt[1]=1;
	init();
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; i++)
	{
		cin >> s;
		//cout << s << '\n';
		a.push_back(s);
		if(s.length() < 3)
			continue;
		insert(0, 0, 0, i);
		reverse(s.begin(), s.end());
		//cout << s << '\n';
		insert(1, 0, 0, i);
	} 
	string ss;
	vector<int>v1, v2;
	set<pair<int, int> >ans;
	for(int ca = 0; ca < m; ca++)
	{
		cin >> ss;
		v1.clear();
		v2.clear();
		ans.clear();
		int l = ss.length();
		if(l <= 2)
		{
			cout << "none\n";
			continue;
		}
		for(int j = 0; j < l; j++)
		{
			v1.push_back(-1);
			v2.push_back(-1);
		}
		int idx=0;
		for(int j = 0; j < ss.length(); j++)
		{
			if(trie[0][idx][ss[j]-'a']==-1)
				break;
			idx = trie[0][idx][ss[j]-'a'];
			v1[j]=idx;
		}
		idx=0;
		for(int j = l-1; j >= 0; j--)
		{
			if(trie[1][idx][ss[j]-'a']==-1)
				break;
			idx = trie[1][idx][ss[j]-'a'];
			v2[j]=idx;
		}
		for(int i = 0; i < l; i++)
		{
			if(i < 2)
				continue;
			if(v1[i]==-1)
				continue;
			if(l-i >= 3)
			{
				if(v2[i] != -1)
				{
					if(!((v[0][v1[i]].size() == 1) && (v[1][v2[i]].size() == 1)))
					{
						ans.insert(make_pair(n+1, n+2));
						ans.insert(make_pair(n+2, n+2));
					}
					else
					{
						ans.insert(make_pair(v[0][v1[i]][0], v[1][v2[i]][0]));
					}
				}
			}
			if(ans.size() > 1)
				break;
			if(l-i-1 >= 3)
			{
				if(v2[i+1] != -1)
				{
					if(!((v[0][v1[i]].size() == 1 )&& (v[1][v2[i+1]].size() == 1)))
					{
						ans.insert(make_pair(n+1, n+2));
						ans.insert(make_pair(n+2, n+2));
					}
					else
					{
						ans.insert(make_pair(v[0][v1[i]][0], v[1][v2[i+1]][0]));
					}
				}
			}
			if(ans.size() > 1)
				break;
		}
		if(ans.empty())
			cout << "none\n";
		if(ans.size() == 1)
			cout << a[(*ans.begin()).first] << ' ' << a[(*ans.begin()).second] << '\n';
		if(ans.size() > 1)
			cout << "ambiguous\n"; 
	}
}
//07-02-46
