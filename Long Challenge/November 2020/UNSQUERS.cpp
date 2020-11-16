#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define pb push_back
#define nl cout<<"\n"
#define db(x) cout<<x<<" "
#define fi(a,b) for(int i=a;i<b;i++)
#define fj(a,b) for(int j=a;j<b;j++)
#define fk(a,b) for(int k=a;k<b;k++)
#define F first
#define S second
#define mxsize (int)1e5+5
int n,q,s;
vector<int> height(mxsize,0);
vector<int> sz(mxsize,0);
// vector<int> leftone(mxsize,0);
vector<int> nextgre(mxsize,0);
int segtre[4000000];
int query(int si,int ss,int se,int qa,int qb){
    if(ss>qb||se<qa)
        return INT_MIN;
    if(ss>=qa&&se<=qb)
        return segtre[si];
    int mid=(ss+se)/2;
    int left=query(2*si,ss,mid,qa,qb);
    int right=query(2*si+1,mid+1,se,qa,qb);

    return max(left,right);
}
void build_tree(int si,int ss,int se){
    if(ss==se){ 
        segtre[si]=sz[ss];
        return ;
    }
    int mid=(ss+se)/2;
    build_tree(2*si,ss,mid);
    build_tree(2*si+1,mid+1,se);
    segtre[si]=max(segtre[2*si],segtre[2*si+1]);
}

void convert(int& l,int& r,int& ans){
	l+=(s*ans-1);		l%=n;		l++;
	r+=(s*ans-1);		r%=n;		r++;
	if(l>r)	swap(l,r);
	ans=0;
}
void findnextgreater(){
	stack<int> s;
	fi(1,n+1){
		while(!s.empty()&&height[s.top()]<=height[i]){
			s.pop();
		}
		if(s.empty())	nextgre[i]=0;
		else 			nextgre[i]=s.top();
		s.push(i);
	}
}
void fill(){
	stack<int> s;
	// vector<int> faltu(n+1,0);
	for(int i=n;i>=1;i--){
		while(!s.empty()&&s.top()<=height[i]){
			s.pop();
		}
		// if(s.empty())	faltu[i]=0;
		// else			faltu[i]=s.top()-1;
		s.push(height[i]);
		sz[i]=s.size();
	}
	// int left=0;
	// for(int i=1;i<=n;i++){
	// 	if(sz[i]==1)	left=i;
	// 	leftone[i]=left;
	// }
	// next greater element of arr for faltu[i]
	findnextgreater();
	build_tree(1,1,n);
}
void fun(){
	cin>>n>>q>>s;
	fi(1,n+1)	cin>>height[i];
	fill();
	int ans=0;
	// fi(1,n+1)	db(sz[i]);
	while(q--){
		int l,r;
		cin>>l>>r;
		convert(l,r,ans);
		// db(l);db(r);
		int threshold=sz[r]-1;
		while(l<r&&threshold>0){
			int ind=nextgre[r];
			
			int dif=sz[r]-sz[ind];

			if(ind<l)	ind=l;
			// db(ind);
			int nx=query(1,1,n,ind,r);
			// db(dif);db(nx);nl;
			
			ans=max(ans,nx-threshold);
			threshold-=dif;

			r=ind;
		}

		if(l==r)	ans=max(ans,1);
		// db(l);db(r);	
		if(l<r){
			ans=max(ans,query(1,1,n,l,r)-threshold);
		}

		// else if(sz[r]==1||r==n){
		// 	// max of l to r
		// }
		// else{
		// 	for(int i=r;i>=l;i--){
		// 		if(sz[r]!=1){
		// 			//
		// 		}
		// 	}
		// 	// max of l to r
		// }
		cout<<ans<<"\n";
	}


}
// 8 7 6 5 4 3 2 1 12 13 15 16 17 18 19 20
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cout.precision(20);
	cout<<fixed;
	#ifndef ONLINE_JUDGE
		freopen("/ATOM/input.txt", "r", stdin);
		freopen("/ATOM/output.txt", "w", stdout);
	#endif
	int t=1;
	// cin>>t;
	while(t--){
		fun();
	}
}
