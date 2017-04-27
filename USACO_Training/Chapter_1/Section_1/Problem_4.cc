//USACO Training Chapter 1,Section 1,Problem 4
//Powered By Inv.
//Accepted at 2017/4/26 19:37
#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
char a[1500];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++){
        scanf("%c",&a[i]);
        a[n*2+i]=a[n+i]=a[i];
    }
    for(int i=n+1;i<=n*2;i++){
        int lans=0,l=i,r=i+1;
        char tl=a[i],tr=a[i+1];
        while(tl=='w')tl=a[--l];
        while(tr=='w')tr=a[++r];
        for(int j=i;j>i-n;j--){
            if(a[j]!=tl && a[j]!='w')break;
            else lans++;
        }
        for(int j=i+1;j<i+1+n;j++){
            if(a[j]!=tr && a[j]!='w')break;
            else lans++;
        }
        ans=max(ans,min(n,lans));
    }
    printf("%d\n",ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}