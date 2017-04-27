//USACO Training Chapter 1,Section 2,Problem 4
//Powered By Inv.
//Accepted at 2017/4/27 15:50
#include<bits/stdc++.h>
using namespace std;
int n,j;
char jz[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char chr[256],chs[1024];
void turn(int x,char *y){
    memset(y,0,sizeof(y));
    int s=0;
    while(x){
        y[s++]=jz[x%n];
        x/=n;
    }
}
inline void check(char a[],char x[]){
    int len=strlen(x);
    for(int i=0;i<len/2;i++){
        if(x[i]==x[len-1-i])continue;
        else return;
    }
    for(int i=strlen(a)-1;i>=0;i--){
        printf("%c",a[i]);
    }
    printf(" ");
    for(int i=0;i<len;i++){
        printf("%c",x[i]);
    }
    printf("\n");
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=300;i++){
        j=i*i;
        turn(i,chr);
        turn(j,chs);
        check(chr,chs);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}