#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
//#include <atcoder/all>
#endif

using namespace std;
//using namespace atcoder;
#define INF 1e9
#define repi(n) for(int i=0;i<n;i++)
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()
#define uset unordered_set
#define umap unordered_map
typedef long long ll;
typedef vector<int> vi;
typedef vector< vector<int> > vvi;
typedef vector<ll> vl;
typedef vector< vector<ll> > vvl;
typedef vector<bool> vb;
typedef vector< vector<bool> > vvb;
typedef vector<double> vd;
typedef vector< vector<double> > vvd;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

struct Edge{
	int to;
	int ind;
	ll w;
	Edge(int to,int ind,ll w):to(to),ind(ind),w(w){}
};

struct Point{
	int x;
	int y;
	Point(int x,int y):x(x),y(y){}
};

using Graph=vector<vector<Edge>>;

template <typename T>
bool chmin(T &x,T y){
	if(x>y){
		x=y;
		return true;
	}
	return false;
}

template <typename T>
bool chmax(T &x,T y){
	if(x<y){
		x=y;
		return true;
	}
	return false;
}

template <typename T>
string toBinary(T x){
	string res="";
	while(x!=0){
		if(x&1){
			res="1"+res;
		}
		else{
			res="0"+res;
		}
		x=x>>1;
	}
	return res;
}

int toDecimal(string s){
	int res=0;
	int d=1;
	for(int i=s.size()-1;i>=0;i--){
		if(s[i]=='1'){
			res+=d;
		}
		d*=2;
	}
	return res;
}

template <typename T>
void printVector(vector<T> &x){
	for(auto i : x)cout<<i<<" ";
	cout<<endl;
}

template <typename T>
void printVector2d(vector< vector<T> > &x){
	for(auto &i : x){
		for(auto j : i){
			cout<<j<<" ";
		}
		cout<<endl;
	}
}

void printYesOrNo(bool x){
	cout<<(x ? "Yes" : "No")<<endl;
}

Graph G;
vb seen;
int d;
int k;
vi ans;
vi rnum;
map<pair<int,int>,int> mp;

void dfs(int x,int p,int day){
	day%=d+1;
	if(day==0)day++;
	while(rnum[day]==k){
		day++;
		day%=d+1;
		if(day==0)day++;
	}
	int tmpx=x;
	int tmpp=p;
	if(tmpx>tmpp){
		swap(tmpx,tmpp);
	}
	if(mp.find({tmpx,tmpp})!=mp.end()){
	if(seen[mp[{tmpx,tmpp}]])return;
	ans[mp[{tmpx,tmpp}]]=day;
	rnum[day]++;
	seen[mp[{tmpx,tmpp}]]=true;
	}
	for(auto v : G[x]){
		dfs(v.to,x,day+1);
	}
}

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout<<fixed<<setprecision(15);
	int n,m;
	cin>>n>>m>>d>>k;
	G.resize(n);
	seen.resize(m,false);
	ans.resize(m,false);
	rnum.resize(d+1,0);
	vector<pair<pair<int,int>,ll>> es(m);
	repi(m){
		int u,v;
		ll w;
		cin>>u>>v>>w;
		u--;v--;
		if(u>v){
			swap(u,v);
		}
		G[u].push_back(Edge(v,i,w));
		G[v].push_back(Edge(u,i,w));
		mp[make_pair(u,v)]=i;
		es[i]=make_pair(make_pair(u,v),w);
	}
	dfs(10,10,1);
	//for(int i=1;i<=d;i++)cerr<<rnum[i]<<" ";
	//cerr<<endl;
	printVector(ans);
	return 0;
}