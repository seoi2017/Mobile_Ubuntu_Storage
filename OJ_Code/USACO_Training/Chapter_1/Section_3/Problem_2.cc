//USACO Training Chapter 1,Section 3,Problem 2
//Powered By Inv.
//Accepted at 2017/5/4 16:20
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
const int MX=301;
int a[MX],dp[MX][MX],si[MX],sj[MX];
int m,s,c,tag=0;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d%d%d",&m,&s,&c);
    for(int i=1;i<=c;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+1+c);
    for(int i=1;i<=c;i++){
        si[a[i]]=1;
        i==1?sj[a[i]]=1:sj[a[i]]=a[i]-tag;
        tag=a[i];
    }
    for(int i=0;i<=s;i++){
        dp[0][i]=INF;
    }
    for(int i=0;i<=m;i++){  
        dp[i][0]=0;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=s;j++){
            dp[i][j]=si[j]?min(dp[i-1][j-1]+1,dp[i][j-1]+sj[j]):dp[i][j-1];
        }
    }
    printf("%d\n",dp[m][s]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}