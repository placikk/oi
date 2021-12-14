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
const int mxN = 5e5+7;
pair<int,pair<int,int>> a[mxN];

bool cmp(pair<int,pair<int,int>> x, pair<int,pair<int,int>> y){
	if(x.nd.st < y.nd.st) return 1;
	return 0;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n;
	rep(i,1,n) cin >> a[i].st >> a[i].nd.st;
	rep(i,1,n) a[i].nd.nd = i;
	sort(a+1,a+n+1,cmp);
	int czas = 0;
	priority_queue<pair<int,pair<int,int>>> q;
	rep(i,1,n){
		if(czas+a[i].st <= a[i].nd.st){
			czas += a[i].st;
			q.push(a[i]);
		}else{
			q.push(a[i]);
			int p = q.top().st;
			czas = czas + a[i].st - p;
			q.pop();
		}
	}
	cout << q.size() << "\n";
	vector<pair<int,pair<int,int>>> v;
	while(q.size() > 0){
		pair<int,pair<int,int>> p = q.top();
		q.pop();
		v.pb(p);
	}
	sort(all(v),cmp);
	int z = 1;
	for(auto x : v){
		cout << x.nd.nd << " " << z << "\n";
		z += x.st;
	}
}