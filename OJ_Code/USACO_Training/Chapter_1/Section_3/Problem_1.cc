//USACO Training Chapter 1,Section 3,Problem 1
//Powered By Inv.
//Accepted at 2017/4/27 19:52
#include<bits/stdc++.h>
#define N 5010
using namespace std;
struct _t{
    int c,s;
}a[N];
inline bool cmp(_t x,_t y){
    return x.c<y.c;
}
int n,ans=0,m,tot=0;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i].c,&a[i].s);
    }
    if(n==0 || m==0)printf("0\n");
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        if(tot+a[i].s>=m){
            for(int j=1;j<=a[i].s;j++){
                if(tot<m){
                    tot++;
                    ans+=a[i].c;
                }
                else break;
            }
            printf("%d\n",ans);
            break;
        }
        ans+=a[i].c*a[i].s;
        tot+=a[i].s;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}