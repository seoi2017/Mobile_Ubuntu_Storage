//Problem:[POJ1177][Find them,Catch them]
//Powered By HYS.
//Accepted at 21:03:42,2017/04/11 on VJudge.
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define N 100010
using namespace std;
int fa[N*2]={0},b[N],c[N],n,m;
char a[N];
inline int findfa(int x){
    return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
inline void bing(int x,int y){
    fa[findfa(y)]=findfa(x);
}
int main(){
    freopen("input.txt","r",stdin),freopen("output.txt","w",stdout);
    int cases;
    scanf("%d",&cases);
    while(cases--){
        scanf("%d%d\n",&n,&m);
        for(int i=1;i<=n*2;i++)fa[i]=i;
        for(int i=1;i<=m;i++)scanf("%c %d %d\n",&a[i],&b[i],&c[i]);
        if(n==2){
            printf("In different gangs.\n");
            continue;
        }
        for(int i=1;i<=m;i++){
            if(a[i]=='A'){
                int x=findfa(b[i]),y=findfa(c[i]);
                if(x==findfa(c[i]+n)||y==findfa(b[i]+n))printf("In different gangs.\n");
                else if(x==y)printf("In the same gang.\n");
                else printf("Not sure yet.\n");
            }
            else{
                bing(b[i],c[i]+n);
                bing(c[i],b[i]+n);
            }
        }
    }
    fclose(stdin),fclose(stdout);
    return 0;
}