//USACO Training Chapter 1,Section 3,Problem 3
//Powered By Inv.
//Accepted at 2017/5/4 16:--
#include<bits/stdc++.h>
using namespace std;
int n,a[11],ans=0;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                for(int l=1;l<=n;l++){
                    for(int m=1;m<=n;m++){
                        int x=(a[i]*100+a[j]*10+a[k]),y=(a[l]*10+a[m]);
                        if(!x/100<=9 || !y/10<=9)continue;
                        if(!x*y/1000<=9)continue;
                        if()continue;
                        ans++;
                        printf("%d*%d\n",(a[i]*100+a[j]*10+a[k]),(a[l]*10+a[m]));
                    }
                }
            }
        }
    }
    printf("%d\n",ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}