//USACO Training Chapter 1,Section 1,Problem 2
//Powered By Inv.
//Accepted at 2017/4/26 14:54
#include<bits/stdc++.h>
#define N 32
using namespace std;
map<string,int> m,ans;
map<int,string> rm;
char temp[N]={0};
int n,c,p;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",temp);
        m[temp]=i;
        ans[temp]=0;
        rm[i]=temp;
    }
    for(int i=1;i<=n;i++){
        scanf("%s",temp);
        scanf("%d%d",&c,&p);
        if(p==0)continue;
        int v=c/p;
        ans[temp]-=v*p;
        for(int i=1;i<=p;i++){
            scanf("%s",temp);
            ans[temp]+=v;
        }
    }
    for(int i=1;i<=n;i++){
        printf("%s %d\n",(char*)rm[i].data(),ans[rm[i]]);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}