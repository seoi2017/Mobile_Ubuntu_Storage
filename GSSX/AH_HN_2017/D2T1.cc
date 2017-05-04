//AHOI\HNOI 2017 Day2 T1 dalao
//Accepted at 2017/5/4 17:00
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
const int jp[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};  
const int N=105,INF=(int)1e9;  
int n,m,mc,a[N],w[N],C[N],dp[N][N],k,fl[N],maxc,tmp;  
map<int,int> s;  
int dat[1000005];  
int find(int x){  
    if(x<=1000000)return dat[x];  
    return s[x];  
}  
void insert(int x,int ans){  
    if(x<=1000000)dat[x]=ans;  
    else s[x]=ans;  
}
int calc(int n){  
    if(n<0)return INF;  
    if(n==0)return 0;  
    if(n==1)return 1;  
    int l=n,ed=1;  
    for(int i=0;i<25;i++)while(l%jp[i]==0)ed=jp[i],l/=jp[i];  
    if(l>1)return INF;  
    if(find(n))return find(n);  
    int lim=k+1;  
    for(int i=ed;i<lim-1;i++)if(n%i==0){  
        int t=i+1;  
        l=n;  
        for(int j=i;j>=2&&t<=lim&&l>1;j--)while(l%j==0){l/=j;++t;}  
        if(l==1)lim=min(lim,t);  
    }  
    insert(n,lim);  
    return lim;  
}  
void dfs(int x,int pos){  
    if(tmp==m)return;  
    int t=calc(x);  
    if(t>k/2)return;  
    for(int i=pos;i>=0;i--)if((long long)x*jp[i]<=maxc)dfs(x*jp[i],i);  
    for(int i=0;i<=k-2*t;i++){  
        for(int j=1;j<=m;j++)if(!fl[j]){  
            int l=calc(C[j]-x-i);  
            if(l+t+i<=k)fl[j]=1,++tmp;  
        }  
    }  
}
int main(){  
    freopen("input.txt","r",stdin);  
    freopen("output.txt","w",stdout);  
    scanf("%d%d%d",&n,&m,&mc);  
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);  
    for(int i=1;i<=n;i++)scanf("%d",&w[i]);  
    for(int i=1;i<=m;i++)scanf("%d",&C[i]),maxc=max(maxc,C[i]);  
    memset(dp,-1,sizeof(dp));  
    dp[0][0]=mc;  
    for(int i=0;i<n;i++){  
        for(int j=0;j<=i;j++)if(dp[i][j]!=-1){  
            if(dp[i][j]-a[i+1]<0)continue;  
            dp[i+1][j]=min(mc,max(dp[i+1][j],dp[i][j]-a[i+1]+w[i+1]));  
            dp[i+1][j+1]=min(mc,max(dp[i+1][j+1],dp[i][j]-a[i+1]));  
        }  
        for(int j=0;j<=n;j++)if(dp[i+1][j]!=-1)k=max(k,j);  
    }  
    for(int i=1;i<=m;i++){  
        for(int j=0;j<k&&j<C[i];j++)fl[i]|=calc(C[i]-j)+j<=k;  
        tmp+=fl[i];  
    }  
    dfs(1,14);  
    for(int i=1;i<=m;i++)printf("%d\n",fl[i]);  
    fclose(stdin);
    fclose(stdout);
    return 0;  
}