//USACO Training Chapter 1,Section 2,Problem 1
//Powered By Inv.
//Accepted at 2017/4/27 08:55
#include<bits/stdc++.h>
#define N 11000
using namespace std;
struct point{
    int s;
    int c;
}a[N<<1];
inline bool cmpt(point x,point y){
    return x.s==y.s?x.c>y.c:x.s<y.s;
}
inline bool cmp(int x,int y){
    return x>y;
}
int ls[N<<1],lb[N<<1];
int n,t1,t2,cov=0,ans1=0,ans2=0;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&t1,&t2);
        a[i].s=t1,a[i].c=1;
        a[i+n].s=t2,a[i+n].c=-1;
    }
    sort(a+1,a+(n<<1)+1,cmpt);
    int tag=0;
    for(int i=1;i<=n<<1;i++){
        if(cov==0){
            !tag ? tag=2 : tag=1;
            lb[i]=lb[i-1]+a[i].s-a[i-1].s;
            ls[i]=0;
        }
        cov+=a[i].c;
        if(!(a[i].c==1 && cov==1)){
            ls[i]=ls[i-1]+a[i].s-a[i-1].s;
            lb[i]=0;
        } 
    }
    sort(ls+1,ls+1+(n<<1),cmp);
    sort(lb+1,lb+1+(n<<1),cmp);
    printf("%d %d",ls[1],tag==2?0:lb[1]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}