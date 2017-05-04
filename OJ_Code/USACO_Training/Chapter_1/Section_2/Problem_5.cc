//USACO Training Chapter 1,Section 2,Problem 5
//Powered By Inv.
//Accepted at 2017/4/27 16:42
#include<bits/stdc++.h>
using namespace std;
int n,s,tag=0;
char chs[1024],jz[]={'0','1','2','3','4','5','6','7','8','9'};
void turn(int x,int t){
    memset(chs,0,sizeof(chs));
    int s=0;
    while(x){
        chs[s++]=jz[x%t];
        x/=t;
    }
}
inline bool check(){
    int len=strlen(chs);
    for(int i=0;i<len/2;i++){
        if(chs[i]==chs[len-1-i])continue;
        else return false;
    }
    return true;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d%d",&n,&s);
    for(int i=s+1;n;i++){
        tag=0;
        for(int j=2;j<=10;j++){
            turn(i,j);
            if(check()){
                tag++;
            }
            if(tag==2){
                printf("%d\n",i);
                n--;
                tag=0;
                break;
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}