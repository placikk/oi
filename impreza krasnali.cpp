//Michal Plata
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define st first
#define nd second
#define pb push_back
#define rep(i,a,b) for(ll i=a;i<=b;i++)
#define all(a) a.begin(),a.end()
const int mxN = 2e5+7;
const int mod = 1e9+7;
vector<int> graf[mxN]; //1-n ludzie, n+1-2n miejsca
int t[mxN],n;
set<int> zajete;
int ile_zostalo;
bool ok = 1;
int k = 0;
int kolor[mxN];
int cnt_k[mxN];
int wys[mxN];

void dfs(int v){
	if(zajete.find(v) != zajete.end()) return;
	kolor[v] = k;
	for(auto u : graf[v]) if(kolor[u] == 0) dfs(u);
}

void wywal_pow();
void sprawdz(int v);
 
void brut(){
	vector<int> v;
	rep(i,1,n) v.pb(i);
	int res = 0;
	do{
		bool spoko = 1;
		rep(i,2,n-1) if(t[i] != v[i-2] && t[i] != v[i]) spoko = 0;
		if(t[1] != v[1]) spoko = 0;
		if(t[n] != v[n-2]) spoko = 0;
		if(spoko) res++;
	}while(next_permutation(all(v)));
	cout << res << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	ile_zostalo = n;
	rep(i,1,n) cin >> t[i];
	if(n <= 3){
		brut();
		return 0;
	}
	rep(i,1,n-1){
		graf[t[i]].pb(i+n+1);
		graf[i+n+1].pb(t[i]);
	}
	rep(i,2,n){
		graf[t[i]].pb(i+n-1);
		graf[i+n-1].pb(t[i]);
	}
	wywal_pow();
	rep(i,1,n){
		if(wys[t[i]] == 0) wys[t[i]] = i;
		else if(wys[t[i]]+2 != i) ok = 0;
		else{
			zajete.insert(i-1+n);
			zajete.insert(t[i]);
			ile_zostalo--;
		}
	}
	rep(i,1,n) sprawdz(i);
	if(ok == 0){
		cout << "0\n";
		return 0;
	}
	rep(i,1,n+n){
		if(kolor[i] == 0){
			k++;
			dfs(i);
		}
	}
	rep(i,1,n+n) cnt_k[kolor[i]]++;
	ll res = 1;
	rep(i,1,k) if(cnt_k[i] > 1){
		res = (res*((cnt_k[i]/2)+1))%mod;
		ile_zostalo -= (cnt_k[i]/2);
	}
	rep(i,1,ile_zostalo) res = (res*i)%mod;
	cout << res << "\n";
}


void wywal_pow(){
	set<int> pom;
	rep(i,1,2*n){
		for(auto x : graf[i]) pom.insert(x);
		graf[i].clear();
		for(auto q : pom) graf[i].pb(q);
		pom.clear();
	}
}

void sprawdz(int v){
	if(ok == 0) return;
	if(zajete.find(v) != zajete.end()) return;
	if(graf[v].size() == 0) return;
	set<int> w;
	for(auto u : graf[v]) if(zajete.find(u) == zajete.end()) w.insert(u);
	if(w.size() == 0 && graf[v].size() > 0) ok = 0;
	if(w.size() == 1){
		auto it = w.begin();
		int p = *it;
		if(zajete.find(p) != zajete.end()) ok = 0;
		zajete.insert(v);
		zajete.insert(p);
		ile_zostalo--;
		for(auto u : graf[p]) sprawdz(u);
		return;
	}
	if(w.size() == 3){
		auto it = w.begin();
		int x = *it; it++;
		int y = *it; it++;
		int z = *it;
		if(x+2 != y || y+2 != z) ok = 0;
		if(zajete.find(y) != zajete.end()) ok = 0;
		zajete.insert(v);
		zajete.insert(y);
		ile_zostalo--;
		for(auto u : graf[y]) sprawdz(u);
		return;
	}
}