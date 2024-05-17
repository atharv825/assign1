#include <bits/stdc++.h> 
//Atharv Bajaj
#define int long long int
#define pb push_back
#define fi first
#define se second
#define ii pair<int, int>
#define MP make_pair
#define vi vector<int>
#define endl "\n"
#define pb push_back
#define be begin
#define up upper_bound
#define lo lower_bound
#define bi binary_search
#define si set<int>
#define msi multiset<int>
#define vii vector<pair<int, int>>
#define mii map<int, int>
#define all(v) v.begin(), v.end()
#define mems1(a) memset(a, -1, sizeof(a))
#define mems0(a) memset(a, 0, sizeof(a))
#define rep(i, s, e) for (int i = s; i < e; i++)
#define rrep(i, s, e) for (int i = s - 1; i >= e; i--)
#define yes cout<<"Yes"<<endl
#define no cout<<"no"<<endl
#define pr(a) cout<<"a"<<endl
using namespace std;
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
vector<int>kmp(string s){
    int n=s.length();
    vector<int>lps(n+1);
    int i=0,j=-1;
    lps[0]=-1;
    while(i<n){
        while(j!=-1&&s[j]!=s[i]){
            j=lps[j];
        }
        i++;j++;lps[i]=j;
    }
    return lps;
}
vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max((int)0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}
vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}
void smallestprime(){
    rep(i,2,N){
        sp[i]=i;
    }
    rep(i,2,N){
        if(sp[i]==i){
            for(int j=2*i;j<N;j+=i){
                if(sp[j]==j){
                    sp[j]=i;
                }
            }
        }
    }
}
//segment tree that gives min over the range and no of times that min occur
struct node{
    int mn,cnt;
    node(int m=1e9,int c=0){
        mn=m;
        cnt=c;
    }
};
node t[400400];
node merge(node a,node b){
    if(a.mn==b.mn){
        return node(a.mn,a.cnt+b.cnt);
    }
    else if(a.mn<b.mn)return a;
    else return b;
}
void build(int index,int l,int r){
    if(l==r){
        t[index]=node(a[l],1);
        return;
    }
    int mid=(l+r)/2;
    build(2*index,l,mid);
    build(2*index+1,mid+1,r);
    t[index]=merge(t[2*index],t[2*index+1]);

}
void update(int index,int l,int r,int pos,int val){
    if(l>pos||r<pos)return;
    if(l==r){
        t[index]=node(val,1);
        a[l]=val;
        return;
    }
    int mid=(l+r)/2;
    update(2*index,l,mid,pos,val);
    update(2*index+1,mid+1,r,pos,val);
    t[index]=merge(t[2*index],t[2*index+1]);
}
node query(int index,int l,int r,int lq,int rq){
    if(l>rq||lq>r)return 0;
    if(l>=lq&&r<=rq)return t[index];
    int mid=(l+r)/2;
    return merge(query(2*index,l,mid,lq,rq),query(2*index+1,mid+1,r,lq,rq));
}
class trie{
    struct node{
        char val;
        string s;
        node* child[26];
        int isterminal;
        int cnt;
    };
    node* root;
    node* getnode(char c){
        node* newnode=new node;
        newnode->val=c;
        rep(i,0,26)newnode->child[i]=NULL;
        newnode->isterminal=0;
        newnode->cnt=0;
        newnode->s="";
        return newnode;
    }
    public:
    trie(){
        root=getnode('/');

    }
    void insert(string word){
        node* cur=root;
        for(int i=0;i<word.length();i++){
            int idx=word[i]-'a';
            if(cur->child[idx]==NULL){
                cur->child[idx]=getnode(word[i]);
            }
            cur->child[idx]->cnt+=1;
            cur=cur->child[idx];
        }
        cur->isterminal+=1;
        cur->s=word;
    }
    bool search(string word){
        node*cur=root;
        for(int i=0;i<word.length();i++){
            int idx=word[i]-'a';
            if(cur->child[idx]==NULL){
                return false;
            }
            cur=cur->child[idx];
        }
        return (cur->isterminal>0);
    }
    bool startwith(string prefix){
        node*cur=root;
        for(int i=0;i<prefix.length();i++){
            int idx=prefix[i]-'a';
            if(cur->child[idx]==NULL){
                return false;
            }
            cur=cur->child[idx];
        }
        return (cur->cnt>0);
    }

};
void solve(){
    int n;
    cin>>n;
    vector<string>st(n);
    for(int i=0;i<n;i++)cin>>st[i];
    cout<<solution(st)<<endl;
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    //cin >> t;
    for (int i = 0; i < t; i++)
    {
        solve();
    }
}

