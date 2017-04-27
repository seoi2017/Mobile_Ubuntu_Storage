//USACO Training Chapter 1,Section 1,Problem 3
//Powered By Inv.
//Accepted at 2017/4/26 15:48
#include<bits/stdc++.h>
using namespace std;
int n,ans[8]={0},nd=1;
int days(int x,int y){
    if(y==2){
        if(x%100==0){
            if(x%400==0){
                return 29;
            }
            else return 28;
        }
        else if(x%4==0){
            return 29;
        }
        else return 28;
    }
    else{
        if(y==4 || y==6 || y==9 || y==11){
            return 30;
        }
        else return 31;
    }
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&n);
    for(int i=1900;i<1900+n;i++){
        for(int j=1;j<=12;j++){
            for(int k=1;k<=days(i,j);k++){
                if(k==13){
                    ans[nd]++;
                }
                nd==7 ? nd=1 : nd++;
            }
        }
    }
    printf("%d %d %d %d %d %d %d\n",ans[6],ans[7],ans[1],ans[2],ans[3],ans[4],ans[5]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}