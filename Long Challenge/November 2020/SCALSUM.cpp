#include <iostream>
#include <vector>
// #include <assert.h>
#include <algorithm>
#include <queue>

using namespace std;
#define ll long long
#define mod 4294967296ll
#define pb push_back
#define nl cout<<"\n"
#define db(x) cout<<x<<" "
#define fi(a,b) for(int i=a;i<b;i++)
#define fj(a,b) for(int j=a;j<b;j++)
#define fk(a,b) for(int k=a;k<b;k++)
#define F first
#define S second

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define mxsize (int)3e5+5
int n,q;
vector<int> adj[mxsize];  
vector<ll> weight(mxsize);
vector<int> par(mxsize,0);
vector<pair<int,ll>> mp[mxsize];
vector<int> depth(mxsize,0);
vector<int> indegree(mxsize,0);
vector<ll> self(mxsize);

ll read () {
	bool minus = false;
	ll result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}

ll search(int& u,int& v){
	if(u==v)	return self[u];
	for(int i=0;i<mp[u].size();i++){
		if(mp[u][i].F==v){
			return mp[u][i].S;
		}
	}
	return -2;
}

ll compute(int& u,int& v){
	if(u>v)	swap(u,v);
	ll val=search(u,v);
	if(val!=-2)	return val;
	
	ll ans=0;
	vector<pair<ll,pair<int,int>>> mediate;
	mediate.push_back({0,{u,v}});
	
	while(u!=0){
		if(u>v)	swap(u,v);
		ll val=search(u,v);
		if(val!=-2){
			ans+=val;
			ans%=mod;
			break;
		}
		if(indegree[u]>=3)		mediate.push_back({ans,{u,v}});

		ans+=(weight[u]*weight[v])%mod;
		ans%=mod;
		u=par[u];
		v=par[v];
	}
	for(int i=0;i<mediate.size();i++){
		ll tempans=(ans-mediate[i].F+mod)%mod;
		u=mediate[i].S.F;
		v=mediate[i].S.S;
		mp[u].push_back({v,tempans});
	}
	return ans;
}

void fun(){
	vector<pair<int,int>> temp;
	vector<int> u(q+1,0),v(q+1,0);
	fi(1,q+1){
		u[i]=read();
		v[i]=read();
		temp.push_back({depth[u[i]],i});
	}
	sort(temp.begin(),temp.end());
	vector<ll> ans(q+1,0);
	
	for(int i=0;i<q;i++){
	    // assert(q-i>=5000);
		ans[temp[i].S]=compute(u[temp[i].S],v[temp[i].S]);
	}
	
	for(int i=1;i<=q;i++)       printf("%lld\n",ans[i]);
	
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	#ifndef ONLINE_JUDGE
		freopen("/ATOM/input.txt", "r", stdin);
		freopen("/ATOM/output.txt", "w", stdout);
	#endif
	n=read();q=read();
	fi(1,n+1)	weight[i]=read();
	int x,y;
    fi(0,n-1){
		x=read();y=read();
        adj[x].pb(y);
        adj[y].pb(x);
        indegree[x]++;
        indegree[y]++;
    }
    queue<int> q;
	q.push(1);
	par[1]=-1;		
	self[1]=(weight[1]*weight[1])%mod;
	depth[1]=0;
	while(!q.empty()) {
		int sz=q.size();
		for(int i=0;i<sz;i++){
			int x=q.front();
			q.pop();
			for(auto &child:adj[x]){
				if(par[child]==0){
					par[child]=x;
					q.push(child);
					depth[child]=depth[x]+1;
					self[child]=(self[x]+(weight[child]*weight[child])%mod)%mod;
				}
			}
		}
	}
	par[1]=0;
	fun();
}
